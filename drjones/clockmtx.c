// Clock programm for DX 32*8 LED Matrix + HT1632C + ATmega8; 
// DrJones 2012
//
// button1: adjust time forward, keep pressed for a while for fast forward
// button2: adjust time backward, keep pressed for a while for fast backward
// button3: adjust brightness in 4 steps




/* #define F_CPU 1000000 */

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>

#define byte uint8_t
#define word uint16_t



PROGMEM byte bigdigits[10][6] = {
  {126,129,129,129,129,126},  {128,132,130,255,128,128},            // 0,1
  {130,193,161,145,137,134},  { 66,129,137,137,137,118},            // 2,3
  {0x3f,0x20,0x20,0xfc,0x20,0x20}, {0x4f,0x89,0x89,0x89,0x89,0x71}, // 4,5
  {0x7e,0x89,0x89,0x89,0x89,0x72}, {0x03,0x01,0xc1,0x31,0x0d,0x03}, // 6,7
  {0x76,0x89,0x89,0x89,0x89,0x76}, {0x46,0x89,0x89,0x89,0x89,0x7e}, // 8,9
};




//pins and macros

#define HTport   PORTB
#define HTddr    DDRB
#define HTstrobe 3
#define HTclk    4
#define HTdata   5

#define HTclk0    HTport&=~(1<<HTclk)
#define HTclk1    HTport|= (1<<HTclk)
#define HTstrobe0 HTport&=~(1<<HTstrobe)
#define HTstrobe1 HTport|= (1<<HTstrobe)
#define HTdata0   HTport&=~(1<<HTdata)
#define HTdata1   HTport|= (1<<HTdata)
#define HTpinsetup() do{  HTddr |=(1<<HTstrobe)|(1<<HTclk)|(1<<HTdata); HTport|=(1<<HTstrobe)|(1<<HTclk)|(1<<HTdata);  }while(0)
        // set as output and all high


#define key1 ((PIND&(1<<7))==0)
#define key2 ((PIND&(1<<6))==0)
#define key3 ((PIND&(1<<5))==0)
#define keysetup() do{ DDRD&=0xff-(1<<7)-(1<<6)-(1<<5); PORTD|=(1<<7)+(1<<6)+(1<<5); }while(0)  //input, pull up


byte leds[32];  //the screen array, 1 byte = 1 column, left to right, lsb at top. 


#define HTstartsys   0b100000000010 //start system oscillator
#define HTstopsys    0b100000000000 //stop sytem oscillator and LED duty    <default
#define HTsetclock   0b100000110000 //set clock to master with internal RC  <default
#define HTsetlayout  0b100001000000 //NMOS 32*8 // 0b100-0010-ab00-0  a:0-NMOS,1-PMOS; b:0-32*8,1-24*16   default:ab=10
#define HTledon      0b100000000110 //start LEDs
#define HTledoff     0b100000000100 //stop LEDs    <default
#define HTsetbright  0b100101000000 //set brightness b=0..15  add b<<1  //0b1001010xxxx0 xxxx:brightness 0..15=1/16..16/16 PWM
#define HTblinkon    0b100000010010 //Blinking on
#define HTblinkoff   0b100000010000 //Blinking off  <default
#define HTwrite      0b1010000000   // 101-aaaaaaa-dddd-dddd-dddd-dddd-dddd-... aaaaaaa:nibble adress 0..3F   (5F for 24*16)

//ADRESS: MSB first
//DATA: LSB first     transferring a byte (msb first) fills one row of one 8*8-matrix, msb left, starting with the left matrix
//timing: pull strobe LOW, bits evaluated at rising clock edge, strobe high
//commands can be queued: 100-ccccccccc-ccccccccc-ccccccccc-... (ccccccccc: without 100 at front)
//setup: cast startsys, setclock, setlayout, ledon, brightness+(15<<1), blinkoff



void HTsend(word data, byte bits) {  //MSB first
  word bit=((word)1)<<(bits-1);
  while(bit) {
    HTclk0;
    if (data & bit) HTdata1; else HTdata0;
    HTclk1;
    bit>>=1;
  }
}

