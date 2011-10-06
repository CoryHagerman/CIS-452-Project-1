/************************************************************
Cory Hagerman
sort.cpp
This will be the most child process in the tree
it will be sent one filename.
this program will sort the file, print it to standard out, and
then signal the parent that it has printed everything
*************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void sort(int[], int);
void print(int[], int);
int main(int argc, char * argv[]){
    int *numbers;
    int curr_size = 10;
    int number_words;
    ofstream log;
    sleep(1);
    //append to the log
    log.open("log.txt", std::ios::app);
    log << "PID: " << getpid() << " is sorting: " << argv[1]<< endl;
    log.close(); 
    
    //get space to read in the file
    numbers = (int*) calloc(curr_size, sizeof(int));
    if (numbers == NULL) {
        fprintf (stderr, "memory allocation failed\n");
        exit (1);
    }
   
    string line;
    ifstream myfile (argv[1]);

    //read in file
    if (myfile.is_open()){
        while ( myfile.good() ){
            //make more space if need when reading in file
	    if (number_words >= curr_size){
		curr_size += 10;
		numbers = (int*) realloc(numbers, curr_size * sizeof(int));
	    }
            getline (myfile,line);
            numbers[number_words++] = atoi(line.c_str());
	    //cout << line << endl;
        }
        myfile.close();
    } 
    number_words--; 
    sort(numbers, number_words);
    print(numbers, number_words);
    //append to log file
    log.open("log.txt", std::ios::app);
    log << "PID: " << getpid() << " is done sorting: " << argv[1]<< endl; 
    //free numbers
    free(numbers);
    log.close();
    return 0;
}
//Bubble Sort
void sort (int* array, int count){
        
    for (int j = 0; j < count; j++)
        for (int i = 1; i < count; i++)
	    if (array[i - 1] > array[i]){
		int tmp = array[i - 1];
		array[i - 1] = array[i];
		array[i] = tmp;
	    }
}
//Print the values in an array
void print (int* array, int count){
    for (int i = 0; i < count; i++)
	cout << array[i] << "\n";
}
