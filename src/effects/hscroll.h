/*
 * effect.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef HSCROLL_H_
#define HSCROLL_H_

#include <stdint.h>
#include "font.h"
#include "display.h"
#include "effect.h"

class HScrollEffect: public TextEffect {
private:
    const bool blankAtEnd;
    uint8_t textLength;
    uint8_t maxPos;
    uint8_t pos;
    uint8_t glyph_width;
    uint8_t charCol;
public:
    HScrollEffect(Display& display, const Font& font, const char* text,
            bool blankAtEnd);
    virtual bool step();
};

#endif /* EFFECT_H_ */
