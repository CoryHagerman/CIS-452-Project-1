/************************************************************
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
    numbers = (int*) calloc(curr_size, sizeof(int));
    if (numbers == NULL) {
        fprintf (stderr, "memory allocation failed\n");
        exit (1);
    }
   
    string line;
    ifstream myfile (argv[1]);
    if (myfile.is_open()){
        while ( myfile.good() ){
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
    free(numbers);

    return 0;
}

void sort (int* array, int count){
        
    for (int j = 0; j < count; j++)
        for (int i = 1; i < count; i++)
	    if (array[i - 1] > array[i]){
		int tmp = array[i - 1];
		array[i - 1] = array[i];
		array[i] = tmp;
	    }
}

void print (int* array, int count){
    for (int i = 0; i < count; i++)
	cout << array[i] << "\n";
}
