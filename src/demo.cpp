#include "display.h"
#include "effects/hscroll.h"
#include "runner.h"
#include "fonts/jiffy.h"

const char* text = "The quick brown fox jumps over the lazy dog $12.34 07:45";

int main(void) {

    Display display;
    Runner runner(display);

    while (1) {
        Effect* effect = new HScrollEffect(display, font_jiffy, text, true);
        runner.show(*effect);
        delete effect;
    }

    return(0);
}
