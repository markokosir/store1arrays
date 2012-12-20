/***********************************
*
*       product.h
*
***********************************/

#ifndef PRODUCT_H
#define PRODUCT_H

#include "main.h"

#define ARROW_UP 328    
#define ARROW_DOWN 336
#define RETURN 13
#define NORMAL_CURSOR 1
#define NO_CURSOR 0

//function prototypes
void EnterProd(void);
void DeleteProd(void);
void FindProd(void);
void SellProd(void);
void DisplayProd(void);
void SortProd(void);
int KeyPress(void);
int Menu(void);
void ClrScr(void);
void SetCursorType(int cursor);

#endif //PRODUCT_H