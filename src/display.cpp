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

    for (uint8_t i=0;i<32;i++) HTleds[i]=0b01010101<<(i%2);  HTsendscreen();
}

void Display::show(const char* text, Effect& effect) {
    effect.run(font, text);
}
