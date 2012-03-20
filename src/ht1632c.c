/*
 Based on code from DrJones:
   http://club.dealextreme.com/forums/Forums.dx/threadid.1118199?page=1
   http://lux.yi.org/clockmtx.c
*/

#include <avr/pgmspace.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/eeprom.h>
#include "ht1632c.h"

#define byte uint8_t
#define word uint16_t

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

// set as output and all high
void HTpinsetup() {
    HTddr |=(1<<HTstrobe)|(1<<HTclk)|(1<<HTdata); HTport|=(1<<HTstrobe)|(1<<HTclk)|(1<<HTdata);
}

byte leds[32];  //the screen array, 1 byte = 1 column, left to right, lsb at top.
byte* HTleds = leds;

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