void HTcommand(word data) {
  HTstrobe0;
  HTsend(data,12);
  HTstrobe1;
}

void HTsendscreen(void) {
  HTstrobe0;
  HTsend(HTwrite,10);
  for (byte mtx=0;mtx<4;mtx++)  //sending 8x8-matrices left to right, rows top to bottom, MSB left
    for (byte row=0;row<8;row++) {  //while leds[] is organized in columns for ease of use.
      byte q=0;
      for (byte col=0;col<8;col++)  q = (q<<1) | ( (leds[col+(mtx<<3)]>>row)&1 ) ;
      HTsend(q,8);
    }
  HTstrobe1;
}


void HTsetup() {  //setting up the display
  HTcommand(HTstartsys);
  HTcommand(HTledon);
  HTcommand(HTsetclock);
  HTcommand(HTsetlayout);
  HTcommand(HTsetbright+(8<<1));
  HTcommand(HTblinkoff);
}

void HTbrightness(byte b) {
  HTcommand(HTsetbright + ((b&15)<<1) );
}

//------------------------------------------------------------------------------------- CLOCK ------------------


volatile byte sec=5;
byte sec0=200, minute, hour, day, month; word year;


inline void clocksetup() {  // CLOCK, interrupt every second
  ASSR |= (1<<AS2);    //timer2 async from external quartz
  TCCR2=0b00000101;    //normal,off,/128; 32768Hz/256/128 = 1 Hz
  TIMSK |= (1<<TOIE2); //enable timer2-overflow-int
  sei();               //enable interrupts
}


// CLOCK interrupt
ISR(TIMER2_OVF_vect) {     //timer2-overflow-int
  sec++;
}



void incsec(byte add) {
  sec+=add;
  while (sec>=60) { 
    sec-=60;  minute++;
    while (minute>=60) {
      minute -= 60;  hour++;
      while (hour >=24) {
        hour-=24;  day++;
      }//24hours
    }//60min
  }//60sec
}

void decsec(byte sub) {
  while (sub>0) {
    if (sec>0) sec--; 
    else {
      sec=59; 
      if (minute>0) minute--; 
      else {
        minute=59; 
        if (hour>0) hour--;
        else {hour=23;day--;}
      }//hour
    }//minute
    sub--;
  }//sec
}

byte clockhandler(void) {
  if (sec==sec0) return 0;   //check if something changed
  sec0=sec;
  incsec(0);  //just carry over
  return 1;
}

//-------------------------------------------------------------------------------------- clock render ----------

void renderclock(void) {
  byte col=0;
  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[hour/10][i]);
  leds[col++]=0;
  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[hour%10][i]);
  leds[col++]=0;
  if (sec%2) {leds[col++]=0x66;leds[col++]=0x66;} else {leds[col++]=0; leds[col++]=0;}
  leds[col++]=0;
  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[minute/10][i]);
  leds[col++]=0;
  for (byte i=0;i<6;i++) leds[col++]=pgm_read_byte(&bigdigits[minute%10][i]);
  leds[col++]=0;
  leds[col++]=(sec>6) +((sec>13)<<1) +((sec>20)<<2) +((sec>26)<<3) +((sec>33)<<4) +((sec>40)<<5) +((sec>46)<<6) +((sec>53)<<7);
}



byte changing, bright=3;
byte brights[4]={0,2,6,15}; //brightness levels

int main(void) {  //==================================================================== main ==================

  HTpinsetup();
  HTsetup();
  keysetup();
  clocksetup();

  for (byte i=0;i<32;i++) leds[i]=0b01010101<<(i%2);  HTsendscreen();


  hour=7;minute=40;

  while(1){ 
         if (key1) {if (changing>250) incsec(20); else {changing++; incsec(1);} }
    else if (key2) {if (changing>250) decsec(20); else {changing++; decsec(1);} }
    else if (key3) {if (!changing) {changing=1; bright=(bright+1)%4; HTbrightness(brights[bright]);} } //only once per press
    else changing=0;

    if(clockhandler()) { renderclock(); HTsendscreen(); }
  }
  return(0);
}//main
