/*
 * delay.h
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#ifndef DELAY_H_
#define DELAY_H_

#include "effect.h"
#include <stdint.h>

class DelayEffect: public Effect {
    uint16_t cycles;
public:
    DelayEffect(Display& display, uint16_t cycles): Effect(display), cycles(cycles) {};
    bool step() { return (--cycles > 0); }
};

#endif /* DELAY_H_ */
