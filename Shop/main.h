/***********************************
*
*       main.h
*
***********************************/

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include "product.h"
#include "file.h"
#include "utils.h"

#define MAX_PRODUCT 100 //maximum number of products
#define TAKEN 1         //prevent writing in memory location
#define FREE 0          //make memory location writeable
     
typedef struct goods
{
	char product_name[14];
	int code;
	int supply;
	int status;
	float price;
}goods;

//global variables
extern goods *product[MAX_PRODUCT];
extern int z;//products saved?

#endif //MAIN_H