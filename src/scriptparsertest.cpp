#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cstring>
#include <stdint.h>
#include "scriptparser.h"
#include "commands.h"

class ScriptParserTest : public CppUnit::TestFixture {
private:
    CPPUNIT_TEST_SUITE(ScriptParserTest);
    CPPUNIT_TEST(test_no_args);
    CPPUNIT_TEST(test_1_arg);
    CPPUNIT_TEST(test_rate);
    CPPUNIT_TEST(test_sleep);
    CPPUNIT_TEST(test_2_commands);
    CPPUNIT_TEST_SUITE_END();

    void parse(const char* text, const uint8_t* expected, int length) {
        uint8_t script[100];
        ScriptParser parser(script);
        do {
            parser.parse(*text);
        } while (*(text++) != '\0');
        CPPUNIT_ASSERT(ScriptParser::IGNORE != parser.state);
        CPPUNIT_ASSERT_EQUAL(0, std::memcmp(script, expected, length));
    }

public:
    void test_no_args() {
        uint8_t e1[] = { CODE_END };
        parse("end", e1, sizeof(e1));
    }

    void test_1_arg() {
        uint8_t e1[] = { CODE_HSCROLL, 5, 'h', 'e', 'l', 'l', 'o' };
        parse("hscroll hello", e1, sizeof(e1));
    }

    void test_rate() {
        uint8_t e1[] = { CODE_RATE, 18 };
        parse("rate 18", e1, sizeof(e1));
    }

    void test_sleep() {
        uint8_t e1[] = { CODE_SLEEP, 0, 0 };
        // The byte order depends on the platform
        *((uint16_t*) &e1[1]) = 1000;
        parse("sleep 1000", e1, sizeof(e1));
    }

    void test_2_commands() {
        uint8_t e1[] = { CODE_RATE, 2, CODE_HSCROLL, 1, 'a', CODE_END };
        parse("rate 2\nhscroll a\nend", e1, sizeof(e1));
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(ScriptParserTest);
