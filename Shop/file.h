/***********************************
*
*       file.h
*
***********************************/

#ifndef FILE_H
#define FILE_H

#include "main.h"

//function prototypes
int NumProd(const char *file_name);
int CheckExist(const char *file_name);
void SaveProd(void);
void LoadProd(void);
void CheckSave(const int save);

#endif //FILE_H