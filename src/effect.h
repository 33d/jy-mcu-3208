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
#include "pstring.h"

class Effect {
protected:
    Display& display;
protected:
    Effect(Display& display): display(display) {};
public:
    virtual bool step() = 0;
    virtual ~Effect() {};
};

class TextEffect: public Effect {
protected:
    const Font& font;
    const PString& text;
    TextEffect(Display& display, const Font& font, const PString& text)
        : Effect(display), font(font), text(text) {}
};

#endif

