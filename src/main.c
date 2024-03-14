
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

#include "parameters.h"
#include "hash_functions.h"
#include "list_operations.h"
#include "menu.h"
#include "fingerprint.h"
#include "hash_dict.h"
#include "hash_matches_dict.h"
#include "hash_min_sharing_dict.h"
#include "hash_overlap_dict.h"
#include "overlap_list.h"
#include "pthread.h"

#include "creazione_fingerprintlist.h"
#include "creazione_dizionario.h"
#include "creazione_msdict.h"
#include "creazione_odict.h"
#include "calcolo_olist.h"

#include "stampa_res.h"

#define MAX_LINE_LENGTH 10

int main(int argc, char **argv)
{
	unsigned int hdictsize = INT_MAX / 100;
	
	init_menu("./intro.txt"); // visualizzazione intto

	// MALLOC SECTION
	fingerprint *f_list = (fingerprint *)malloc(sizeof(fingerprint) * INT_MAX / 40); // inizializzazione della lista di read con quante read ci sono all'interno del file
	pthread_mutex_t *mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * hdictsize);
	hash_dict *hdict = (hash_dict *)malloc(sizeof(hash_dict));	   // creazion hash_dict
	hash_dict *hdicttemp = (hash_dict *)malloc(sizeof(hash_dict)); // creazion hash_dict
	hash_mdict *hmdict = (hash_mdict *)malloc(sizeof(hash_mdict));
	hash_odict *hodict = (hash_odict *)malloc(sizeof(hash_odict));
	olist *overlap_list = (olist *)malloc(sizeof(olist));

	parameters *p = init_parameters();

	// INIT SECTION
	initHashDict(hdict, hdictsize);		// inizializzazione di hdict
	initHashDict(hdicttemp, hdictsize); // inizializzazione di hdicttemp
	initHashMDict(hmdict, hdictsize);
	initHashODict(hodict, hdictsize);
	initolist(overlap_list);

	for (unsigned int i = 0; i < hdictsize; i++)
		pthread_mutex_init(&mutex[i], NULL);

	time_t seconds = time(NULL); // comincio a prendere il tempo
	unsigned int num_fingerprint = crea_fingerprint_list(f_list);
	printf("Secondi lettura fingerprint: %ld\n", time(NULL) - seconds);

	seconds = time(NULL); // viene resettato il tempo
	crea_dizionario(f_list, num_fingerprint, hdict, hdicttemp, mutex, p);
	printf("Secondi creazione dizionario: %ld\n", time(NULL) - seconds); // diplsy tempo creazione di>

	seconds = time(NULL);
	crea_msdict(hmdict, hdict, mutex);
	printf("Secondi creazione msdict e mdict: %ld\n", time(NULL) - seconds); // viene mostrato quanto tempo ci è voluto a create matches_dict e min_sharing_dict

	seconds = time(NULL);
	crea_odict(f_list, hmdict, hodict, mutex, p);
	printf("Secondi calcolo overlaps: %ld\n", time(NULL) - seconds); // viene mostrato quanto tempo ci è voluto a create matches_dict e min_sharing_dict

	seconds = time(NULL);
	calcola_olist(hodict, overlap_list, hdictsize);
	printf("Secondi calcolo lista di overlaps: %ld\n", time(NULL) - seconds);

	if (argc == 2)
	{
		stampa_risultati(hdict, hmdict, hodict, overlap_list, p->k);
	}

	// FREE/DESTRY SECTION
	for (unsigned int i = 0; i < hdictsize; i++)
		pthread_mutex_destroy(&mutex[i]);
	free(hodict);
	free(hmdict);
	free(hdict);

	return 0;
}