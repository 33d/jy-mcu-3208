/*
 * display.cpp
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#include "display.h"
#include "ht1632c.h"
#include <util/delay_basic.h>

Display::Display() {
    ::HTpinsetup();
    ::HTsetup();
    set_delay(20);
}

void Display::show(Effect& effect) {
    while (1) {
        if (!effect.step())
            break;
        _delay_loop_2(delay);
        HTsendscreen();
    }
}

void Display::set_delay(uint8_t delay_ms) {
    // Divide by 4 because _delay_loop_2 takes 4 cycles
    this->delay = (F_CPU / 1000) * delay_ms / 4;
}
