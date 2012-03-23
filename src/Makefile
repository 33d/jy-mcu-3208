PROJECT	       = demo

PRG            = $(PROJECT)
OBJECTS        = 
AVR_OBJECTS    = display ht1632c runner avrcpp \
        effects/hscroll \
        font fonts/jiffy \
        $(PROJECT) 
TEST_OBJECTS   = 

ARDUINO_HOME  ?= /opt/arduino-0018

# "arduino" or any programmer supported by avrdude
PROGRAMMER    ?= arduino
#UPLOAD_SPEED   = 19200 # for Diecimilia
UPLOAD_SPEED  ?= 57600
UPLOAD_PORT   ?= /dev/ttyUSB0

MCU_TARGET    ?= atmega8
OPTIMIZE       = -O2

DEFS           = -DF_CPU=1000000L
LIBS           = 
TEST_LIBS      = -lcunit

# You should not have to change anything below here.

AVRCC          = avr-gcc
AVRCPP         = avr-g++

# Override is only needed by avr-lib build system.

CALLFLAGS      = -g -Wall $(OPTIMIZE) -mmcu=$(MCU_TARGET) \
	-ffunction-sections -fdata-sections \
	$(DEFS)
	#-funsigned-char -funsigned-bitfields -fpack-struct -short-enums 
override AVRCFLAGS        = $(CALLFLAGS) -std=gnu99  
override AVRCPPFLAGS      = $(CALLFLAGS)
override AVRLDFLAGS       = -Wl,-Map,$(PRG).map

AVROBJCOPY      = avr-objcopy
OBJDUMP         = avr-objdump

INCLUDES = -I.

BUILD_DIR	= build
TEST_DIR	= test
BUILD_OBJS	= $(foreach OBJ,$(OBJECTS) $(AVR_OBJECTS),$(OBJ).avr.o)
TEST_OBJS	= $(foreach OBJ,$(OBJECTS) $(TEST_OBJECTS),$(OBJ).o) test.o

.PHONY: reset_arduino

export CFLAGS CPPFLAGS F_CPU LDFLAGS ARDUINO_HOME CC CPP INCLUDES ARDUINO_CORE

all: $(PRG).elf lst text eeprom

$(PRG).elf: $(BUILD_OBJS)
	# I have no idea why I need $(LIBS) twice
	$(AVRCPP) $(AVRCPPFLAGS) $(AVRLDFLAGS) -o $@ $(LIBS) $^ $(LIBS)

%.avr.o : %.c 
	$(AVRCC) $(AVRCFLAGS) $(INCLUDES) -c -o $@ $<

%.avr.o : %.cpp
	$(AVRCPP) $(AVRCPPFLAGS) $(INCLUDES) -c -o $@ $<

test: test-prg
	./test

test-prg: $(TEST_OBJS)
	$(CXX) $(CPPFLAGS) $(LDFLAGS) -o test $^ $(TEST_LIBS)

clean:
	rm -rf *.o *.avr.o $(PRG).elf *.eps *.png *.pdf *.bak 
	rm -rf *.lst *.map $(EXTRA_CLEAN_FILES)

lst:  $(PRG).lst

%.lst: %.elf
	$(OBJDUMP) -h -S $< > $@

# Rules for building the .text rom images

text: hex bin srec

hex:  $(PRG).hex
bin:  $(PRG).bin
srec: $(PRG).srec

%.hex: %.elf
	$(AVROBJCOPY) -j .text -j .data -O ihex $< $@

%.srec: %.elf
	$(AVROBJCOPY) -j .text -j .data -O srec $< $@

%.bin: %.elf
	$(AVROBJCOPY) -j .text -j .data -O binary $< $@

# Rules for building the .eeprom rom images

eeprom: ehex ebin esrec

ehex:  $(PRG)_eeprom.hex
ebin:  $(PRG)_eeprom.bin
esrec: $(PRG)_eeprom.srec

%_eeprom.hex: %.elf
	$(AVROBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O ihex $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.srec: %.elf
	$(AVROBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O srec $< $@ \
	|| { echo empty $@ not generated; exit 0; }

%_eeprom.bin: %.elf
	$(AVROBJCOPY) -j .eeprom --change-section-lma .eeprom=0 -O binary $< $@ \
	|| { echo empty $@ not generated; exit 0; }

# Every thing below here is used by avr-libc's build system and can be ignored
# by the casual user.

FIG2DEV                 = fig2dev
EXTRA_CLEAN_FILES       = *.hex *.bin *.srec

ifeq ($(PROGRAMMER),arduino)
AVRDUDE = $(ARDUINO_HOME)/hardware/tools/avrdude \
		-C$(ARDUINO_HOME)/hardware/tools/avrdude.conf \
		-p$(MCU_TARGET) -cstk500v1 -P$(UPLOAD_PORT) \
		-b$(UPLOAD_SPEED)

reset_arduino:
	# Reset the Arduino first to activate the bootloader
	stty 57600 raw ignbrk hup < $(UPLOAD_PORT)

else
AVRDUDE = avrdude \
		-p$(MCU_TARGET) -c$(PROGRAMMER) -P$(UPLOAD_PORT) \
		-b$(UPLOAD_SPEED)

reset_arduino:

endif
	
upload: $(PRG).hex reset_arduino
	$(AVRDUDE) -Uflash:w:$<:i

