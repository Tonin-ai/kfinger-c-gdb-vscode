#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fingerprint.h"
#include "limits.h"


#define MAX_LINE_LENGTH 10

unsigned int crea_fingerprint_list(fingerprint *f_list){						   // lista di puntatori a fingerprint
	char line[MAX_LINE_LENGTH], temp[MAX_LINE_LENGTH];		   // stringhe di appoggio
	FILE *fp = fopen("../input/fingerprint_ecoli_CFL_ICFL_COMB-30.txt", "r"); // apertura file input
	// FILE* fp = fopen("../../progettokfinger/input.txt", "r"); //apertura file input


	if (fp == NULL)
	{ // controllo se è presente il file input
		printf("no such file.");
		return 0;
	}

	unsigned int i = -1;
	while (fscanf(fp, "%s", line) > 0)
	{ // finchè c'è qualcosa da leggere ne file
		if (strcmp(line, "|"))
		{ // ignoriamo i |
			int linetemp = strlen(line);
			if (linetemp >= 3 && line[linetemp - 2] == '_')
			{ // verifico se è una stringa che come penultimo carattere ha _
				// printf("%d\n",(f_list+i)->size);
				// if(!atoi(line)){
				// if(i>=0) viewList(f_list+i); //visualizzo l'ultimo fingerprint
				i++;
				sscanf(line, "%[^_]", temp);
				(f_list + i)->id = atoi(temp);
				sscanf(line, "%*[^_]%*c%s", temp);
				(f_list + i)->isreverse = atoi(temp);
				initArray(f_list + i); // viene inizializzata la fingerprint che avrà l'id e isreverse letti
									   // printf("[Id : %d ,Reverse: %d]\n",(f_list+i)->id,(f_list+i)->isreverse);
			}

			else
			{
				addInFingerprintList(f_list + i, atoi(line));
				// rscount++;
			} // viene aggiunto l'intero alla fingerprint
		}
	}
	
	if (i == -1)
	{
		printf("Non sono state lette righe.\n");
		return 0;
	}

    return i;
}