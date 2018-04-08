#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
/*
	FILE *fp;
	fp = fopen("noodled.txt", "w");
	fprintf(fp, "%s", "this will be written to noodled.txt\n");
	fclose(fp);
	return(0);
*/
/*
	char trim[9];
	fgets(trim, 3, stdin);
	printf("%s", trim);
*/
/*
	char *a[2];
	a[0] = "blah";
	a[1] = "hmm";
	printf("%s", a[0]);
	printf("%s", a[1]);
	return(0);
*/
/*
	char a[2][15]; //a[number of strings][length of each string] (char arrays, not string literals)
	strncpy(a[0], "blah", 4);
	strncpy(a[1], "hmm", 3);
	printf("%s", a[0]);
	printf("%s", a[1]);
	return(0);
*/	
/*
	char a[2][15];
	printf("%s is the contents", a[1]);
	return(0);
*/	
/*
	double num = 469.78;
	printf("%8.6f", num);
*/
/*
	int *a = (int*)malloc(3*sizeof(int));
	//check to ensure malloc succeeded...
	a[0] = 1;
	for (int i = 0; i < 3; i++){
		printf("%d\n", *(a+i));
	}
	int b[3];
	b = {1,2,3};
	//int b[3] = {1,2,3};
	for (int i = 0; i < 3; i++){
		printf("%d\n", *(b+i));
	}
*/

	fputc('t', stdout);

	
	
	return 0;	
}
