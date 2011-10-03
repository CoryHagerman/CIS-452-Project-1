/************************************************************
This will be the most child process in the tree
it will be sent one filename.
this program will sort the file, print it to standard out, and
then signal the parent that it has printed everything
*************************************************************/
#include <stdio.h>

void sort(int[], int);

int main(int argc, char * argv[]){

    int[] array;

    return 0;
}

void sort (int[] array, int count){
    for (int i = 0; i < count-1; i++)
    	for (int j = 1; j < count; j++)
	    if (array[i] > array[j]){
		int tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
	    }
}
