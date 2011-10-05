#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

void child (int, int, char * argv[]);

int main(int argc, char * argv[])
{
    pid_t pid, pid2;
    int status;
    if (argc <= 2){
	char * const parmList[] ={"./sort", argv[1] };
	if(execvp(parmList[0], parmList) < 0){
	    perror("Exec Failure on Sort");
	    exit(1);
	}
    }
    if((pid = fork()) < 0){
        perror ("fork failed");
        exit(1);
    }
    else if (!pid)//child
    {
	child(argc/2 + 1, 0, argv);
	exit(1);
    }
    else{ //parent
        if((pid2 = fork()) < 0){
            perror ("fork failed");
            exit(1);
        }
        else if (!pid2)// second child
        {
            child(argc - argc/2, argc/2, argv);
            exit(1);
        }
        else{ //parent
            wait(&status);
            wait(&status);
        }
    }
    return 0;
}


void child (int size, int start, char * argv[])
{
	printf("Child %d is now running\n", getpid());
	char ** parmList2;
	parmList2 = (char **)calloc(size, sizeof(char*));
        //printf("calloced\n");
	parmList2[0] = (char *)malloc(sizeof(argv[0]));
	strcpy(parmList2[0],argv[0]);
	for (int i = 1; i < size; i ++){
	    parmList2[i] = (char *)malloc(sizeof(argv[i + start]));
	    strcpy(parmList2[i],argv[i + start]);
	    //parmList2[i] = argv[i];
	}
	parmList2[size] = NULL;
	//printf("im a child :%s: :%s:\n", parmList2[0], parmList2[1]);	
	//printf("size:%d:\nstart:%d:\n",size, start);
	//printf("im about to exec\n");
	if(execvp(parmList2[0], parmList2) < 0){
            perror("Exec Failure");
            exit(1);
        }
}
