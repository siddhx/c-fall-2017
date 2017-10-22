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
	struct File *earthquake = malloc(sizeof(struct File));

	earthquake->strFileName = strdup(strFileName);
	earthquake->strFileSummary = strdup(strFileSummary);
	earthquake->strData 	= NULL;
	// earthquake->strTempData[] = ;
    earthquake->ptrFileLog = NULL;
    earthquake->ptrSummary = NULL;

    // earthquake->count = countlines(earthquake->strFileName);
	// char **temp3[1024];

    earthquake->noOfLines = 0;	

	return earthquake;

}

void File_destory(struct File *earthquake)
{
	assert(earthquake != NULL);

	// free(who->name);
	free(earthquake);
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

void Store_temp_data(struct File *earthquake)
{
    int count;

	// printf("variable value : %s \n", earthquake->strFileName);
    count = countlines(earthquake->strFileName);
	// for (int i = 0; i < count; ++i)
	// {
    while((fgets(earthquake->strTempData, MAX_LEN, earthquake->ptrFileLog) != NULL) && earthquake->noOfLines < count) 
    {	 
	    // Remove the trailing newline character
        if(strchr(earthquake->strTempData,'\n'))
            earthquake->strTempData[strlen(earthquake->strTempData)-1] = '\0';

        earthquake->strData = (char**) realloc(earthquake->strData, sizeof(char**)*(earthquake->noOfLines+1));
        // earthquake->strData = malloc(sizeof(char**)*(earthquake->noOfLines+1));
        
        earthquake->strData[earthquake->noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
        memcpy(earthquake->strData[earthquake->noOfLines], earthquake->strTempData,200 );

// printf("strTempData: %s\n",earthquake->strTempData);
// printf("strTempData: %s\n",earthquake->strData);        
// printf("strData[noOfLines]:%s\n", earthquake->strData[earthquake->noOfLines]);
// printf("%d\n", earthquake->noOfLines);
        earthquake->noOfLines++;
    }
}

// void swap(char *xp, char *yp)
// {
//     int temp = *xp;
//     *xp = *yp;
//     *yp = temp;	
// }

int bubble_sort(struct File *earthquake)
{
    //check for usual errors
    if ( (earthquake->ptrFileLog = fopen(earthquake->strFileName, "r")) == NULL ) 
    {
    	Error_print(earthquake->strFileName);
        return 1;
    }
    if ( (earthquake->ptrSummary = fopen(earthquake->strFileSummary, "a")) == NULL ) 
    {
		Error_print(earthquake->strFileSummary);        
        return 1;
    }    	
	earthquake->ptrFileLog = fopen(earthquake->strFileName, "r");
    // Read and store in a string list.
	Store_temp_data(earthquake);	
    
    int i, j, x;
        // Sort the array.
    for(i= 0; i < (earthquake->noOfLines-1); i++) 
    {    
		// make a copy of i th element of array containing the lines of csv files	
		strcpy(earthquake->strDataCopy, earthquake->strData[i]);
		// make a copy of (i + 1)th element of array containing the lines of csv files		
		if (i < (earthquake->noOfLines-1))
		{
			x=i+1;
			strcpy(earthquake->strDataPlus1, earthquake->strData[x]);				
		} 
    	printf("%s\n", earthquake->strDataPlus1);    	
		earthquake->latitude1 = strtok (earthquake->strDataCopy,",");
		// why is this loop used? Ans: to get latitude 
		for (int i = 1; i < 2; ++i)
			earthquake->latitude1 = strtok (NULL, ",");

    	// printf("%s\n", earthquake->strData[i]);
		// printf ("latitude 1 is %s\n",earthquake->latitude1);
		earthquake->latitude2 = strtok (earthquake->strDataPlus1,",");
		
		// why is this loop used? Ans: to get latitude		
		for (int i = 1; i < 2; i++)
			earthquake->latitude2 = strtok (NULL, ",");

		// printf ("latitude 2 is %s\n",earthquake->latitude2);		
		char temp3[1024];			
        for(j = 0; j < ( earthquake->noOfLines - i - 1); j++) 
        {
    		// if(earthquake->latitude2 != NULL) 
    		// {        
				// if  > 0,  latitude1 > latitude2.
	            if(strcmp(earthquake->latitude1, earthquake->latitude2) > 0) 
	            {
	            	// temp3[1][1] 	= data[j+1][0];
	            	// data[j+1][0] 	= data[j][0];
	            	// data[j][0]		= temp3[1][1];	
					strcpy(temp3,earthquake->strData[j+1]);		        
	                strcpy(*(earthquake->strData+(j+1)), *(earthquake->strData+j));
                	strcpy(*(earthquake->strData+j), temp3);	                
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
    for(i = 0; i < earthquake->noOfLines; i++)
        fprintf(earthquake->ptrSummary,"%s\n",earthquake->strData[i]);

    // free each string
    for(i = 0; i < earthquake->noOfLines; i++)
        free(earthquake->strData[i]);
    // free string list.
    free(earthquake->strData);
    fclose(earthquake->ptrFileLog);
    fclose(earthquake->ptrSummary);
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
    // char *strFileName = "./earthquake.csv";
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
			    struct File *earthquake = File_create("./earthquake_test.csv","./earthquake_out.csv");
				bubble_sort(earthquake);

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