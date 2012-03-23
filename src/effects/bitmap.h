/*
 * bitmapeffect.h
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#ifndef BITMAPEFFECT_H_
#define BITMAPEFFECT_H_

#include "effect.h"

class BitmapEffect: public Effect {
    const uint8_t* data;
public:
    BitmapEffect(Display& display, const uint8_t* data): Effect(display), data(data) {};
    bool step();
};

#endif /* BITMAPEFFECT_H_ */
