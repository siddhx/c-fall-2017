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
#include <time.h>
#include <pthread.h>

void die(const char *message){
	if (errno) {
		perror(message);
	} else {
		printf("ERROR: %s\n", message);
	}

	exit(1);
}

void create_process(char *inputFile, char *outputFile, clock_t begin){
	pid_t pid;	
	if ((pid = fork()) < 0 ) {
	           /* Fork system call failed */
	           perror("fork"), exit(1);
	}else if (pid == 0) {
	           /* Child only, pid is 0 */
				// first child

				char *execFilename = "./EXEC";
		        char *args[4]={inputFile,outputFile,begin, NULL};
		        // execvp(args[0],args);
				execve(execFilename, args);
								
				int pid = getpid();

				printf("Child1 process id is %d\n", pid);

				exit(0);
	           // return 0;
	}else {
	           /* Parent only , pid is child's process ID */
		printf("Parent process id is %d\n", getpid());				
		// printf("Parent process id is %d\n, time_spent is %f seconds ", getpid(),time_spent);			
	}	
}
int main(int argc, char *argv[]){
	// int x;
    // char *FileName = "./E.csv";
	if (argc < 1)
		die("USAGE: ./osassignment <number of processes>");

	char action = argv[1][0];
    // char action = argv[2][0];
	pid_t child1,child2,pid;

	switch (action){
		case '1':
		{
				// int pid = getpid();
			clock_t begin = clock();

			// struct File *E = File_create("./earthquake.csv","./earthquake_out.csv");
			char *execFilename = "./EXEC";
	        char *args[4]={"./earthquake.csv","./earthquake_out.csv",begin, NULL};
	        // execvp(args[0],args);
			execve(execFilename, args);

			// bubble_sort(E);			
			clock_t end = clock();
			double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
			printf("Parent process id is %d\n, time_spent is %f seconds ", getpid(),time_spent);		

			break;
		}

		case '2':
		{
			clock_t begin = clock();
			create_process("earthquake2processaa", "./earthquake_1out.csv", begin);
			create_process("earthquake2processab", "./earthquake_2out.csv", begin);			
			clock_t end = clock();			

			break;
		}

		case '3':
		{
			pthread_t thread1;
			pthread_t do_nothing_thread1;

			// if (pthread_create(&do_nothing_thread1, NULL, do_nothing, NULL))
			// {
			// 	perror("Error creating thread:");
			// 	exit( EXIT_FAILURE);
			// }

			// if (pthread_join(do_nothing_thread1, NULL))
			// {
			// 	perror("problem with pthread_join");
			// }			
		}
		case '4':
		{
			clock_t begin = clock();
			create_process("earthquake4processaa", "./earthquake_1out.csv", begin);
			create_process("earthquake4processab", "./earthquake_2out.csv", begin);
			create_process("earthquake4processac", "./earthquake_3out.csv", begin);
			create_process("earthquake4processad", "./earthquake_4out.csv", begin);
			clock_t end = clock();			

			break;
		}

		break;
        case '9': 
		{
			clock_t begin = clock();
			create_process("earthquake10processaa", "./earthquake_1out.csv", begin);
			create_process("earthquake10processab", "./earthquake_2out.csv", begin);
			create_process("earthquake10processac", "./earthquake_3out.csv", begin);
			create_process("earthquake10processad", "./earthquake_4out.csv", begin);
			create_process("earthquake10processae", "./earthquake_5out.csv", begin);
			create_process("earthquake10processaf", "./earthquake_6out.csv", begin);
			create_process("earthquake10processag", "./earthquake_7out.csv", begin);
			create_process("earthquake10processah", "./earthquake_8out.csv", begin);			
			create_process("earthquake10processai", "./earthquake_9out.csv", begin);
			create_process("earthquake10processaj", "./earthquake_10out.csv", begin);						
			clock_t end = clock();			

			break;
		}
		default:
		printf("%c\n", action);
		die("Invalid action: 1=1 processs, 2=2 processs, 34=4 processs, 10=10 processs");
	}    




	return 0;	
}