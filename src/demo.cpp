#include "display.h"
#include "effects/hscroll.h"
#include "runner.h"
#include "scriptparser.h"
#include "fonts/jiffy.h"

int main(void) {

    Display display;
    Runner runner(display);
    ScriptRunner scriptRunner(runner);
    const char* message = "hscroll Hello!!!";

    ScriptParser parser(scriptRunner.script);
    char* c = const_cast<char*>(message);
    // make sure the null at the end is passed in
    do {
        parser.parse(*c);
    } while (*(c++) != 0);

    while (1) {
        scriptRunner.run();
    }

    return(0);
}
