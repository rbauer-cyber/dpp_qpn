/*
 * console.h
 *
 *  Created on: Dec 5, 2024
 *      Author: rbauer
 */

#ifndef CONSOLE_H_
#define CONSOLE_H_

#include <stdarg.h>

#ifdef __cplusplus
    extern "C" {
#endif

void consoleInit();
void consoleDisplayArgs(const char * format, ... );
void consoleDisplay(const char* pMsg);
uint8_t consoleInputReady();
uint8_t consoleReadByte();


#ifdef __cplusplus
}
#endif

#endif /* CONSOLE_H_ */
