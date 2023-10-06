#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dict_entry_occ_kmers.h"
typedef struct dict_occ_kmers
{

	dict_entry_kmers **head; // puntatore alla lista di entry
	int size;				 // numero di entry stimate
	int used;				 // numero di entry effettivamente usate

} dict_kmers;

void initDict(dict_kmers *dict);
dict_entry_kmers *add_dict_entry(dict_kmers *dict, int *kmer);
dict_entry_kmers *find_dict_entry(dict_kmers *dict, int *kmer, int k);
int add_in_dict(dict_kmers *dict, int *kmer, int r, int s, int k);
int memCompare(dict_entry_kmers *entry, int *kmer, int k);
void viewDict(dict_kmers *dict, int k);

// le funzioni per il dizionario prendono sempre come primo valore il dizionario di riferimetno

// aggiunta di una nuova entry all'interno del dizionario

/*
in: dict
out: void
viene allocata dinamicamente della memoria per contenere le entry
*/
void initDict(dict_kmers *dict)
{
	dict->size = 10;
	dict->head = (dict_entry_kmers **)malloc(dict->size * sizeof(dict_entry_kmers *));
	dict->used = 0;
}

/*
in: dict, kmer
out: dict_entry_kmers*
viene preso in input il dizionario di riferimento e il kmer che vogliamo inserire
ai kmer in futuro verranno associate liste di coppie (READ,START)
*/

dict_entry_kmers *add_dict_entry(dict_kmers *dict, int *kmer)
{
	if (dict->size == dict->used)
	{ // si controlla se c'è bisogno di allocare ulteriore memoria
		dict->size *= 2;
		dict->head = realloc(dict->head, dict->size * sizeof(dict_kmers *));
	}
	dict->head[dict->used++] = create_dict_entry(kmer); // viene inserito allìinterno del dizionario l'entry che ha per chiave il kmer
	return dict->head[dict->used - 1];
}

// cerca la entry (kmer e lista di r,s)
/*
in: dict, kmer,k
out: dict_entry_kmers*
viene preso input un dizionario un kmer e il parametro k per cercare se effettivamente è presento
all'interno del dizionario una entry che ha per chiave il kmer.
Se è presente viene resituito il puntatore alla entry, NULL altimenti.
*/
dict_entry_kmers *find_dict_entry(dict_kmers *dict, int *kmer, int k)
{
	// for (int i = 0;i<dict->used;i++){if(memCompare(dict->head[i],kmer,k)) return dict->head[i];}
	for (int i = 0; i < dict->used; i++)
	{
		if (!memcmp(dict->head[i]->kmer, kmer, k * sizeof(int)))
			return dict->head[i];
	}
	return NULL;
}

// aggiunge alla entry (kmer e lista di r,s) una coppia (r,s)
// cosa principale
/*
in: dict, kmer, r, s, k
out: 1 se viene inserita la coppia (READ,START) nella entry del zionario dict che ha per hiave il kmer
*/
int add_in_dict(dict_kmers *dict, int *kmer, int r, int s, int k)
{
	dict_entry_kmers *entry = find_dict_entry(dict, kmer, k);
	if (entry != NULL)
	{
		return add_in_dict_entry_kmers(entry, r, s);
	}

	else
	{
		return add_in_dict_entry_kmers(add_dict_entry(dict, kmer), r, s);
	}
}
// implementaizone alternativa al memcmp
int memCompare(dict_entry_kmers *entry, int *kmer, int k)
{
	for (int i = 0; i < k; i++)
		if (entry->kmer[i] != kmer[i])
			return 0;
	return 1;
}
/*
in: dict,k
out: void
Viene vistualizzato il dizionario
*/
void viewDict(dict_kmers *dict, int k)
{
	for (int i = 0; i < dict->used; i++)
	{
		dict_entry_kmers *entry = dict->head[i];
		printf("[");
		for (int j = 0; j < k; j++)
		{
			printf("%d ", entry->kmer[j]);
		}
		printf("]=");
		for (int j = 0; j < entry->used; j++)
		{
			printf("(%d,%d)", entry->head[j]->read, entry->head[j]->start);
		}
		// printf("\n");
	}
}
