/*
 * console.cpp
 *
 *  Created on: Dec 5, 2024
 *      Author: rbauer
 */

#include "Arduino.h"
#include "console.h"

void consoleInit()
{
	Serial.begin(115200);
}

void consoleDisplayArgs(const char * format, ... )
//void consoleDisplay(const char* pMsg)
{
	static char buffer[40];
	va_list args;
	va_start (args, format);
	vsnprintf (buffer, 40, format, args);
	buffer[39] = 0;
	va_end (args);
	Serial.println(buffer);
}

void consoleDisplay(const char* pMsg)
{
	Serial.println(pMsg);
}

uint8_t consoleInputReady()
{
    return( Serial.available() );
}

uint8_t consoleReadByte()
{
    return( Serial.read() );
}
