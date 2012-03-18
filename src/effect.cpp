/*
 * effect.cpp
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#include "ht1632c.h"
#include "font.h"
#include <string.h> // should be <cstring>
#include <util/delay.h>
#include "effect.h"

Effect::~Effect() {}

void HScrollEffect::run(const char* text) {
    uint8_t textLength = ::strlen(text);
    // The length, including the blank space at the end (if requested)
    uint8_t maxPos = blankAtEnd ? textLength + 1 : textLength;
    uint8_t pos = 0;
    const struct Glyph* glyph = &font[text[pos] - '0'];
    uint8_t charCol = 0;

    while (pos < maxPos) {
        // Shift the memory
        memmove(HTleds, HTleds + 1, 31);

        // Render the last column
        HTleds[31] = pos < textLength
            ? glyph->data[charCol]
            : 0;

        // Move the starting column
        ++charCol;
        if (charCol >= glyph->width) {
            ++pos;
            charCol = 0;
            glyph = pos < textLength
                ? &font[text[pos] - '0']
                : &startEndGlyph;
        }

        HTsendscreen();
        _delay_ms(30);
    }
}
