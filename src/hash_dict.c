#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include "dict_occ_kmers.h"

typedef struct hash_dict{

        dict_kmers** dicts_list; //lista di puntatori ai dizionari
	int size; //numero di entry del dizionario

} hash_dict;

void initHashDict(hash_dict* hdict,int size);
int add_in_hash_dict(dict_kmers** dict,int* kmer,int r,int s,int k);
void viewHashDict(hash_dict* hdict,int k);

/*
in: hsdict,size
out: void
viengono allocate al dizionario un numero di entry pari al parametro size
passato per input al dizionario hdict
*/

void initHashDict(hash_dict* hdict,int size){
	hdict->size=size;
	hdict->dicts_list=(dict_kmers**)malloc(hdict->size * sizeof(dict_kmers*));
	for(int i=0;i<hdict->size;i++) hdict->dicts_list[i]=NULL;
}
/*
in: dict,kmer,r,s,k
out: 1 se viene inserita la entry che ha pre chiave kmer e coppia (READ,START) all'interno del dizionario dict
*/
int add_in_hash_dict(dict_kmers** dict,int* kmer,int r,int s,int k){
	if(!*dict){//controlla se la entry di hdict relativa al dizionario dict è ha già della memoria allocata
		*dict = (dict_kmers*)malloc(sizeof(dict_kmers));
		initDict(*dict);
	}
	return add_in_dict(*dict,kmer,r,s,k);

}

/*
in: hdict, k
out: void
vengono visualizzati tutti i dizionari presenti all'interno di hdict
*/

void viewHashDict(hash_dict* hdict,int k){
	for(int i=0;i<hdict->size;i++){
		if(hdict->dicts_list[i]){
			//printf("ciao\n");
			//printf("%d\n",hdict->dicts_list[i]->size);
			viewDict(hdict->dicts_list[i],k);
			printf("\n");
		}
	}
}
