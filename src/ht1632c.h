/*
 * ht1632c.h
 *
 *  Created on: 18/03/2012
 *      Author: damien
 */

#ifndef HT1632C_H_
#define HT1632C_H_

#include <stdint.h>

#if defined(__cplusplus)
extern "C" {
#endif

extern uint8_t* HTleds;
extern void HTsetup();
extern void HTpinsetup();
extern void HTbrightness(uint8_t brightness);
extern void HTsendscreen(void);

#if defined(__cplusplus)
}
#endif

#endif /* HT1632C_H_ */
