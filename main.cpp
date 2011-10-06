/*
 * Cory Hagerman
 * main.cpp
 * 
 * */
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
    //pipe to redirect child output
    int pipe1[2];

    //used for child process
    pid_t pid;
    int status;

    //int to read in from the child
    int c;
   
    // input stream
    FILE *instream;

    //output stream
    ofstream outstream, log;
    //start a log file
    log.open("log.txt");
    log << "started execution" << endl;
    log.close();
    //create the pipe for the children
    if (pipe(pipe1) < 0){
	perror("bad pipe");
	exit(0);
    }
    //fork a child
    if ((pid = fork ()) < 0){
	perror ("fork failed");
	exit(1);
    }else if (!pid){
        //set up the output of the child
    	dup2 (pipe1[WRITE], STDOUT_FILENO);
	close (pipe1[READ]);
	close (pipe1[WRITE]);
	//exec with the same arguments
	if(execvp("./parent", argv) < 0){
	    perror("exec failed");
	    exit(1);
	}
    }
    else {
        waitpid(pid,&status,0);
        close (pipe1[WRITE]);

        //read in from the child and print it out to stdout and the
        //out put file
        instream = fdopen(pipe1[READ], "r");
        outstream.open("out.txt");
        while (fscanf(instream, "%d", &c) != EOF){
	    outstream << c << "\n";	
	    cout << c << "\n";	
        }
	//close the opened resources
        outstream.close(); 
        close(pipe1[READ]);

        fclose (instream);
    }

    return 0;
}
