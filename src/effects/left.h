/*
 * left.h
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#ifndef LEFT_H_
#define LEFT_H_

#include "effect.h"
#include "display.h"

class LeftEffect: public TextEffect {
public:
    LeftEffect(Display& display, const Font& font, const PString& text)
        : TextEffect(display, font, text) {};
    bool step();
};

#endif /* LEFT_H_ */
