/*
 * effect.cpp
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#include "ht1632c.h"
#include <string.h> // should be <cstring>
#include <util/delay.h>
#include "effect.h"

Effect::~Effect() {}

void HScrollEffect::run(const Font& font, const char* text) {
    uint8_t textLength = ::strlen(text);
    // The length, including the blank space at the end (if requested)
    uint8_t maxPos = blankAtEnd ? textLength + 1 : textLength;
    uint8_t pos = 0;
    uint8_t glyph_width = font.char_width(text[pos]);
    uint8_t charCol = 0;

    while (pos < maxPos) {
        // Shift the memory
        memmove(HTleds, HTleds + 1, 31);

        // Render the last column
        HTleds[31] = pos < textLength
            ? font.char_col(text[pos], charCol)
            : 0;

        // Move the starting column
        ++charCol;
        if (charCol >= glyph_width) {
            ++pos;
            charCol = 0;
            glyph_width = pos < textLength ? font.char_width(text[pos]) : 32;
        }

        HTsendscreen();
        _delay_ms(30);
    }
}
