//Header files to include
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

//Compile-time constants
#define MAX_WORD_LEN 34
#define MAX_WORDS_FILE 750
#define MAX_FILE_SIZE 5000

//Defining the Entry struct
typedef struct entry_struct{
	int word_length;
	int occurrences;
	char wordarray[MAX_WORDS_FILE][MAX_WORD_LEN];
	int uniques;
} Entry;


//Global variables
Entry count[MAX_WORD_LEN]; //tracks number of words of each length. Rearrangable while keeping track of what word length corresponds to what number of occurrences

//Function declarations

void str_tolower(char *instr);

void process_line (char *input_line, int dowords);

void print_count();

void print_count_pw();

int comparator(const void *p, const void *q);//for qsorting entries by occurrences

int comparator_str(const void *a, const void *b); //compare function for qsorting words


//FUNCTIONS

//converts a whole string to lowercase
void str_tolower(char *instr){
	for (int i = 0; instr[i]; i++){
		instr[i] = tolower(instr[i]);
	}
}

void process_line(char *input_line, int dowords){

        char *t;
	int present; //determines whether a word has already been stored

        t = strtok(input_line, " .,;()\n");
        //in the next line, that t in the loop condition counts as true so long as t exists (so long as we have not run out of tokens)
        while(t){
		str_tolower(t);
		if (dowords){
			present = 0;
			for (int i = 0; i < count[strlen(t)-1].occurrences; i++){
				if (!strcmp(t, count[strlen(t)-1].wordarray[i])) {
					present = 1; //if the word is already there, remember so
					break;
				}
			}
			if (!present){
				strncpy(count[strlen(t)-1].wordarray[count[strlen(t)-1].uniques], t, MAX_WORD_LEN); //add to list of unique words
				count[strlen(t)-1].uniques++; //a unique word has been added
			}
		}
		count[strlen(t)-1].occurrences++;//increment the number that corresponds to the number of words of t's length
                t = strtok(NULL, " .,;()\n");
        }
        return;
}


void print_count(){
        for (int i = 0; i < MAX_WORD_LEN; i++){
                if (count[i].occurrences!=0){
                        printf("Count[%02d]=%02d;\n", count[i].word_length, count[i].occurrences);
                }
        }
}

void print_count_pw(){
	for (int i = 0; i < MAX_WORD_LEN; i++){
		if (count[i].uniques!=0){
			qsort(count[i].wordarray, MAX_WORDS_FILE, sizeof(char)*MAX_WORD_LEN, comparator_str);
			printf("Count[%02d]=%02d; (words: \"", count[i].word_length, count[i].occurrences); //everything before the word list

			if (count[i].uniques==1) printf("%s\")\n", count[i].wordarray[0]); //format for just one unique
			else{ //format for 2+ uniques
				printf("%s\"", count[i].wordarray[0]);
				int j;
				for (j=1; j < count[i].uniques-1; j++) printf(", \"%s\"", count[i].wordarray[j]);
				printf(" and \"%s\")\n", count[i].wordarray[j]);
			}
		}
	}
}

int comparator(const void *p, const void *q){//compare function for qsorting Entries
	Entry *entryp = (Entry *)p;
	Entry *entryq = (Entry *)q;
	return (entryq->occurrences - entryp->occurrences);
}

int comparator_str(const void *a, const void *b){ //compare function for qsorting words
	char *stra = (char*) a;
	char *strb = (char*) b; 
	if (!strcmp(strb,"")) return -1; //tricks qsort into thinking that strb, which is empty, is "bigger" (later alphabetically) than strb and therefore places strb AFTER stra, since qsort sorts in ascending order.
	else return (strcmp(stra, strb));
}

//MAIN PROGRAM

int main(int argc, char **argv){

	//SETUP
	FILE *input;
	int sortflag = 0; //detects sort flag
	int pwflag = 0; //detects print-words flag

	for (int i = 0; i < MAX_WORD_LEN; i++){ //initializing count array
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
		
		if (!strcmp("--print-words", argv[i])) {
			//printf("--print-words detected");
			pwflag = 1;
		}
	}
	
	char tmpstr[MAX_FILE_SIZE];//this is the string that fgets dumps lines to
	while (fgets(tmpstr, MAX_FILE_SIZE, input) != NULL){
		
		process_line(tmpstr, pwflag);//tokenizes the line and adds to word totals
	}
	//done calculating word totals
	
	
	if (sortflag){
		qsort(count, MAX_WORD_LEN, sizeof(Entry), comparator);
	}
	if (pwflag){
		print_count_pw(); //Let's put the pwflag check here and have two different print_count functions.
	}
	else{
		print_count();
	}
	return 0;
}
