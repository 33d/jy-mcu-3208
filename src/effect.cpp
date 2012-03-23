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

HScrollEffect::HScrollEffect(const Font& font, const char* text, bool blankAtEnd = true)
    : Effect(font, text), blankAtEnd(blankAtEnd), pos(0), charCol(0) {
    textLength = ::strlen(text);
    // The length, including the blank space at the end (if requested)
    maxPos = blankAtEnd ? textLength + 1 : textLength;
    glyph_width = font.char_width(text[pos]);
}

bool HScrollEffect::step() {
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

    return (pos < maxPos);
}
