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

void consoleDisplayArgs(const char * format, ... );
void consoleDisplay(const char* pMsg);
void consoleInit();

#ifdef __cplusplus
}
#endif

#endif /* CONSOLE_H_ */
