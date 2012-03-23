/*
 * effect.cpp
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#include <string.h> // should be <cstring>
#include <util/delay.h>
#include "hscroll.h"

HScrollEffect::HScrollEffect(Display& display, const Font& font, const PString& text, bool blankAtEnd = true)
    : TextEffect(display, font, text), blankAtEnd(blankAtEnd), pos(0), charCol(0) {
    // The length, including the blank space at the end (if requested)
    maxPos = blankAtEnd ? text.length() + 1 : text.length();
    glyph_width = font.char_width(text[pos]);
}

bool HScrollEffect::step() {
    // Shift the memory
    memmove(display.buffer, display.buffer + 1, 31);

    // Render the last column
    display.buffer[31] = pos < text.length()
        ? font.char_col(text[pos], charCol)
        : 0;

    // Move the starting column
    ++charCol;
    if (charCol >= glyph_width) {
        ++pos;
        charCol = 0;
        glyph_width = pos < text.length() ? font.char_width(text[pos]) : 32;
    }

    return (pos < maxPos);
}
