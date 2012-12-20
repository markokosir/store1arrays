/***********************************
*
*       file.c
*
***********************************/

#include "file.h"

int NumProd(const char *file_name)
{
        char x;
        int taken = 0;
        int f = 0;

        FILE *t;

        t = fopen(file_name, "r");
        if(t == NULL)
        {
                return 0;
        }
        //check number of products in a memory
        for(f = 0; f < MAX_PRODUCT; f++)
        {
                if(product[f]->status == TAKEN)
                {
                        taken++;
                        //memory full
                        if(taken == 99)
                        {
                                fclose(t);
                                return 1;
                        }
                }
        }
        //check number of products in a database
        while((x = fgetc(t)) != EOF)
        {
                if(x  == '\n')
                {
                        taken++;
                        //to many products in a database
                        if(taken > 99)
                        {
                                fclose(t);
                                return 2;
                        }
                }
        }
        fclose(t);
        return 3;
}

int CheckExist(const char *file_name)
{
        FILE *d;

        d = fopen(file_name, "r");
        if(d == NULL)
        {
                return 0;
        }
        else
        {
                fclose(d);
                return 1;
        }
}

void SaveProd(void)
{
        int h = 0;
        int j = 0;
        int e = 0;
        int q = 0;
        char file_name[20];
        char option;

        FILE *p;

        change:;
        SetCursorType(NORMAL_CURSOR);
        ClrScr();
        printf("SAVE\n\n");
        printf("Save as: ");
        GetStr(file_name, 15);
        for(j = 0; j < 17; j++)
        {
                if(file_name[j] == 0)
                {
                        file_name[j] = '.';
                        file_name[j+1] = 't';
                        file_name[j+2] = 'x';
                        file_name[j+3] = 't';
                        file_name[j+4] = 0;
                        break;
                }
        }
        e = CheckExist(file_name);
        if(e == 1)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s already exist, do you want to replace it?(Y/N)", file_name);
                option = getch();
                if(option == 'Y' || option == 'y')
                {
                        goto overwrite;
                }
                else
                {
                        goto change;
                }
        }
        else
        {
                overwrite:;
                p = fopen(file_name, "w");
                if(p == NULL)
                {
                        SetCursorType(NO_CURSOR);
                        ClrScr();
                        printf("File %s can not be opened!", file_name);
                        getch();
                }
                //save products in a database
                else
                {
                        for(h = 0; h < MAX_PRODUCT; h++)
                        {
                                if(product[h]->status == TAKEN)
                                {
                                        for(q = 0; product[h]->product_name[q] != 0; q++)
                                        {
                                                if(product[h]->product_name[q] == ' ')
                                                {
                                                        product[h]->product_name[q] = '_';
                                                }
                                        }
                                        fprintf(p, "%16s\t%d\t%f\t%d\n",product[h]->product_name, product[h]->code, product[h]->price, product[h]->supply);
                                        for(q = 0; product[h]->product_name[q] != 0; q++)
                                        {
                                                if(product[h]->product_name[q] == '_')
                                                {
                                                        product[h]->product_name[q] = ' ';
                                                }
                                        }
                                }
                        }
                z = 1;
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s saved!", file_name);
                getch();
                }
        fclose(p);
        }
        SetCursorType(NORMAL_CURSOR);
}

void LoadProd(void)
{
        int i = 0;
        int j = 0;
        int r = 0;
        int q = 0;
        int v = 0;
        char choice;
        char file_name[20];

        FILE *k;

        ClrScr();
        printf("LOAD\n\n");
        printf("Open file: ");
        GetStr(file_name, 15);
        for(j = 0; j < 17; j++)
        {
                if(file_name[j] == 0)
                {
                        file_name[j] = '.';
                        file_name[j+1] = 't';
                        file_name[j+2] = 'x';
                        file_name[j+3] = 't';
                        file_name[j+4] = 0;
                        break;
                }
        }
        //enough free memory to load a database?
        r = NumProd(file_name);
        if(r == 0)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s can not be opened!\n", file_name);
                getch();
        }
        else if (r == 1)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("Loading failed - memory full!");
                getch();
        }
        else if(r == 2)
        {
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("Loading failed - to many products in file!");
                getch();
        }
        else
        {
                k = fopen(file_name, "r");
                ClrScr();

                back:;
                if(product[i]->status == FREE)
                {
                        while(fscanf(k, "%16s\t%d\t%f\t%d\n", product[i]->product_name, &product[i]->code, &product[i]->price, &product[i]->supply) == 4)
                        {
                                for(q = 0; product[i]->product_name[q] != 0; q++)
                                {
                                        if(product[i]->product_name[q] == '_')
                                        {
                                                product[i]->product_name[q] = ' ';
                                        }
                                }
                                //check if there are any duplicates
                                for(v = 0; v < MAX_PRODUCT; v++)
                                {
                                        if((product[i]->code == product[v]->code) && (product[v]->status == TAKEN))
                                        {
                                                printf("-------------------------------------------------------------\n");
                                                printf("Code %d already exist.\n", product[i]->code);
                                                printf("Current product: %s, %d, %.2f, %d\n", product[v]->product_name, product[v]->code, product[v]->price, product[v]->supply);
                                                printf("Product from file (%s): %s, %d, %.2f, %d\n", file_name, product[i]->product_name, product[i]->code, product[i]->price, product[i]->supply);
                                                printf("Replace current product?(Y/N)\n");
                                                choice = getch();
                                                //replace a product with the new one
                                                if(choice == 'Y' || choice == 'y')
                                                {
                                                        product[v]->status = FREE;
                                                        product[i]->status = TAKEN;
                                                        break;       
                                                }
                                                //do not insert current product
                                                else
                                                {
                                                        product[i]->status = FREE;
                                                        goto next_prod;
                                                }
                                        }
                                }
                                product[i]->status = TAKEN;
								next_prod:;
								i++;
								goto back;
                        }
                }
                else
                {
                        i++;
                        goto back;
                }
                z = 0;
                SetCursorType(NO_CURSOR);
                ClrScr();
                printf("File %s successfully loaded!", file_name);
                getch();
                fclose(k);
        }
        SetCursorType(NORMAL_CURSOR);
}

void CheckSave(const int save)
{
        char option;
		COORD scrCoordinates = {0};

		scrCoordinates.X = 30;
		scrCoordinates.Y = 10;
		
        if(save == 0)
        {
                ClrScr();
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), scrCoordinates);
                printf("Save changes?(Y/N)");
                option = getch();
                if(option == 'Y' || option == 'y')
                {
                        SaveProd();
                }
        }
}