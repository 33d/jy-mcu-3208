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
    int8_t startPos = -1;
    const struct Glyph* startGlyph = &startEndGlyph;
    uint8_t startCharCol = 0;

    while (startPos < textLength) {
        int8_t currentPos = startPos;
        uint8_t currentCharCol = startCharCol;
        const struct Glyph* glyph = startGlyph;
        // Render a frame
        for (uint8_t col = 0; col < 32; col++) {
            // Is this column not before or after the text?
            HTleds[col] = currentPos >= 0 && currentPos < textLength
                ? glyph->data[currentCharCol]
                : 0;
            ++currentCharCol;
            if (currentCharCol >= glyph->width) {
                // go to the next character
                ++currentPos;
                char c = text[currentPos];
                glyph = currentPos > textLength
                    ? &startEndGlyph // the space at the end
                    : &font[c - '0'];
                currentCharCol = 0;
            }
        }

        // Move the starting column
        ++startCharCol;
        if (startCharCol >= startGlyph->width) {
            ++startPos;
            startCharCol = 0;
            startGlyph = startPos <= textLength
                ? &font[text[startPos] - '0']
                : &startEndGlyph;
        }

        HTsendscreen();
        _delay_ms(30);
    }
}
