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
#include "display.h"

class Effect {
protected:
    Display& display;
protected:
    Effect(Display& display): display(display) {};
public:
    virtual bool step() = 0;
    virtual ~Effect();
};

class TextEffect: public Effect {
protected:
    const Font& font;
    const char* text;
    TextEffect(Display& display, const Font& font, const char* text)
        : Effect(display), font(font), text(text) {}
};

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
