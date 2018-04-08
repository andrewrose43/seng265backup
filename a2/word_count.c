//HEADER FILES

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//Defining the Entry struct out of which the list is composed
typedef struct entry_struct{
        int word_length;
        int occurrences;
	struct entry_struct *next;
} Entry;


//GLOBAL VARIABLES

int longest; //the longest word recorded
Entry *head; //pointer to the first Entry in the linked list


//FUNCTION DECLARATIONS

void process_line (char *input_line); //splits a line into tokens and uses those tokens to modify the list of Entries

void print_entries(); //generates output

Entry *new_entry_empty (); //creates a new Entry with no occurrences

Entry *new_entry_full (); //creates a new Entry with one occurrence

void *emalloc(size_t n); //wrapper function provided by SENG 265

void free_list(Entry * e); //frees the entire linked list


//FUNCTIONS

void process_line (char *input_line){
	
	Entry *pointer; //this pointer allows us to scroll through the linked list
	char *t;

	t = strtok(input_line, " .,;()\n");
	//in the next line, that t in the loop condition counts as true so long as t exists (so long as we have not run out of tokens)
        while(t){
		pointer = head; //start from the beginning of the list
		
		if (strlen(t)<=longest){ //if there exists an Entry for words of length strlen(t)
			for (int i = 1; i<strlen(t); i++){
				pointer = pointer->next;
			}
			pointer->occurrences++; //add 1 to the number of words of length strlen(t) that have occurred
		}
		else if (strlen(t)==longest+1){ //if the token is 1 character longer than the longest word previously recorded
			for (int j = 1; j<longest; j++){
				pointer = pointer->next;
			}
			pointer->next = new_entry_full(); //make a new entry for words of this length
		}
		else { //strlen(t) > longest+1
			for (int k = 1; k<longest; k++){
				pointer = pointer->next;
			}
			for (int l = longest; l<strlen(t)-1; l++){
				pointer->next = new_entry_empty(); //make entries with zero occurrences for word lengths between longest and strlen(t) //THIS IS LINE 61
				pointer = pointer->next;

			}
			pointer->next = new_entry_full(); //make a new entry for words of this length
		}

                t = strtok(NULL, " .,;()\n"); //next token
        }
        return;
}	

void print_entries(){
	Entry *curr = head;
	for (int i = 1; i <= longest; i++){
		if (curr->occurrences!=0) printf("Count[%02d]=%02d;\n", curr->word_length, curr->occurrences);
		curr = curr->next;
	}

}

Entry *new_entry_empty (){
	Entry *newe = (Entry *) emalloc (sizeof(Entry));
	newe->word_length = longest+1;
	newe->occurrences = 0;
	newe->next = NULL;
	longest++;
	return newe;
}

Entry *new_entry_full (){
	Entry *newe = (Entry *) emalloc (sizeof(Entry));
	newe->word_length = longest+1;
	newe->occurrences = 1;
	newe->next = NULL;
	longest++;
	return newe;
}

void *emalloc(size_t n){
	void *p;
	p = malloc(n);
	if (p==NULL){
		fprintf(stderr, "malloc of %u bytes failed", (unsigned int) n);
	exit(1);
	}
	return p;
}

void free_list(Entry * e){
	if (e->next==NULL){
		free(e);
		return;
	}
	free_list(e->next);
	free(e);	
}


//MAIN PROGRAM

int main(int argc, char **argv){

	//SETUP
	FILE *input;
	int sortflag = 0; //is flipped if the sort option is desired

	longest = 1; //it is initialized to 1 even though no words have yet been detected. This reflects the existence of the word-length-1 node from the beginning. longest is never visible to the user, so this behind-the-scenes disparity is never revealed in the case that no words exist in the input file.

	//Instantiating the first Entry node in the list
	head = (Entry *) emalloc(sizeof(Entry));
	head->word_length = 1;
	head->occurrences = 0;
	head->next = NULL;

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

                /*if (!strcmp("--sort", argv[i])) {
                        //printf("--sort detected");
                        sortflag = 1;
                }*/ //this would be uncommented if I had gotten to Part B
        }

	size_t read;
	char *line = NULL;
	size_t len = 0;

	//Generate the list
	while ((read = getline(&line, &len, input)) != -1){
		process_line(line);
	}

	free(line); //free dynamic memory
	free_list(head);
	
	fclose(input); //close the file

	print_entries(); //generate output
	

	return 0;
}
