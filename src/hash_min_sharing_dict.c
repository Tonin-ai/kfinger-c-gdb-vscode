#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include "min_sharing_dict.h"

typedef struct hash_msdict{

        min_sharing_dict** dicts_list;//lista di puntatori a dizionari min_sharing_dict
        int size; //numero di entry della lista

} hash_msdict;

void initHashMSDict(hash_msdict* msdict,int size);
int add_in_hash_msdict(min_sharing_dict** dict,int* reads);
void viewHashMSDict(hash_msdict* msdict);

/*
in: msdict,size
out: void
il dizionario msdict viene inizializzato con un numero di entry pari al paramentro size passato dall'utente
*/

void initHashMSDict(hash_msdict* msdict,int size){
        msdict->size=size;
        msdict->dicts_list=(min_sharing_dict**)malloc(msdict->size * sizeof(min_sharing_dict*));
        for(int i=0;i<msdict->size;i++) msdict->dicts_list[i]=NULL;
}

/*
in: dict,reads
out: 1 se l'inserimento della read che ha per chiave reads all'interno del dizionario dict va a buon fine
*/

int add_in_hash_msdict(min_sharing_dict** dict,int* reads){
        if(!*dict){
                *dict = (min_sharing_dict*)malloc(sizeof(min_sharing_dict));
                initMSDict(*dict);
        }
        return add_in_msdict(*dict,reads);

}

/*
in: msdict
vengono visualizzate tutte le entry presenti nella lista di dizionari
*/

void viewHashMSDict(hash_msdict* msdict){
        for(int i=0;i<msdict->size;i++){
                if(msdict->dicts_list[i]){
                        //printf("ciao\n");
                        //printf("%d\n",hdict->dicts_list[i]->size);
                        viewMSDict(msdict->dicts_list[i]);
                }
        }
}

