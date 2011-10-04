#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

int main(int argc, char * argv[])
{
 // char* child1[MAX_ARGS];
 // char* child2[MAX_ARGS];
    pid_t pid;
    int child_status;
    if (argc == 2){
	char *const parmList[] ={"./sort", argv[1] };
	execvp(parmList[0], parmList);
    }
   // printf("this should not be here\n");
    if((pid = fork()) < 0){
        perror ("fork failed");
        exit(1);
    }
    else if (!pid)//child
    {
        char * parmList[argc/2 + 2];// = {argv[0]};
	parmList[0] = argv[0];
	for (int i = 1; i < argc/2 + 1; i ++)
	    parmList[i] = argv[i];
	parmList[argc/2 + 1] = NULL;
	printf("im a child %s %s\n", argv[0], argv[1]);	
	printf("%d\n",(argc/2 + 1));
        //exit(0);
	execvp(parmList[0], parmList);
    }
    else{ //parent
        char * parmList[(argc - argc/2)];// = {argv[0]};
        parmList[0] = argv[0];
	for (int i = argc/2 + 1; i < argc; i ++)
            parmList[i - argc/2] = argv[i];

        wait(&child_status);
    }
    return 0;
}

