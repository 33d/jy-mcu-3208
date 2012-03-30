/*
 * commands.h
 *
 *  Created on: 25/03/2012
 *      Author: damien
 */

#ifndef COMMANDS_H_
#define COMMANDS_H_

#if defined(AVR)
#include <avr/pgmspace.h>
#endif
#include <stdint.h>

// code 0 is reserved
#define CODE_END ((uint8_t) 1)
#define CODE_RATE ((uint8_t) 2)
#define CODE_HSCROLL ((uint8_t) 3)
#define CODE_LEFT ((uint8_t) 4)
#define CODE_SLEEP ((uint8_t) 5)
#define CODE_BITMAP ((uint8_t) 6)

typedef uint8_t*(*CommandParser)(const char* src, uint8_t* dest);

struct Command {
    const char* const name;
    const uint8_t code;
    CommandParser parser;
};

extern const struct Command commands[];

#endif /* COMMANDS_H_ */
