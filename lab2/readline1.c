#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

size_t size = 100;

int read_line (char *line){
	
	int r, numchar = 0;
	char ch;
	
	do{
		ch = fgetc (stdin);
	
		if (ch == '\n'){
			line[numchar] = '\0';		
			return numchar;
		}

		line[numchar++] = ch;
	} while (ch != EOF);
	
	return -1;

}




	

