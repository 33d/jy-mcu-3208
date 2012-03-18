#include <stdint.h>
#include <avr/pgmspace.h>

struct Glyph {
    const uint8_t width;
    const uint8_t* data;
};

const uint8_t _startEndData[] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
const struct Glyph startEndGlyph = {
    32, _startEndData
};

const uint8_t _font_data[] = {
    0x3e, 0x7f, 0x41, 0x41, 0x41, 0x7f, 0x3e, 0x00, 0x02, 0x7f, 0x7f, 0x00
};

const struct Glyph font[] = {
    { 8, _font_data },
    { 4, _font_data + 8 }
};
