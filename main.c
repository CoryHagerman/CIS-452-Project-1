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

int main(int argc, char * argv[])
{ 
    int pipe1[2];
    pid_t pid;
    int status;
    int c;
    FILE *instream, *outstream;

    if (pipe(pipe1) < 0){
	perror("bad pipe");
	exit(0);
    }
    if ((pid = fork ()) < 0){
	perror ("fork failed");
	exit(1);
    }else if (!pid){
    	dup2 (pipe1[WRITE], STDOUT_FILENO);
	close (pipe1[READ]);
	close (pipe1[WRITE]);

	if(execvp("./parent", argv) < 0){
	    perror("exec failed");
	    exit(1);
	}
    }
    else {
    wait(&status);
    close (pipe1[WRITE]);
    instream = fdopen(pipe1[READ], "r");
    outstream = fopen("out.txt", "w");

    if (outstream == NULL) {
        fprintf(stderr, "Can't open output file %s!\n","out.txt");
        exit(1);
    }
    while (fscanf(instream, "%d", &c) != EOF)
	fprintf(outstream, "im printing\n");
    //printf("Your files are sorted into out.txt\n");
    //close(pipe1[1]); 
    //FILE *stream1, *stream2;
    //stream1 = fdopen (pipe1[0], "r");
    //stream2 = fopen ("out.txt", "wt");
    //while ((fscanf(stream1, "%d", &c)) != EOF)
//	printf("%d", c);
	//putchar(c);
    
    close(pipe1[READ]);
    fclose (instream);
    fclose (outstream);
    //fclose (stream2);
    }
    return 0;
}
