#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "read_start_tuple.h"
typedef struct dict_entry_occ_kmers{

	int* kmer; //chiave
	rs_tuple** head; //lista di puntatori a coppie (READ,START)
	int size; //numeri di entry stimate
	int used; //numero di entry effettivamente inserite

} dict_entry_kmers;


dict_entry_kmers* create_dict_entry(int* kmer);
int add_in_dict_entry_kmers(dict_entry_kmers* entry,int r, int s);

/*
in: kmer
out: dict_entry_kmers con chiave kmer e numero di entry stimate
stabilite dal programmatore
*/

dict_entry_kmers* create_dict_entry(int* kmer){
	dict_entry_kmers* entry=(dict_entry_kmers*)malloc(sizeof(dict_entry_kmers));
	entry->kmer = kmer;
	entry->size = 10;
	entry->head = (rs_tuple**)malloc(entry->size * sizeof(rs_tuple*));
	entry->used = 0;

	return entry;
}


/*
in: entry,r,s
out: 1 se l'inseimento della coppia (READ,START) è andata a buon fine
*/

int add_in_dict_entry_kmers(dict_entry_kmers* entry,int r, int s){
	if(entry->used == entry->size){ //Controllo se c'è bisogno di allocare altra memoria
		entry->size*=2;
		entry->head =  realloc(entry->head, entry->size * sizeof(rs_tuple*));
	}
	entry->head[entry->used++] = create_rs_tuple(r, s); //La nuova entry sarà bessa in testa alla lista delle entry,
							    //il puntatore alla entry è data dalla funzione create_rs_tuple(r, s)
	return 1;
}

