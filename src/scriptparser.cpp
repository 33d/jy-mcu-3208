/*
 * scriptparser.cpp
 *
 *  Created on: 24/03/2012
 *      Author: damien
 */

#include "scriptparser.h"
#include <string.h>
#if defined(AVR)
#include <avr/pgmspace.h>
#endif
#include "commands.h"

const Command* ScriptParser::find_command_code() {
    const Command* command = commands;
    while (command->name != 0) {
        if (strcmp/*_P*/(buf, command->name) == 0)
            return command;
        ++command;
    }
    return 0;
}

void ScriptParser::process_command(char c) {
    *buf_pos = 0; // terminate the string
    current_command = find_command_code();
    if (current_command == 0)
        state = IGNORE; // command not found
    else {
        *(script_pos++) = current_command->code;
        if (c == ' ') {
            buf_pos = buf;
            state = TEXT;
        } else
            commit(); // command with no data
    }
}

void ScriptParser::commit() {
    *buf_pos = 0; // terminate the string
    CommandParser parser = (CommandParser) current_command->parser;
    if (parser != 0)
        script_pos = parser(buf, script_pos);

    // reset for the next command
    state = COMMAND;
    buf_pos = buf;
}

void ScriptParser::parse(const char c) {
    if (c == '\r' || c == '\n' || c == '\0' || (state == COMMAND && c == ' ')) {
        // end of command or data
        if (state == COMMAND)
            process_command(c);
        else if (state != IGNORE)
            commit();
    } else {
        // append the text, unless we're in IGNORE mode
        if (state != IGNORE)
            *(buf_pos++) = c;
    }
}
