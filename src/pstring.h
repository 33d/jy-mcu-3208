/*
 * string.h
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#ifndef PSTRING_H_
#define PSTRING_H_

#include <stdint.h>

/**
 * A Pascal-style string; that is, with the length at the start.  This limits
 * the string to 255 bytes.
 */
class PString {
    const uint8_t len;
    const char* text;
public:
    PString(const uint8_t* string): len(*string), text((char*) (string+1)) {}
    /** The length of the string, in characters. */
    uint8_t length() const { return len; }
    /** The length of the string, in bytes; not including the length byte. */
    uint8_t size() const { return len; }
    /**
     * Fetches the character at some character offset.  A Unicode version
     * would return some other data type.
     */
    char operator[](uint8_t pos) const { return text[pos]; }
};

#endif /* STRING_H_ */
