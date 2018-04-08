#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>

int main(){

	int bytes_read;
	size_t nbytes = 100;
	char *my_string;

	puts("Please enter a line of text.");

	// These two lines are the heart of the program.
	my_string = (char *) malloc (nbytes+1);
	bytes_read = getline(&my_string, &nbytes, stdin);
	
	if (bytes_read == -1) puts("ERROR!");
	else{
		puts("You typed:");
		puts(my_string);
	}
	return 0;
}
