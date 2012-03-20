/*
 * display.cpp
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#include "display.h"
#include "ht1632c.h"

Display::Display(const Font& font)  : font(font) {
    ::HTpinsetup();
    ::HTsetup();
}

void Display::show(const char* text, Effect& effect) {
    effect.run(font, text);
}
