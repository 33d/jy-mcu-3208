/*
 * left.cpp
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#include "left.h"
#include <string.h>

bool LeftEffect::step() {
    display.clear();

    uint8_t count = 0; // checks for overflows
    for (uint8_t p = 0; p < text.length(); p++) {
        for (uint8_t col = 0; col < font.char_width(text[p]); col++) {
            display.buffer[count++] = font.char_col(text[p], col);
            if (count >= 32)
                return false;
        }
    }

    return false;
}
