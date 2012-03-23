/*
 * runner.cpp
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#include "runner.h"
#include <util/delay_basic.h>

void Runner::show(Effect& effect) {
    while (1) {
        if (!effect.step())
            break;
        _delay_loop_2(delay);
        display.update();
    }
}

void Runner::set_delay(uint8_t delay_ms) {
    // Divide by 4 because _delay_loop_2 takes 4 cycles
    this->delay = (F_CPU / 1000) * delay_ms / 4;
}

uint8_t Runner::get_delay() const {
    return delay / (F_CPU / 1000) * 4;
}
