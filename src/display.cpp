/*
 * display.cpp
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#include "display.h"
#include "ht1632c.h"
#include <util/delay_basic.h>
#include <string.h>

Display::Display(): buffer(HTleds) {
    ::HTpinsetup();
    ::HTsetup();
}

void Display::update() {
    HTsendscreen();
}

void Display::clear() {
    ::memset(buffer, 0, 32);
}
