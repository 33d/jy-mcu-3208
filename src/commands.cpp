#include <stdlib.h>
#include <string.h>
#include "commands.h"

uint8_t* parse_rate(const char* src, uint8_t* dest) {
    *(dest++) = atoi(src);
    return dest;
}

uint8_t* string_to_pstring(const char* src, uint8_t* dest) {
    uint8_t count = 0;
    uint8_t* lenByte = dest;
    ++dest;
    while ((*src != '\0') && (*src != '\r') && (*src != '\n')) {
        *(dest++) = *(src++);
        ++count;
    }
    *lenByte = count;
    return dest;
}

uint8_t* parse_sleep(const char* src, uint8_t* dest) {
    uint16_t* destInt = (uint16_t*) dest;
    *destInt = atoi(src);
    return dest+2;
}

uint8_t* parse_bitmap(const char* src, uint8_t* dest) {
    memcpy(dest, src, 32);
    return dest + 32;
}

#define DEFNAME(x) const char* name_ ## x /*PROGMEM*/  = #x
DEFNAME(rate);
DEFNAME(hscroll);
DEFNAME(left);
DEFNAME(sleep);
DEFNAME(bitmap);
DEFNAME(end);

const struct Command commands[] /*PROGMEM*/ = {
    { name_rate, CODE_RATE, parse_rate },
    { name_hscroll, CODE_HSCROLL, string_to_pstring },
    { name_left, CODE_LEFT, string_to_pstring },
    { name_sleep, CODE_SLEEP, parse_sleep },
    { name_bitmap, CODE_BITMAP, parse_bitmap },
    { name_end, CODE_END, 0 },
    { 0, 0, 0 }
};
