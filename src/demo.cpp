#include "display.h"
#include "effects/hscroll.h"
#include "runner.h"
#include "scriptrunner.h"
#include "fonts/jiffy.h"

int main(void) {

    Display display;
    Runner runner(display);
    ScriptRunner scriptRunner(runner);

    while (1)
        scriptRunner.run();

    return(0);
}
