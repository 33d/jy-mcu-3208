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
public:
    uint8_t script[512];
    ScriptRunner(Runner& runner): runner(runner) {};
    void run();
};

#endif /* SCRIPTRUNNER_H_ */
