#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <fstream>
#define READ 0
#define WRITE 1

using namespace std;

int main(int argc, char * argv[])
{ 
    int pipe1[2];
    pid_t pid;
    int status;
    int c;
    FILE *instream;
    ofstream outstream, log;

    log.open("log.txt");
    log << "started execution" << endl;
    log.close();
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
	//freopen ("myfile.txt","w",stdout);
	if(execvp("./parent", argv) < 0){
	    perror("exec failed");
	    exit(1);
	}
    }
    else {
    wait(&status);
    close (pipe1[WRITE]);
    instream = fdopen(pipe1[READ], "r");
    outstream.open("out.txt");

    while (fscanf(instream, "%d", &c) != EOF){
	outstream << c << "\n";	
	cout << c << "\n";	
    }
    outstream.close(); 
    close(pipe1[READ]);

    fclose (instream);
    }

    log.open("log.txt");
    log << "ended executing" << endl;
    log.close();
    //cout << "Sorted all of the files and output to out.txt" << endl;   
    return 0;
}
