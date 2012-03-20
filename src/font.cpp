#include <avr/pgmspace.h>
#include <stdint.h>
#include "font.h"

uint8_t Font::char_width(char c) const {
    const uint16_t* PROGMEM addr = offsets + (c - ' ');
    return (uint8_t) (pgm_read_word(addr+1) - pgm_read_word(addr));
}

uint8_t Font::char_col(char c, uint8_t column) const {
    const uint16_t* PROGMEM addr = offsets + (c - ' ');
    const uint8_t* PROGMEM glyph_addr = data + pgm_read_word(addr);
    return pgm_read_byte(glyph_addr + column);
}
