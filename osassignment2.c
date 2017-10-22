/* 
Siddharth Agarwal
UTA ID 1001577570
CSE 3320-001 Operating Systems
*/

/*References: 
	1. https://stackoverflow.com/questions/28536150/how-to-sort-data-inside-txt-files-in-c
	2. https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file
*/

// write a program to implement bubble or insertion sort 

// to do
//  1 split the file in to smaller chunks of 1000 lines 
// 		by the split function
// 2. sort each file chunk in parallel in the c program
// 		(either by processes or concurrency) ? 
// 		
// merge sort these smaller chunks and get the final sorted file
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>

#define MAX_LEN 10000 // Length of each line in input file.

struct File
{
    char *strFileName;    
    char *strFileSummary;
    char strTempData[MAX_LEN]; 
	char **strData; // String List	

    int noOfLines;

    FILE * ptrFileLog;
    FILE * ptrSummary;

	char *latitude1;
	char *latitude2;
	char strDataCopy[10000];
	char strDataPlus1[10000];
	// int count;

	// char data[count][2];
	// char **temp3;			    
};

struct File *File_create(char *strFileName, char *strFileSummary)
{
	struct File *E = malloc(sizeof(struct File));

	E->strFileName = strdup(strFileName);
	E->strFileSummary = strdup(strFileSummary);
	E->strData 	= NULL;
	// E->strTempData[] = ;
    E->ptrFileLog = NULL;
    E->ptrSummary = NULL;

    // E->count = countlines(E->strFileName);
	// char **temp3[1024];

    E->noOfLines = 0;	

	return E;

}

void File_destory(struct File *E)
{
	assert(E != NULL);

	// free(who->name);
	free(E);
}

void Error_print(char * variableName)
{
	fprintf(stderr,"Error: Could not open %s\n",variableName);	
}

int countlines(char *filename)
{
  // count the number of lines in the file called filename 
	FILE *fp = fopen(filename,"r");
	int ch=0;
	int lines=0;
	// printf("variable value : %c \n", filename);

	if (fp == NULL)
		return 0;

	lines++;
	while ((ch = fgetc(fp)) != EOF)
	{
	    if (ch == '\n')
		lines++;
	}
	fclose(fp);
	return lines;
}

