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
#include "commands.h"

/*
uint8_t ScriptRunner::script[] = {
    CODE_RATE, 20,
    CODE_HSCROLL, 5, 'H', 'e', 'l', 'l', 'o',
    CODE_LEFT, 5, 'W', 'o', 'r', 'l', 'd',
    CODE_SLEEP, 0x03, 0xE8,
    CODE_BITMAP, 0x00, 0x00, 0x00, 0x00, 0x00, 0x04, 0x0c, 0x14, 0x28, 0x38, 0x48,
        0x70, 0x90, 0xf7, 0x97, 0xf0, 0x97, 0xf7, 0x90, 0x70, 0x48, 0x38,
        0x28, 0x14, 0x0c, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    CODE_SLEEP, 0x03, 0xE8,
    CODE_HSCROLL, 1, ' ', // length=0 doesn't work (it should though)
    CODE_END
};
*/

void ScriptRunner::run() {
    uint8_t command;
    const uint8_t* pos = script;
    while (true) {
        command = *(pos++);
        if (command == CODE_END) {
            pos = script;
            break;
        }

        switch (command) {
        case CODE_RATE:
            runner.set_delay(*(pos++));
            break;
        case CODE_HSCROLL: {
            PString text(pos++);
            HScrollEffect effect(runner.get_display(), font_jiffy, text, true);
            runner.show(effect);
            pos += text.size();
        } break;
        case CODE_LEFT: {
            PString text(pos++);
            LeftEffect effect(runner.get_display(), font_jiffy, text);
            runner.show(effect);
            pos += text.size();
        } break;
        case CODE_SLEEP: {
            uint16_t cycles = *(pos++);
            cycles <<= 8;
            cycles |= *(pos++);
            cycles /= runner.get_delay();
            DelayEffect effect(runner.get_display(), cycles);
            runner.show(effect);
        } break;
        case CODE_BITMAP: {
            BitmapEffect effect(runner.get_display(), pos);
            runner.show(effect);
            pos += 32;
        } break;
        }
    }
}
