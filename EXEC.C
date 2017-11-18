/* 
Siddharth Agarwal
UTA ID 1001577570
CSE 3320-001 Operating Systems
*/

/*References: 
	1. https://stackoverflow.com/questions/28536150/how-to-sort-data-inside-txt-files-in-c
	2. https://stackoverflow.com/questions/12733105/c-function-that-counts-lines-in-file

NOTES:
	1. This file contains the sorting function to be called by osassignment2 to sort the contents of the file name passed while calling via exec_() family of functions
*/

#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>
#define MAX_LEN 10000 // Length of each line in input file.

struct File{
	char *FileName;    
	char *FileSummary;
	char TempData[MAX_LEN]; 
	char **Data; // String List	

	int Lines;

	FILE * FileLog;
	FILE * Summary;

	char *latitude1;
	char *latitude2;
	char DataCopy[10000];
	char DataPlus1[10000];		    
};

struct File *File_create(const char *FileName, const char *FileSummary){
	struct File *E 	= (struct File*)malloc(sizeof(struct File));
	E->FileName 	= strdup(FileName);
	E->FileSummary 	= strdup(FileSummary);
	E->Data 		= NULL;
	// E->TempData[] = ;
	E->FileLog 		= NULL;
	E->Summary 		= NULL;
    // E->count = countlines(E->FileName);
	// char **temp3[1024];
	E->Lines 		= 0;	
	return E;
}


void File_destory(struct File *E){
	assert(E != NULL);
	// free(who->name);
	free(E);
}

void Error_print(char * variableName){
	fprintf(stderr,"Error: Could not open %s\n",variableName);	
}

int countlines(char *filename){
  // count the number of lines in the file called filename 
	FILE *fp = fopen(filename,"r");
	int ch=0;
	int lines=0;
	// printf("variable value : %c \n", filename);
	if (fp == NULL){
		return 0;
	}
	lines++;
	while ((ch = fgetc(fp)) != EOF){
		if (ch == '\n')
			lines++;
	}
	fclose(fp);
	return lines;
}

void Store_temp_data(struct File *E){
	int count;
	// count = countlines(E->FileName);
	// printf("line count as per E->Lines is %d\n",E->Lines );
	// printf("line count as per countlines(E->FileName) is %d\n",count );
	while((fgets(E->TempData, MAX_LEN, E->FileLog) != NULL) /*&& E->Lines < count*/) {	 
	    // Remove the trailing newline character
		if(strchr(E->TempData,'\n')){
			E->TempData[strlen(E->TempData)-1] = '\0';
		}
		E->Data = (char**) realloc(E->Data, sizeof(char**)*(E->Lines+1));
        // E->Data = malloc(sizeof(char**)*(E->Lines+1));
		E->Data[E->Lines] = (char*)calloc(MAX_LEN,sizeof(char));
		memcpy(E->Data[E->Lines], E->TempData,200 );
// printf("TempData: %s\n",E->TempData);        
// printf("Data[Lines]:%s\n", E->Data[E->Lines]);
// printf("%d\n", E->Lines);
		E->Lines++;
	}
}

int bubble_sort(struct File *E){
    //check for usual errors
	if ( (E->FileLog = fopen(E->FileName, "r")) == NULL ){
		Error_print(E->FileName);
		return 1;
	}
	if ( (E->Summary = fopen(E->FileSummary, "a")) == NULL ){
		Error_print(E->FileSummary);        
		return 1;
	}    	
	E->FileLog = fopen(E->FileName, "r");
    // Read and store in a string list.
	Store_temp_data(E);	

	int i, j, x;
        // Sort the array.
	for(i= 0; 
		i < (E->Lines-1); 
		i++) {    
		// make a copy of i th element of array containing the lines of csv files	
		strcpy(E->DataCopy, E->Data[i]);
		// make a copy of (i + 1)th element of array containing the lines of csv files		
		if (i < (E->Lines-1)){
			x=i+1;
			strcpy(E->DataPlus1, E->Data[x]);				
		} 
    	// printf("%s\n", E->DataPlus1);    	
		E->latitude1 = strtok (E->DataCopy,",");
		// why is this loop used? Ans: to get latitude 
		for (int i = 1; 
			i < 2; 
			++i){
			E->latitude1 = strtok (NULL, ",");
		}
    	// printf("%s\n", E->Data[i]);
		// printf ("latitude 1 is %s\n",E->latitude1);
		E->latitude2 = strtok (E->DataPlus1,",");
		// why is this loop used? Ans: to get latitude		
		for (int i = 1; i < 2; i++){
			E->latitude2 = strtok (NULL, ",");
		}
		// printf ("latitude 2 is %s\n",E->latitude2);		
		char temp3[1024];			
		for(j = 0; 
			j < ( E->Lines - i - 1); 
			j++){
    		// if(E->latitude2 != NULL) 
    		// {        
				// if  > 0,  latitude1 > latitude2.
			if(strcmp(E->latitude1, E->latitude2) > 0) {
	            	// temp3[1][1] 	= data[j+1][0];
	            	// data[j+1][0] 	= data[j][0];
	            	// data[j][0]		= temp3[1][1];	
				strcpy(temp3,E->Data[j+1]);		        
				strcpy(*(E->Data+(j+1)), *(E->Data+j));
				strcpy(*(E->Data+j), temp3);	                
			}             
	        // }
		}
	}

    // Write it to outfile. file.
	for(i = 0; 
		i < E->Lines; 
		i++){
		fprintf(E->Summary,"%s\n",E->Data[i]);
	}

    // free each string
	for(i = 0; 
		i < E->Lines; 
		i++){
		free(E->Data[i]);
	}
    // free string list.
	free(E->Data);
	fclose(E->FileLog);
	fclose(E->Summary);
	return 0;
}

void die(const char *message){
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

int main(int argc, char const *argv[])
{
	clock_t begin = clock();
	// printf("welcome to the world of fork and exec by sid \n");
	const char * inputFile = argv[0];
	const char * outputFile= argv[1];
	printf("CSV input  file name is : %s\n", inputFile);
	printf("CSV output file name is : %s\n", outputFile);
	
	printf("start time is : %f\n", argv[2]);

	struct File *E1 = File_create(inputFile,outputFile);
	bubble_sort(E1);	

	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
	printf("time_spent is %f seconds ", getpid(),time_spent);						
	return 0;
}