void Store_temp_data(struct File *E)
{
    int count;

	// printf("variable value : %s \n", E->strFileName);
    count = countlines(E->strFileName);
	// for (int i = 0; i < count; ++i)
	// {
    while((fgets(E->strTempData, MAX_LEN, E->ptrFileLog) != NULL) && E->noOfLines < count) 
    {	 
	    // Remove the trailing newline character
        if(strchr(E->strTempData,'\n'))
            E->strTempData[strlen(E->strTempData)-1] = '\0';

        E->strData = (char**) realloc(E->strData, sizeof(char**)*(E->noOfLines+1));
        // E->strData = malloc(sizeof(char**)*(E->noOfLines+1));
        
        E->strData[E->noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
        memcpy(E->strData[E->noOfLines], E->strTempData,200 );

// printf("strTempData: %s\n",E->strTempData);
// printf("strTempData: %s\n",E->strData);        
// printf("strData[noOfLines]:%s\n", E->strData[E->noOfLines]);
// printf("%d\n", E->noOfLines);
        E->noOfLines++;
    }
}

// void swap(char *xp, char *yp)
// {
//     int temp = *xp;
//     *xp = *yp;
//     *yp = temp;	
// }

int bubble_sort(struct File *E)
{
    //check for usual errors
    if ( (E->ptrFileLog = fopen(E->strFileName, "r")) == NULL ) 
    {
    	Error_print(E->strFileName);
        return 1;
    }
    if ( (E->ptrSummary = fopen(E->strFileSummary, "a")) == NULL ) 
    {
		Error_print(E->strFileSummary);        
        return 1;
    }    	
	E->ptrFileLog = fopen(E->strFileName, "r");
    // Read and store in a string list.
	Store_temp_data(E);	
    
    int i, j, x;
        // Sort the array.
    for(i= 0; i < (E->noOfLines-1); i++) 
    {    
		// make a copy of i th element of array containing the lines of csv files	
		strcpy(E->strDataCopy, E->strData[i]);
		// make a copy of (i + 1)th element of array containing the lines of csv files		
		if (i < (E->noOfLines-1))
		{
			x=i+1;
			strcpy(E->strDataPlus1, E->strData[x]);				
		} 
    	printf("%s\n", E->strDataPlus1);    	
		E->latitude1 = strtok (E->strDataCopy,",");
		// why is this loop used? Ans: to get latitude 
		for (int i = 1; i < 2; ++i)
			E->latitude1 = strtok (NULL, ",");

    	// printf("%s\n", E->strData[i]);
		// printf ("latitude 1 is %s\n",E->latitude1);
		E->latitude2 = strtok (E->strDataPlus1,",");
		
		// why is this loop used? Ans: to get latitude		
		for (int i = 1; i < 2; i++)
			E->latitude2 = strtok (NULL, ",");

		// printf ("latitude 2 is %s\n",E->latitude2);		
		char temp3[1024];			
        for(j = 0; j < ( E->noOfLines - i - 1); j++) 
        {
    		// if(E->latitude2 != NULL) 
    		// {        
				// if  > 0,  latitude1 > latitude2.
	            if(strcmp(E->latitude1, E->latitude2) > 0) 
	            {
	            	// temp3[1][1] 	= data[j+1][0];
	            	// data[j+1][0] 	= data[j][0];
	            	// data[j][0]		= temp3[1][1];	
					strcpy(temp3,E->strData[j+1]);		        
	                strcpy(*(E->strData+(j+1)), *(E->strData+j));
                	strcpy(*(E->strData+j), temp3);	                
	            }             
	        // }
        }
    }

	// for (int d = 0; d < count; ++d)
	// {
	// 	/* code */
	// 	// printf ("latitude1: %c\n",(float)data[d][0]);

	// }
    // Write it to outfile. file.
    for(i = 0; i < E->noOfLines; i++)
        fprintf(E->ptrSummary,"%s\n",E->strData[i]);

    // free each string
    for(i = 0; i < E->noOfLines; i++)
        free(E->strData[i]);
    // free string list.
    free(E->strData);
    fclose(E->ptrFileLog);
    fclose(E->ptrSummary);
    return 0;
}

void die(const char *message)
{
    if (errno) {
        perror(message);
    } else {
        printf("ERROR: %s\n", message);
    }

    exit(1);
}

int main(int argc, char *argv[])
{
	// int x;
    // char *strFileName = "./E.csv";
    if (argc < 1)
        die("USAGE: ./osassignment <number of processes>");

    char action = argv[1][0];
    // char action = argv[2][0];
	pid_t child1,child2;

    switch (action) 
    {
        case '1':
        	{
				// int pid = getpid();
			    struct File *E = File_create("./earthquake_test.csv","./earthquake_out.csv");
				bubble_sort(E);

				printf("Parent process id is %d\n", getpid());		
			
	        
	            break;
        	}

        case '2':
			if(!(child1 = fork())){
				// first child
				int pid = getpid();

				// only child process executes this

				printf("Child1 process id is %d\n", pid);
		 		
		        exit(0);
			} 
			else if (!(child2= fork())){
				// second child		
				int pid = getpid();
				// only child2 executes this
				printf("Child2 process id is %d\n", pid);
		        exit(0);		
			}
            break;

        case '4':

            break;

        // case '10': 

        //     break;
        default:
        	printf("%c\n", action);
            die("Invalid action: 1=1 processs, 2=2 processs, 4=4 processs, 10=10 processs");
    }    




    return 0;	
}