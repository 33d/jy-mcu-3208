/*
 * bitmapeffect.cpp
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#include "bitmap.h"
#include <string.h>

bool BitmapEffect::step() {
    ::memcpy(display.buffer, data, 32);
    return false;
}
