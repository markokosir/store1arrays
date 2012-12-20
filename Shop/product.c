/***********************************
*
*       product.c
*
***********************************/

#include "product.h"

void EnterProd(void)
{
        int j = 0;
        int k = 0;
        int code;
        char option;

        do
        {  
                begin_input:;
				SetCursorType(NORMAL_CURSOR);
                ClrScr();
                //find free location and enter a product
                for(j = 0; j < 100; j++)
                {        
                        if(product[j]->status == FREE)
                        {
                                z = 0;
                                printf("ENTER PRODUCT\n\n");
                                printf("Product: ");
                                GetStr(product[j]->product_name, 13);
                                printf("Code: ");
                                if(GetNum("%d" ,&code, 5) == NULL)
                                {
                                        goto begin_input;
                                }
                                //check if a code already exist
                                for(k = 0; k < MAX_PRODUCT; k++)
                                {
                                        if((product[k]->code == code) && (product[k]->status == TAKEN))
                                        {
                                                printf("Code %d already exist.", code);
                                                getch();
                                                goto begin_input;
                                        }
                                }
                                product[j]->code = code;
                                printf("Price: ");
                                if(GetNum("%f" , &product[j]->price, 4) == NULL)
                                {
                                        goto begin_input;
                                }
                                printf("Supply: ");
                                if(GetNum("%d", &product[j]->supply, 5) == NULL)
                                {
                                        goto begin_input;
                                }
                                product[j]->status = TAKEN;
                                printf("Enter another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
                if(j == MAX_PRODUCT)
                {
                        //turn off cursor
                        SetCursorType(NO_CURSOR);
                        ClrScr();
                        printf("Memory full!");
                        getch();
                        option = 'n';
                }
        }while(option == 'Y' || option == 'y');
}

void DeleteProd(void)
{
        int j = 0;
        char option;
        int code;

        do
        {
                begin_input:;
                ClrScr();
                printf("DELETE PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" ,&code, 5) == NULL)
                {
                        goto begin_input;
                }
                //find and delete a product
                for(j = 0; j < MAX_PRODUCT; j++)
                {
                        if(product[j]->code == code)
                        {
                                z = 0;
                                product[j]->code = 0;
                                product[j]->status = FREE;
                                printf("Product has been deleted.\n\n");
                                printf("Delete another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
                if(j == MAX_PRODUCT)
                {
                        printf("Code %d doesn't belong to any product.\n", code);
                        printf("Delete another product?(Y/N)");
                        option = getch();
                }
        }while(option == 'Y' || option == 'y');
}

void FindProd(void)
{
        int j = 0;
        int code;
        char option;

        do
        {
                begin_input:;
                ClrScr();
                printf("FIND PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" ,&code, 5) == NULL)
                {
                        goto begin_input;
                }
                //find and display a product
                for(j = 0; j < MAX_PRODUCT; j++)
                {
                        if(product[j]->code == code  && product[j]->status == TAKEN)
                        {
                                printf("%s, %.2f €,  %d pieces.\n\n", product[j]->product_name, product[j]->price, product[j]->supply);
                                printf("Find another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
                if(j == MAX_PRODUCT)
                {
                        printf("Code %d doesn't belong to any product.\n", code);
                        printf("Find another product?(Y/N)");
                        option = getch();
                }
        }while(option == 'Y' || option == 'y');
}

void SellProd(void)
{
        int j = 0;
        int code;
        char option;

        do
        {
                begin_input:;
                ClrScr();
                printf("SELL PRODUCT\n\n");
                printf("Code: ");
                if(GetNum("%d" ,&code, 5) == NULL)
                {
                        goto begin_input;
                }
                //find and decrement a product supply
                for(j = 0; j < MAX_PRODUCT; j++)
                {
                        if(product[j]->code == code)
                        {
                                if(product[j]->supply == 0)
                                {
                                        printf("This product is not available.\n\n");
                                        printf("Sell another product?(Y/N)");
                                        option = getch();
                                        break;
                                }
                                z = 0;
                                product[j]->supply--;
                                printf("Product sold.\n");
                                printf("Supply: %d\n\n", product[j]->supply);
                                printf("Sell another product?(Y/N)");
                                option = getch();
                                break;
                        }
                }
                if(j == MAX_PRODUCT)
                {
                        printf("Code %d doesn't belong to any product.\n", code);
                        printf("Sell another product?(Y/N)");
                        option = getch();
                }
        }while(option == 'Y' || option == 'y');

}

void DisplayProd(void)
{
        int k = 0;
        int num_prod = 0;

        SetCursorType(NO_CURSOR);
        ClrScr();
        printf("DISPLAY ALL PRODUCTS\n\n");
        printf("|       Product|  Code|     Price|       Supply|\n");
        printf("------------------------------------------------\n");
        for(k = 0; k < MAX_PRODUCT; k++)
        {
                if(product[k]->status == TAKEN)
                {
                        num_prod++;
                        printf("| %13s| %5d| %7.2f €| %5d pieces|\n", product[k]->product_name, product[k]->code, product[k]->price, product[k]->supply);
                }
        }
        printf("\nTotal number of products: %d", num_prod);
        getch();
        SetCursorType(NORMAL_CURSOR);
}

void SortProd(void)
{
		//well, why would I keep it simple, I made a sort function that really plays around with arrays ;)
        int i = 0;
        int j = 0;
        int k = 0;
        int sort = 0;
        struct goods temp;
        char temp_name1[14];
        char temp_name2[14];

        SetCursorType(NO_CURSOR);
        ClrScr();
        //sort products alphabetical
        do
        {
                sort = 0;
                for(i = 1; i < MAX_PRODUCT; i++)
                {
                        strcpy(temp_name1, product[i-1]->product_name);
                        strcpy(temp_name2, product[i]->product_name);
                        for(j = 0; temp_name1[j] != 0; j++)
                        {
                                temp_name1[j] = toupper(temp_name1[j]);
                        }
                        for(k = 0; temp_name2[k] != 0; k++)
                        {
                                temp_name2[k] = toupper(temp_name2[k]);
                        }
                        if((strcmp(temp_name1, temp_name2) > 0) && product[i-1]->status == TAKEN && product[i]->status == TAKEN)
                        {
                                temp = *product[i-1];
                                *product[i-1] = *product[i];
                                *product[i] = temp;
                                sort = 1;
                        }
                }
        }while(sort == 1);
        printf("Products sorted.");
        getch();
}

int KeyPress(void)
{
        int key = getch();

        if(key == 0 || key == 224)
        {
                key = 256 + getch();
        }
        return key;
}

int Menu(void)
{
		//this is probably the most fancy menu that I ever came up with
        int j = 0;
        int i = 0;
        int key;
        char shop[] = "                                  *** STORE ***                                  ";
        char display[9][30] = {{"* Enter product"},
                               {"  Delete product"},
                               {"  Find product"},
                               {"  Sell product"},
                               {"  Display all products"},
                               {"  Sort products"},
                               {"  Load"},
                               {"  Save"},
                               {"  Exit"}};

        //display menu
        while(1)
        {
                Delay(50);
				ShowCursor(0);
                ClrScr();
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0);
                SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE), BACKGROUND_BLUE);
                printf("--------------------------------------------------------------------------------");
                //move text every 100 miliseconds
                if(j == 2)
                {
                        MoveStr(shop, shop[0]);
                        printf("%s", shop);
                        j = 0;
                }
                else
                {
                        printf("%s", shop);
                        j++;
                }
                printf("--------------------------------------------------------------------------------");
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_RED | FOREGROUND_INTENSITY));
				printf("\n\n\n");
                puts(display[0]);
                puts(display[1]);
                puts(display[2]);
                puts(display[3]);
                puts(display[4]);
                puts(display[5]);
                puts(display[6]);
                puts(display[7]);
                puts(display[8]);
                if(kbhit())
                {
                        key = KeyPress();
                        //change star location - up
                        if(key == ARROW_UP)
                        {
                                for(i = 0; i < 9; i++)
                                {
                                        if(display[i][0] == '*')
                                        {
                                                if( i == 0)
                                                {
                                                        i = 8;
                                                        display[0][0] = ' ';
                                                        display[8][0] = '*';
                                                        break;
                                                }
                                                display[i][0] = ' ';
                                                display[i-1][0] = '*';
                                                i--;
                                                break;
                                        }
                                }
                        }
                        //change star location - down
                        else if(key == ARROW_DOWN)
                        {
                                for(i = 0; i < 9; i++)
                                {
                                        if(display[i][0] == '*')
                                        {
                                                if(i == 8)
                                                {
                                                        i = 0;
                                                        display[8][0] = ' ';
                                                        display[0][0] = '*';
                                                        break;
                                                }
                                                display[i][0] = ' ';
                                                display[i+1][0] = '*';
                                                i++;
                                                break;
                                        }
                                }
                        }
                        //return star location
                        else if(key == RETURN)
                        {
                                return i;
                        }
                }
        }
}

void ClrScr(void)
{
		//get the top left position
	    COORD scrCoordinates = {0};                        
	    //visible characters
	    DWORD charsLenght;
	    DWORD d;                      
	    CONSOLE_SCREEN_BUFFER_INFO buff;

	    //get a handle to the console
	    HANDLE scrHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	    GetConsoleScreenBufferInfo(scrHandle, &buff);

	    //get number of characters
	    charsLenght = buff.dwSize.X * buff.dwSize.Y;

	    //put whitespaces into the screen buffer
	    FillConsoleOutputCharacter(scrHandle, TEXT(' '), charsLenght, scrCoordinates, &d);
	    GetConsoleScreenBufferInfo(scrHandle, &buff);
	    FillConsoleOutputAttribute(scrHandle, buff.wAttributes, charsLenght, scrCoordinates, &d);

	    //put cursor back to the top left position
	    SetConsoleCursorPosition(scrHandle, scrCoordinates);
}

void SetCursorType(int cursor)
{
	CONSOLE_CURSOR_INFO cursorInfo = {0};

	//show cursor
	if(cursor)
	{
		cursorInfo.dwSize = 30;
		cursorInfo.bVisible = TRUE;
		SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cursorInfo);		
	}
	//hide cursor
	else 
	{
		cursorInfo.dwSize = 100;
		cursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo (GetStdHandle (STD_OUTPUT_HANDLE), &cursorInfo);
	}
}