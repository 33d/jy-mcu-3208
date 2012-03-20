/*
 * display.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "effect.h"
#include "font.h"

class Display {
    const Font& font;
public:
    Display(const Font& font);
    void show(const char* text, Effect& effect);
};

#endif /* DISPLAY_H_ */
