#include "display.h"
#include "effect.h"

const char* text = "001100110011";

int main(void) {

    Display display;
    HScrollEffect effect(30);

    while (1) {
        display.show(text, effect);
    }

    return(0);
}
