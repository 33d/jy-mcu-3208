#include "display.h"
#include "effect.h"
#include "fonts/jiffy.h"

const char* text = "The quick brown fox jumps over the lazy dog $12.34 07:45";

int main(void) {

    Display display;

    while (1) {
        Effect* effect = new HScrollEffect(font_jiffy, text, true);
        display.show(*effect);
        delete effect;
    }

    return(0);
}
