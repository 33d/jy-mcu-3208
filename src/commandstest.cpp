#include <cppunit/TestFixture.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestSuite.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cstring>
#include <stdint.h>

extern uint8_t* string_to_pstring(const char* src, uint8_t* dest);

class CommandsTest : public CppUnit::TestFixture {
private:
    CPPUNIT_TEST_SUITE(CommandsTest);
    CPPUNIT_TEST(test_string_to_pstring);
    CPPUNIT_TEST_SUITE_END();
public:
    void test_string_to_pstring() {
        uint8_t buf[100];

        string_to_pstring("", buf);
        CPPUNIT_ASSERT_EQUAL(std::memcmp("\0", buf, 1), 0);

        string_to_pstring("a", buf);
        CPPUNIT_ASSERT_EQUAL(std::memcmp("\1a", buf, 2), 0);
    }
};

CPPUNIT_TEST_SUITE_REGISTRATION(CommandsTest);
