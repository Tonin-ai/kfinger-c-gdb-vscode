#include <stdlib.h>
#include <stdio.h>
void init_menu(char* file){
	FILE * fp;
    	char * line = NULL;
    	size_t len = 0;
    	ssize_t read;

    	fp = fopen(file, "r");
    	if (fp == NULL) exit(EXIT_FAILURE);

    	while ((read = getline(&line, &len, fp)) != -1) {
        	printf("%s", line);
    	}

    	fclose(fp);
    	if (line)
        free(line);
}
