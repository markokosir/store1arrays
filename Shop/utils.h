/***********************************
*
*       utils.h
*
*  This file defines utilities functions, all functions are written in ANSI C standard.
*
*  This code is in the public domain, it was written completely and 
*  entirely by Marko Kosir, feel free to use this code or change it 
*  in any way you like.
*
*  Questions, comments & bugs report to kosir.mar@gmail.com
*
*  Author: Marko Kosir
*  Last modified: July 3rd, 2005
***********************************/

#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <string.h>
#include <time.h>

//function prototypes
int RemoveNewLine(char* str);
void ClrBuf(void);
void GetStr(char *str,const unsigned int str_len);
int GetNum(const char *format, const void *variable, unsigned int width);
void MoveStr(char *str, const char first_char);
void Delay(clock_t mili_seconds);

#endif //UTILS_H