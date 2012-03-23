/*
 * display.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <stdint.h>

class Display {
public:
    uint8_t* const buffer;
    Display();
    void update();
};

#endif /* DISPLAY_H_ */
