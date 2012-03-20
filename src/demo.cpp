#include "display.h"
#include "effect.h"
#include "font.h"
#include "fonts/jiffy.h"

const char* text = "The quick brown fox jumps over the lazy dog $12.34 07:45";

int main(void) {

    Display display(font_jiffy);
    HScrollEffect effect(30);

    while (1) {
        display.show(text, effect);
    }

    return(0);
}
