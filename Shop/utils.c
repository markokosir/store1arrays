/***********************************
*
*       utils.c
*
***********************************/

#include "utils.h"
                        
///////////////////////////////////////////////////////////////////////////////
/*
 *  remove new line character from a string, if there is any return 0 or
 *  else return 1
 */
int RemoveNewLine(char *str)
{
        char *p;

        if((p = strchr(str, '\n')))
        {
				*p = 0;
                return 0;
        }
        return 1;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
 *  clear an input buffer
 */
void ClrBuf(void)
{
        int ch;

        while((ch = getchar()) != '\n' && ch != EOF);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
 *  get a string from user, add space for a null character
 *  and remove new line character if there is any or else clear the buffer  
 */
void GetStr(char *str,const unsigned int str_len)
{
        fgets(str, (str_len + 1), stdin);
        if(RemoveNewLine(str) == 1)
        {
                ClrBuf();
        }
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
 *  get a string(number) from user, test number of characters(width) and cast
 *  it into a number, if input is invalid return NULL or else return 1
 */
int GetNum(const char *format, const void *variable, unsigned int width)
{
        int i;
        char temp[7];

        for(i = 0; format[i] != 0; i++)
        {
                if(format[i] == '%')
                {
                        i++;
                        //check if is an integer
                        if(format[i] == 'd')
                        {
                                if(width > 5)
                                {
                                        width = 5;
                                }
                                fgets(temp, (width + 1), stdin);
                                if(RemoveNewLine(temp) == 1)
                                {
                                        ClrBuf();
                                }
                                if(sscanf(temp, "%d", variable) != 1)
                                {
                                        printf("Invalid input!\n");
                                        printf("Press Enter to continue . . .");
                                        getchar();
                                        return NULL;
                                }
                        }
                        //check if is a float
                        if(format[i] == 'f')
                        {
                                if(width > 6)
                                {
                                        width = 6;
                                }
                                fgets(temp, (width + 1), stdin);
                                if(RemoveNewLine(temp) == 1)
                                {
                                        ClrBuf();
                                }
                                if(sscanf(temp, "%f", variable) != 1)
                                {
                                        printf("Invalid input!\n");
                                        printf("Press Enter to continue . . .");
                                        getchar();
                                        return NULL;
                                }
                        }
                }
        }
        return 1;          
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
 *  move a string for one character(in left)
 */
void MoveStr(char *str, const char first_char)
{
	int i;

	for(i=1; str[i] != 0; str++)
	{
		str[i-1] = str[i];
	}
	//first character becomes last
	str[i-1] = first_char;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/*
 *  force program to stop for certain miliseconds
 */
void Delay(clock_t mili_seconds)
{
        clock_t end_time = 0;

        end_time = clock () + mili_seconds;
        while (clock () < end_time);
}
///////////////////////////////////////////////////////////////////////////////