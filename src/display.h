/*
 * display.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>
#include "effect.h"
#include "font.h"

class Display {
    uint16_t delay;
public:
    Display();
    void set_delay(uint8_t delay_ms);
    void show(Effect& effect);
};

#endif /* DISPLAY_H_ */
