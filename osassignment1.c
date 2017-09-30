/* 
Siddharth Agarwal
UTA ID 1001577570
CSE 3320-001 Operating Systems
*/

/*References: 
	
	# for code between line 22 to line 67

	1. https://www.quora.com/What-is-the-programming-code-of-copying-one-stack-to-another-by-using-C-language
*/


#include <sys/types.h> 
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <time.h>
#include <curses.h>

#define MaxSize 100 //maximum of 100 file or directory names could be stored.
 
int stackA[MaxSize],stackB[MaxSize],stackC[MaxSize];
int sizeA=0,sizeB=0,sizeC=0;
 
void Push(int *stack,int item, int *size)
{
    if((*size)>MaxSize)
    {
        printf("OVERFLOW\n");
    }
    else
    {
        stack[*size] = item;
        (*size)++;
    }
}
 
int Pop(int *stack, int *size)
{
    if( (*size) <= 0 )
    {
        return -1;
    }
    else
    {
        int x = stack[(*size)-1];
        (*size)--;
        return x;
    }
}
 
void copy_A_to_C()
{
    int x;
    while ( sizeA > 0 )  
    {
        x = Pop( stackA, &sizeA);
        Push( stackB, x, &sizeB);
    }
    while ( sizeB > 0 )
    {
        x = Pop( stackB, &sizeB);
        Push( stackC, x, &sizeC);
    }
}

int main(void) {

    pid_t child;
    DIR * d;
    struct dirent * de;
    int i, c, k;
    char s[256], cmd[256];
    time_t t;
    int item;

    while (1) 
    {
        t = time( NULL );	
        printf( "It is now: %s\n", ctime( &t ));

        getcwd(s, 200);/*check for errors? and what does it return if it returns anything */
        printf( "\nCurrent Directory: %s \n", s );

        d = opendir( "." ); /*errors? more below*/
        c = 0;

        while ((de = readdir(d))) 
        {
			// instead of looping directly from the de, save it in a stack or array for backward and forward traversal       
            
            if ((de->d_type) & DT_DIR) //check if it is a directory(DT_DIR)
            {
                // item = strcat(strcat(c,"Directory"), de->d_name);
                printf ( " ( %d Directory: %s ) \n", c++, de->d_name);
	    	    // Push( stackA, item, &sizeA);                
            }

            if ((de->d_type) & DT_REG) //check if it is a regular file (DT_REG)
            {
                // item = strcat(strcat(c,"File"), de->d_name);
                printf ( " ( %d File: %s ) \n", c++, de->d_name);
	    	    // Push( stackA, item, &sizeA);                            
            }

            // keep printing the file/directory names to get 8 listing on the terminal and then ask for user input 
            if( ( c % 8) == 0 ) 
            {
            	// getinput:
	                printf( "Hit N for Next\n"); /*what if only subdirs?*/
	                k = getchar();

	                int *char_k = k;

            }            
        }
        closedir( d );

        printf( "---------------------------------------\n" );
        printf( "Operations: \t Q Quit\n" );
        printf( "\t\t E Edit\n" );
        printf( "\t\t R Run\n" );
        // printf( "\t\t Q Quit\n" );
        printf( "\t\t C Change\n" );                                
        c = getchar( ); 

        // operations:
	        switch (c) 
	        {
	            case 'q' : exit(0); /*quit*/
	            case 'e' : printf( "Edit What? Enter full name:" );
	                        scanf( "%s", s );
	                        strcpy( cmd, "pico ");
	                        strcat( cmd, s );
	                        system( cmd ); 
	                        break;
	            case 'r' : printf( "Run what?: " );
	                        scanf( "%s", cmd );
	                        system( cmd );
	                        break;
	            case 'c' : printf( "Change To?:" );
	                        scanf( "%s", cmd );
	                        chdir( cmd ); 
	                        break;
	        }
    }
}






