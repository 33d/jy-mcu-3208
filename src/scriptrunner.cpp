/*
 * scriptrunner.cpp
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#include "scriptrunner.h"
#include "pstring.h"
#include "fonts/jiffy.h"
#include "effects/hscroll.h"
#include "effects/left.h"
#include "effects/delay.h"
#include "effects/bitmap.h"

#define END ((uint8_t) 1)
#define RATE ((uint8_t) 2)
#define HSCROLL ((uint8_t) 3)
#define LEFT ((uint8_t) 4)
#define SLEEP ((uint8_t) 5)
#define BITMAP ((uint8_t) 6)

uint8_t ScriptRunner::script[] = {
    RATE, 20,
    HSCROLL, 5, 'H', 'e', 'l', 'l', 'o',
    LEFT, 5, 'W', 'o', 'r', 'l', 'd',
    SLEEP, 0x03, 0xE8,
    BITMAP, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x14, 0x28, 0x38, 0x48,
        0x70, 0x90, 0xf7, 0x97, 0xf0, 0x97, 0xf7, 0x90, 0x70, 0x48, 0x38,
        0x28, 0x14, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    SLEEP, 0x03, 0xE8,
    HSCROLL, 1, ' ', // length=0 doesn't work (it should though)
    END
};

void ScriptRunner::run() {
    uint8_t command;
    while (true) {
        command = *(pos++);
        if (command == END) {
            pos = script;
            break;
        }

        switch (command) {
        case RATE:
            runner.set_delay(*(pos++));
            break;
        case HSCROLL: {
            PString text(pos++);
            HScrollEffect effect(runner.get_display(), font_jiffy, text, true);
            runner.show(effect);
            pos += text.size();
        } break;
        case LEFT: {
            PString text(pos++);
            LeftEffect effect(runner.get_display(), font_jiffy, text);
            runner.show(effect);
            pos += text.size();
        } break;
        case SLEEP: {
            uint16_t cycles = *(pos++);
            cycles <<= 8;
            cycles |= *(pos++);
            cycles /= runner.get_delay();
            DelayEffect effect(runner.get_display(), cycles);
            runner.show(effect);
        } break;
        case BITMAP: {
            BitmapEffect effect(runner.get_display(), pos);
            runner.show(effect);
            pos += 32;
        } break;
        }
    }
}
