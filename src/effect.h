/*
 * effect.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef EFFECT_H_
#define EFFECT_H_

#include <stdint.h>
#include "font.h"

class Effect {
protected:
    const Font& font;
    const char* text;
public:
    Effect(const Font& font, const char* text)
        : font(font), text(text) {}
    virtual bool step() = 0;
    virtual ~Effect();
};

class HScrollEffect: public Effect {
private:
    const bool blankAtEnd;
    uint8_t textLength;
    uint8_t maxPos;
    uint8_t pos;
    uint8_t glyph_width;
    uint8_t charCol;
public:
    HScrollEffect(const Font& font, const char* text,
            bool blankAtEnd);
    virtual bool step();
};

#endif /* EFFECT_H_ */
