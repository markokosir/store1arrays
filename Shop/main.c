/********************************************************************************************************
Program: Store 1 - Arrays
Author: Marko Kosir

Store 1 is implemented using arrays. When the program starts it allocates memory on heap and gives 100 possibly 
entries of products.

Files included:
                - products.txt				sample database
                - codes.txt					codes for products
                - main.h & main.c			heart of a program
                - product.h & product.c		general functions for working with products
                - file.h & file.c			functions for working with files
                - utils.h & utils.c			utilities functions

Note: All the code is written in pure C programming language, however header file conio.h is
      inlcuded in this program(windows.h is also included for rendering reasons), which is 
      not part of ANSI C standard.

Tested - Windows XP
Compiled - Microsoft Visual Studio 2005

Released: July 8th, 2005

Upgrade log:
ported to MVS 2010  (18.9.2010)
********************************************************************************************************/
#include "main.h"

goods *product[MAX_PRODUCT];
int z = 1;

int main()
{
        int i = 0;
        int q = 0;
        int value;//star location

        //alocate memory
        for(i = 0; i < MAX_PRODUCT; i++)
        {
                product[i] = (struct goods *)malloc(sizeof(struct goods));
                if (product[i] == NULL)
                {
						SetCursorType(NO_CURSOR);
						ClrScr();
                        printf("Not enough memory!");
                        getch();
                        goto out;
                }
                product[i]->status = FREE;
        }
        //save some products in memory
        strcpy(product[0]->product_name, "CHOCOLATE");
        product[0]->code = 567;
        product[0]->price = 1.5;
        product[0]->supply = 30;
        product[0]->status = TAKEN;
        strcpy(product[1]->product_name, "JUICE");
        product[1]->code = 121;
        product[1]->price = 2.39;
        product[1]->supply = 30;
        product[1]->status = TAKEN;
        strcpy(product[2]->product_name, "MILK");
        product[2]->code = 123;
        product[2]->price = 2;
        product[2]->supply = 30;
        product[2]->status = TAKEN;
        strcpy(product[3]->product_name, "APPLES");
        product[3]->code = 852;
        product[3]->price = 1.25;
        product[3]->supply = 30;
        product[3]->status = TAKEN;

        do
        {
                value = Menu();
				SetCursorType(NORMAL_CURSOR);
                switch(value)
                {
                        case 0: EnterProd();
                                break;
                        case 1: DeleteProd();
                                break;
                        case 2: FindProd();
                                break;
                        case 3: SellProd();
                                break;
                        case 4: DisplayProd();
                                break;
                        case 5: SortProd();
                                break;
                        case 6: LoadProd();
                                break;
                        case 7: SaveProd();
                                break;
                        case 8: CheckSave(z);
                                break;
                }
        }while(value != 8);

        out:;
        //free memory
        for(q = 0 ; q < i; q++)
        {/////////////////////////////
                free(product[q]);
        }

        return 0;
}
