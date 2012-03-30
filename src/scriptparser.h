/*
 * scriptparser.h
 *
 *  Created on: 24/03/2012
 *      Author: damien
 */

#ifndef SCRIPTPARSER_H_
#define SCRIPTPARSER_H_

#include "scriptrunner.h"
#include "commands.h"

class ScriptParser {
private:
    enum State {
        COMMAND,
        TEXT,
        IGNORE,
        DONE
    };
    State state;
    // our working buffer
    char buf[100];
    // the pointer into buf
    char* buf_pos;
    uint8_t* const script_buffer;
    // the pointer into scriptrunner's buffer
    uint8_t* script_pos;
    // this points to FLASH not RAM
    const Command* current_command;
    const Command* find_command_code();
    void process_command(char c);
    void commit();
public:
    ScriptParser(uint8_t* script_buffer): state(COMMAND), buf_pos(buf),
            script_buffer(script_buffer), script_pos(script_buffer),
            current_command(0) {};
    void parse(const char c);

#if defined(CPPUNIT_ASSERT)
    friend class ScriptParserTest;
#endif
};

#endif /* SCRIPTPARSER_H_ */
