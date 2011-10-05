#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void child (int, char * argv[]);

int main(int argc, char * argv[])
{
 // char* child1[MAX_ARGS];
 // char* child2[MAX_ARGS];
    pid_t pid;
    int status;
    int argc_temp = argc;
 // printf("argc %d\n", argc_temp);
    if (argc_temp <= 2){
	char * const parmList[] ={"./sort", argv[1] };
	execvp(parmList[0], parmList);
    }
   // printf("this should not be here\n");
    if((pid = fork()) < 0){
        perror ("fork failed");
        exit(1);
    }
    else if (!pid)//child
    {
	child(argc_temp/2 + 1, argv);
/*
	printf("Child %d is now running\n", getpid());
	char ** parmList2;
	parmList2 = (char **)calloc(argc_temp/2 + 2, sizeof(char*));
        //char * parmList2[argc_temp/2 + 2];// = {argv[0]};
	strcpy(parmList2[0],argv[0]);
	for (int i = 1; i < argc_temp/2 + 1; i ++){
	    parmList2[i] = malloc(sizeof(argv[i]));
	    strcpy(parmList2[i],argv[i]);
	    //parmList2[i] = argv[i];
	}
	parmList2[argc_temp/2 + 1] = NULL;
	printf("im a child :%s: :%s:\n", argv[0], argv[1]);	
	printf("%d\n",(argc_temp/2 + 1));
        //exit(0);
        sleep(1);
	execvp(parmList2[0], parmList2);
*/
    }
    else{ //parent
    /*    char * parmList3[(argc_temp - argc_temp/2)];// = {argv[0]};
        parmList3[0] = argv[0];
	for (int i = argc_temp/2 + 1; i < argc_temp; i ++)
            parmList3[i - argc_temp/2] = argv[i];
sleep(10);*/
        waitpid(-1, &status, 0);

        //pid = wait(&status);
        //sleep(10);  
    }
    return 0;
}


void child (int size, char * argv[])
{
	printf("Child %d is now running\n", getpid());
	char ** parmList2;
	parmList2 = (char **)calloc(size, sizeof(char*));
        //char * parmList2[argc_temp/2 + 2];// = {argv[0]};
	strcpy(parmList2[0],argv[0]);
	for (int i = 1; i < size; i ++){
	    parmList2[i] = malloc(sizeof(argv[i]));
	    strcpy(parmList2[i],argv[i]);
	    //parmList2[i] = argv[i];
	}
	//parmList2[argc_temp/2 + 1] = NULL;
	printf("im a child :%s: :%s:\n", argv[0], argv[1]);	
	printf("%d\n",size);
        //exit(0);
        sleep(1);
	printf("im about to exec\n");
	execvp(parmList2[0], parmList2);
}
