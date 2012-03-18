/*
 * display.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "effect.h"

class Display {
public:
    Display();
    void show(const char* text, Effect& effect);
};

#endif /* DISPLAY_H_ */
