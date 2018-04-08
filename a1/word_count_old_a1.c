//Header files to include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Compile-time constants
#define MAX_WORD_LEN 34
#define MAX_WORDS_FILE 750
#define MAX_FILE_SIZE 5000

//Defining the Entry struct
typedef struct entry_struct{
	int word_length;
	int occurrences;
} Entry;


//Global variables
Entry count[34]; //tracks number of words of each length. Rearrangable while keeping track of what word length corresponds to what number of occurrences

//Function declarations
void process_line (char *input_line);

void print_count();

int comparator(const void *p, const void *q);//for qsort


//FUNCTIONS

void process_line(char *input_line){

        char *t;

        t = strtok(input_line, " .,;()\n");
        //in the next line, that t in the loop condition counts as true so long as t exists (so long as we have not run out of tokens)
        while(t){
               // strncpy(words[num_words], t, MAX_WORD_LEN); //This old line may be near what's needed to enter into a list of found words
		count[strlen(t)-1].occurrences++;//increment the spot in the array that corresponds to the number of words of t's length
		//warning: you need to initialize the contents of count to all zeroes
                t = strtok(NULL, " .,;()\n");
        }
        return;
}


void print_count(){
	for (int i = 0; i < 34; i++){
		if (count[i].occurrences!=0){
			printf("Count[%02d]=%02d;\n", count[i].word_length, count[i].occurrences);
		}
	}
}

int comparator(const void *p, const void *q){//compare function for qsort
	Entry *entryp = (Entry *)p;
	Entry *entryq = (Entry *)q;
	return (entryq->occurrences - entryp->occurrences);
}

//MAIN PROGRAM

int main(int argc, char **argv){

	//SETUP
	FILE *input;
	int sortflag = 0; 
	
	for (int i = 0; i < 34; i++){ //initializing count array
		count[i].word_length = i+1;
		count[i].occurrences = 0;
	}

	if (argc<3){//checking to ensure that the number of arguments is acceptable
		fprintf(stderr, "Not enough arguments!\nYou need at least 3, and you fed me %d!\n", argc);	
		exit(0);
	}

	//This block deals with the various flags, etc
	for (int i = 1; i < argc; i++){
		
		//locating the input file within the arguments so it can be opened
		if (!strcmp(argv[i], "--infile")){
			
			input = fopen(argv[i+1], "r");//the file will be one argument after the argument "--infile"
			if (input == NULL){
				fprintf(stderr, "Cannot open file!\n");
				exit(1);
			}
		}
		
		if (!strcmp("--sort", argv[i])) {
			//printf("--sort detected");
			sortflag = 1;
		}
	}
	
	char tmpstr[MAX_FILE_SIZE];//this is the string that fgets dumps lines to
	while (fgets(tmpstr, MAX_FILE_SIZE, input) != NULL){
		
		process_line(tmpstr);//tokenizes the line and adds to word totals
	}
	//done calculating word totals
	
	
	if (sortflag){
		qsort(count, MAX_WORD_LEN, sizeof(Entry), comparator);
	}
	
	print_count();

	return 0;
}
