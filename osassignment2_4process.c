/* 
Siddharth Agarwal
UTA ID 1001577570
CSE 3320-001 Operating Systems
*/

/*References: 
	1. https://stackoverflow.com/questions/28536150/how-to-sort-data-inside-txt-files-in-c
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
#include <stdlib.h>

#define MAX_LEN 300 // Length of each line in input file.


int main(){

	int pid = getpid();
	printf("Parent process id is %d\n", pid);		
	pid_t child1,child2;

	if(!(child1 = fork())){
		// first child
		int pid = getpid();
				// int x;
			    // char *strFileName = "./earthquake.csv";
			    char *strFileName = "./earthquake4processaa";    
			    char *strFileSummary = "./earthquake4process_part1.csv";
			    char strTempData[MAX_LEN]; 
				char **strData = NULL; // String List
				    
			    int i, j;
			    int noOfLines = 0;

			    FILE * ptrFileLog = NULL;
			    FILE * ptrSummary = NULL;

			    //check for usual errors
			    if ( (ptrFileLog = fopen(strFileName, "r")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileName);
			        return 1;
			    }
			    if ( (ptrSummary = fopen(strFileSummary, "a")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileSummary);
			        return 1;
			    }    	
				ptrFileLog = fopen(strFileName, "r");

			    // Read and store in a string list.
			    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
				    
				    // Remove the trailing newline character

			        if(strchr(strTempData,'\n'))
			            strTempData[strlen(strTempData)-1] = '\0';
			        strData = (char**)realloc(strData, sizeof(char**)*(noOfLines+1));
			        strData[noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
			        strcpy(strData[noOfLines], strTempData);
			        noOfLines++;
			    }

			    // Sort the array.
			    for(i= 1; i < (noOfLines); ++i) {
			        
			    	// printf("%s\n", strData[i]);
					int x;

					char *latitude1;
					char *latitude2;
					char temp1[1024];
					char temp2[1024];
					char temp3[1024];			
						
					strcpy(temp1, strData[i]);
					
					if (i < (noOfLines-1)){
						x=i+1;
						strcpy(temp2, strData[x]);				
					} 

					latitude1 = strtok (temp1,",");

					for (int i = 1; i < 2; ++i)
						latitude1 = strtok (NULL, ",");

					// printf ("latitude 1 is %s\n",latitude1);

					latitude2 = strtok (temp2,",");
					
					for (int i = 1; i < 2; ++i)
						latitude2 = strtok (NULL, ",");

					// printf ("latitude 2 is %s\n",latitude2);		
			        for(j = 1; j < ( noOfLines - 1); ++j) {

			    		if(latitude2 != NULL){        

				            if(strcmp(latitude1, latitude2) > 0) {
					            	char *swap[1024];

									strcpy(swap, strData[j]);
									strcpy(temp3,strData[j+1]);		        

					                strcpy(*(strData+j), temp3);

					                	strcpy(*(strData+(j+1)), swap);		                
										// printf ("contents in current row being processed: %s\n",*(strData+j+1));
				            }

				     //        if(strcmp(latitude1, latitude2) < 0) {
				     //        	if(i < (noOfLines)){
					    //         	char *swap;
					    //         	swap = temp1;
					    //         	int index = i+1;
					    //         	//strcpy copies the stirng pointed to by the pointer in second argument
					    //             strcpy(swap, temp1);
									// // printf ("latitude 2 is %s\n",*(strData+i));
					    //             strcpy(*(strData+i), temp2);
					    //             // strcpy(*(strData+index), swap);		                
					    //         }
				     //        }	            
				        }
			        }
			    }

			    // Write it to outfile. file.
			    for(i = 0; i < noOfLines; i++)
			        fprintf(ptrSummary,"%s\n",strData[i]);

			    // free each string
			    for(i = 0; i < noOfLines; i++)
			        free(strData[i]);
			    // free string list.
			    free(strData);
			    fclose(ptrFileLog);
			    fclose(ptrSummary);

		// only child process executes this

		printf("Child1 process id is %d\n", pid);
 		
        exit(0);
	} 
	else if (!(child2= fork())){
		// second child		
		int pid = getpid();
		// only child2 executes this
			    char *strFileName = "./earthquake4processab";    
			    char *strFileSummary = "./earthquake4process_part2.csv";
			    char strTempData[MAX_LEN]; 
				char **strData = NULL; // String List
				    
			    int i, j;
			    int noOfLines = 0;

			    FILE * ptrFileLog = NULL;
			    FILE * ptrSummary = NULL;

			    //check for usual errors
			    if ( (ptrFileLog = fopen(strFileName, "r")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileName);
			        return 1;
			    }
			    if ( (ptrSummary = fopen(strFileSummary, "a")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileSummary);
			        return 1;
			    }    	
				ptrFileLog = fopen(strFileName, "r");

			    // Read and store in a string list.
			    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
				    
				    // Remove the trailing newline character

			        if(strchr(strTempData,'\n'))
			            strTempData[strlen(strTempData)-1] = '\0';
			        strData = (char**)realloc(strData, sizeof(char**)*(noOfLines+1));
			        strData[noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
			        strcpy(strData[noOfLines], strTempData);
			        noOfLines++;
			    }

			    // Sort the array.
			    for(i= 1; i < (noOfLines); ++i) {
			        
			    	// printf("%s\n", strData[i]);
					int x;

					char *latitude1;
					char *latitude2;
					char temp1[1024];
					char temp2[1024];
					char temp3[1024];			
						
					strcpy(temp1, strData[i]);
					
					if (i < (noOfLines-1)){
						x=i+1;
						strcpy(temp2, strData[x]);				
					} 

					latitude1 = strtok (temp1,",");

					for (int i = 1; i < 2; ++i)
						latitude1 = strtok (NULL, ",");

					// printf ("latitude 1 is %s\n",latitude1);

					latitude2 = strtok (temp2,",");
					
					for (int i = 1; i < 2; ++i)
						latitude2 = strtok (NULL, ",");

					// printf ("latitude 2 is %s\n",latitude2);		
			        for(j = 1; j < ( noOfLines - 1); ++j) {

			    		if(latitude2 != NULL){        

				            if(strcmp(latitude1, latitude2) > 0) {
					            	char *swap[1024];

									strcpy(swap, strData[j]);
									strcpy(temp3,strData[j+1]);		        

					                strcpy(*(strData+j), temp3);

					                	strcpy(*(strData+(j+1)), swap);		                
										// printf ("contents in current row being processed: %s\n",*(strData+j+1));
				            }

				     //        if(strcmp(latitude1, latitude2) < 0) {
				     //        	if(i < (noOfLines)){
					    //         	char *swap;
					    //         	swap = temp1;
					    //         	int index = i+1;
					    //         	//strcpy copies the stirng pointed to by the pointer in second argument
					    //             strcpy(swap, temp1);
									// // printf ("latitude 2 is %s\n",*(strData+i));
					    //             strcpy(*(strData+i), temp2);
					    //             // strcpy(*(strData+index), swap);		                
					    //         }
				     //        }	            
				        }
			        }
			    }

			    // Write it to outfile. file.
			    for(i = 0; i < noOfLines; i++)
			        fprintf(ptrSummary,"%s\n",strData[i]);

			    // free each string
			    for(i = 0; i < noOfLines; i++)
			        free(strData[i]);
			    // free string list.
			    free(strData);
			    fclose(ptrFileLog);
			    fclose(ptrSummary);
		printf("Child2 process id is %d\n", pid);
        exit(0);		
	}
		else if (!(child2= fork())){
		// second child		
		int pid = getpid();
		// only child2 executes this
			    char *strFileName = "./earthquake4processac";    
			    char *strFileSummary = "./earthquake4process_part4.csv";
			    char strTempData[MAX_LEN]; 
				char **strData = NULL; // String List
				    
			    int i, j;
			    int noOfLines = 0;

			    FILE * ptrFileLog = NULL;
			    FILE * ptrSummary = NULL;

			    //check for usual errors
			    if ( (ptrFileLog = fopen(strFileName, "r")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileName);
			        return 1;
			    }
			    if ( (ptrSummary = fopen(strFileSummary, "a")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileSummary);
			        return 1;
			    }    	
				ptrFileLog = fopen(strFileName, "r");

			    // Read and store in a string list.
			    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
				    
				    // Remove the trailing newline character

			        if(strchr(strTempData,'\n'))
			            strTempData[strlen(strTempData)-1] = '\0';
			        strData = (char**)realloc(strData, sizeof(char**)*(noOfLines+1));
			        strData[noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
			        strcpy(strData[noOfLines], strTempData);
			        noOfLines++;
			    }

			    // Sort the array.
			    for(i= 1; i < (noOfLines); ++i) {
			        
			    	// printf("%s\n", strData[i]);
					int x;

					char *latitude1;
					char *latitude2;
					char temp1[1024];
					char temp2[1024];
					char temp3[1024];			
						
					strcpy(temp1, strData[i]);
					
					if (i < (noOfLines-1)){
						x=i+1;
						strcpy(temp2, strData[x]);				
					} 

					latitude1 = strtok (temp1,",");

					for (int i = 1; i < 2; ++i)
						latitude1 = strtok (NULL, ",");

					// printf ("latitude 1 is %s\n",latitude1);

					latitude2 = strtok (temp2,",");
					
					for (int i = 1; i < 2; ++i)
						latitude2 = strtok (NULL, ",");

					// printf ("latitude 2 is %s\n",latitude2);		
			        for(j = 1; j < ( noOfLines - 1); ++j) {

			    		if(latitude2 != NULL){        

				            if(strcmp(latitude1, latitude2) > 0) {
					            	char *swap[1024];

									strcpy(swap, strData[j]);
									strcpy(temp3,strData[j+1]);		        

					                strcpy(*(strData+j), temp3);

					                	strcpy(*(strData+(j+1)), swap);		                
										// printf ("contents in current row being processed: %s\n",*(strData+j+1));
				            }

				     //        if(strcmp(latitude1, latitude2) < 0) {
				     //        	if(i < (noOfLines)){
					    //         	char *swap;
					    //         	swap = temp1;
					    //         	int index = i+1;
					    //         	//strcpy copies the stirng pointed to by the pointer in second argument
					    //             strcpy(swap, temp1);
									// // printf ("latitude 2 is %s\n",*(strData+i));
					    //             strcpy(*(strData+i), temp2);
					    //             // strcpy(*(strData+index), swap);		                
					    //         }
				     //        }	            
				        }
			        }
			    }

			    // Write it to outfile. file.
			    for(i = 0; i < noOfLines; i++)
			        fprintf(ptrSummary,"%s\n",strData[i]);

			    // free each string
			    for(i = 0; i < noOfLines; i++)
			        free(strData[i]);
			    // free string list.
			    free(strData);
			    fclose(ptrFileLog);
			    fclose(ptrSummary);
		printf("Child2 process id is %d\n", pid);
        exit(0);		
	}
		else if (!(child2= fork())){
		// second child		
		int pid = getpid();
		// only child2 executes this
			    char *strFileName = "./earthquake4processad";    
			    char *strFileSummary = "./earthquake4process_part4.csv";
			    char strTempData[MAX_LEN]; 
				char **strData = NULL; // String List
				    
			    int i, j;
			    int noOfLines = 0;

			    FILE * ptrFileLog = NULL;
			    FILE * ptrSummary = NULL;

			    //check for usual errors
			    if ( (ptrFileLog = fopen(strFileName, "r")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileName);
			        return 1;
			    }
			    if ( (ptrSummary = fopen(strFileSummary, "a")) == NULL ) {
			        fprintf(stderr,"Error: Could not open %s\n",strFileSummary);
			        return 1;
			    }    	
				ptrFileLog = fopen(strFileName, "r");

			    // Read and store in a string list.
			    while(fgets(strTempData, MAX_LEN, ptrFileLog) != NULL) {
				    
				    // Remove the trailing newline character

			        if(strchr(strTempData,'\n'))
			            strTempData[strlen(strTempData)-1] = '\0';
			        strData = (char**)realloc(strData, sizeof(char**)*(noOfLines+1));
			        strData[noOfLines] = (char*)calloc(MAX_LEN,sizeof(char));
			        strcpy(strData[noOfLines], strTempData);
			        noOfLines++;
			    }

			    // Sort the array.
			    for(i= 1; i < (noOfLines); ++i) {
			        
			    	// printf("%s\n", strData[i]);
					int x;

					char *latitude1;
					char *latitude2;
					char temp1[1024];
					char temp2[1024];
					char temp3[1024];			
						
					strcpy(temp1, strData[i]);
					
					if (i < (noOfLines-1)){
						x=i+1;
						strcpy(temp2, strData[x]);				
					} 

					latitude1 = strtok (temp1,",");

					for (int i = 1; i < 2; ++i)
						latitude1 = strtok (NULL, ",");

					// printf ("latitude 1 is %s\n",latitude1);

					latitude2 = strtok (temp2,",");
					
					for (int i = 1; i < 2; ++i)
						latitude2 = strtok (NULL, ",");

					// printf ("latitude 2 is %s\n",latitude2);		
			        for(j = 1; j < ( noOfLines - 1); ++j) {

			    		if(latitude2 != NULL){        

				            if(strcmp(latitude1, latitude2) > 0) {
					            	char *swap[1024];

									strcpy(swap, strData[j]);
									strcpy(temp3,strData[j+1]);		        

					                strcpy(*(strData+j), temp3);

					                	strcpy(*(strData+(j+1)), swap);		                
										// printf ("contents in current row being processed: %s\n",*(strData+j+1));
				            }

				     //        if(strcmp(latitude1, latitude2) < 0) {
				     //        	if(i < (noOfLines)){
					    //         	char *swap;
					    //         	swap = temp1;
					    //         	int index = i+1;
					    //         	//strcpy copies the stirng pointed to by the pointer in second argument
					    //             strcpy(swap, temp1);
									// // printf ("latitude 2 is %s\n",*(strData+i));
					    //             strcpy(*(strData+i), temp2);
					    //             // strcpy(*(strData+index), swap);		                
					    //         }
				     //        }	            
				        }
			        }
			    }

			    // Write it to outfile. file.
			    for(i = 0; i < noOfLines; i++)
			        fprintf(ptrSummary,"%s\n",strData[i]);

			    // free each string
			    for(i = 0; i < noOfLines; i++)
			        free(strData[i]);
			    // free string list.
			    free(strData);
			    fclose(ptrFileLog);
			    fclose(ptrSummary);
		printf("Child2 process id is %d\n", pid);
        exit(0);		
	}
    return 0;	
}