/*
 * runner.h
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#ifndef RUNNER_H_
#define RUNNER_H_

#include "effect.h"

class Runner {
    Display& display;
    uint16_t delay;
public:
    Runner(Display& display): display(display), delay(20) {};
    void show(Effect& effect);
    void set_delay(uint8_t delay_ms);
};

#endif /* RUNNER_H_ */
