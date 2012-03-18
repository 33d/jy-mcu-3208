/*
 * effect.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef EFFECT_H_
#define EFFECT_H_

#include <stdint.h>

class Effect {
public:
    virtual void run(const char* text) = 0;
    virtual ~Effect();
};

class HScrollEffect: public Effect {
private:
    const uint16_t delay;
    const bool blankAtEnd;
public:
    virtual void run(const char* text);
    HScrollEffect(uint16_t delayms, bool blankAtEnd = true)
        : delay(delayms), blankAtEnd(blankAtEnd) {}
};

#endif /* EFFECT_H_ */
