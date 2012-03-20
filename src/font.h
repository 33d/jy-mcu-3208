/*
 * font.h
 *
 *  Created on: 20/03/2012
 *      Author: damien
 */

#ifndef FONT_H_
#define FONT_H_

#include <stdint.h>

/**
 * A font.  This wraps the font data, and keeps the progmem stuff
 * out of the rest of the code.
 */
class Font {
    // These are pointers to flash, not RAM
    const uint16_t* offsets;
    const uint8_t* data;
public:
    Font(const uint16_t* offsets, const uint8_t* data)
        : offsets(offsets), data(data) {}
    uint8_t char_width(char c) const;
    uint8_t char_col(char c, uint8_t column) const;
};

#endif /* FONT_H_ */
