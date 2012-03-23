/*
 * scriptrunner.h
 *
 *  Created on: 23/03/2012
 *      Author: damien
 */

#ifndef SCRIPTRUNNER_H_
#define SCRIPTRUNNER_H_

#include <stdint.h>
#include "runner.h"

class ScriptRunner {
private:
    Runner& runner;
    static uint8_t script[];
    uint8_t* pos;
public:
    ScriptRunner(Runner& runner): runner(runner), pos(&script[0]) {};
    void run();
};

#endif /* SCRIPTRUNNER_H_ */
