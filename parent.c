#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#define READ 0 
#define WRITE 1

void print (int pipe1, int pipe2);

void child (int, int, char * argv[]);

int main(int argc, char * argv[])
{
    if (argc <= 2){
	char * const parmList[] ={"./sort", argv[1] };
	if(execvp(parmList[0], parmList) < 0){
	    perror("Exec Failure on Sort");
	    exit(1);
	}
    }
    
    pid_t pid, pid2;
    int status;
    int pipe1[2], pipe2[2];

    if (pipe (pipe1) < 0) { 
        perror ("plumbing problem"); 
        exit(1); 
    } 
    if (pipe (pipe2) < 0) { 
        perror ("plumbing problem"); 
        exit(1); 
    }
 
    if((pid = fork()) < 0){
        perror ("fork failed");
        exit(1);
    }
    else if (!pid)//child
    {
	dup2 (pipe1[WRITE], STDOUT_FILENO);
	close (pipe1[READ]); 
        close (pipe1[WRITE]);
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
	    dup2 (pipe2[WRITE], STDOUT_FILENO);
	    close (pipe2[READ]); 
            close (pipe2[WRITE]);
            child(argc - argc/2, argc/2, argv);
            exit(1);
        }
        else{ //parent
            wait(&status);
            wait(&status);
	    close(pipe1[WRITE]);
	    close(pipe2[WRITE]);
	    
	    print(pipe1[READ], pipe2[READ]);
	    
	    close(pipe1[READ]);
	    close(pipe2[READ]);		
        }
    }
    return 0;
}

void child (int size, int start, char * argv[])
{
	printf("Child %d is now running\n", getpid());
	char ** parmList2;
	parmList2 = (char **)calloc(size, sizeof(char*));
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

void print (int pipe1, int pipe2){

    bool c1 = true;
    bool c2 = true;
    FILE *stream1;
    FILE *stream2;
    stream1 = fdopen (pipe1, "r");
    stream2 = fdopen (pipe2, "r");
    int left, right;
    if ((fscanf (stream1, "%d", &left)) == EOF)
        c1 = false;
    
    if ((fscanf (stream2, "%d", &right)) == EOF)
        c2 = false;
    
    while (c1 || c2){
	if (c1 && left < right){
	    printf("%d\n",left);
    	    if ((fscanf (stream1, "%d", &left)) == EOF)
        	c1 = false;
	}
	else if(c2 && right <= left){
	    printf("%d\n",right);
	    if ((fscanf (stream2, "%d", &right)) == EOF)
                c2 = false;
	}
	
	if (!c1 && c2){
	    printf("%d\n",right);
	    while ((fscanf (stream2, "%d", &right)) != EOF)
	    printf("%d\n",right);
	    break;
	}
	if (!c2 && c1){
	    printf("%d\n",left);
	    while ((fscanf (stream1, "%d", &left)) != EOF)
	    printf("%d\n",left);
	    break;
	}
    }
    fclose (stream1);
    fclose (stream2);
}
