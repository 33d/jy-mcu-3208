/*
 * Stuff to get C++ features working on the AVR.
 * See http://www.avrfreaks.net/index.php?name=PNphpBB2&file=viewtopic&p=410870
 */

#include <stdlib.h>

void * operator new(size_t size)
{
  return malloc(size);
}

void operator delete(void * ptr)
{
  free(ptr);
}

extern "C" void __cxa_pure_virtual(void) {};
