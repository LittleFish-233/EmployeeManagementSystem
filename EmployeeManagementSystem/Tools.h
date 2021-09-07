#ifndef  __TOOLS_H__

#define   __TOOLS_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void RepeatOutput(const char char_, int frequency, bool isLineFeed);
void CenterOutput(const char* chars, int length, double parameter, bool if_LineFeed);
void OutputOption(const char* chars[], int optionNum, int length, int Columns, double* parameters, bool if_LineFeed);
void OutputTable(const char** chart[], int hang, int lie, double* parameters[], bool if_LineFeed);
char* itoa(long long src);



#endif
