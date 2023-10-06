#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include "matches_dict.h"

typedef struct hash_mdict{

        matches_dict** dicts_list; //lista di puntatori a dizionari
        int size; //numero di dizionari

} hash_mdict;

void initHashMDict(hash_mdict* mdict,int size);
int add_in_hash_mdict(matches_dict** dict,int* reads,int first, int second);
void viewHashMDict(hash_mdict* mdict);

/*
in: mdict,dize
out: void
viene inizializzato il dizionario con un numero di entry passate come parametro
*/

void initHashMDict(hash_mdict* mdict,int size){
        mdict->size=size;
        mdict->dicts_list=(matches_dict**)malloc(mdict->size * sizeof(matches_dict*));
        for(int i=0;i<mdict->size;i++) mdict->dicts_list[i]=NULL;
}

/*
in: dict,reads,first,second
oud: 1 se viene inserito correttemente la coppia (FIRST_READ,SECOND_READ) all'inerno della entry con chiave reads nel dizionario dict 
*/

int add_in_hash_mdict(matches_dict** dict,int* reads,int first, int second){
        if(!*dict){//viene controllato de è allocata memoria per il dizionario dict
                *dict = (matches_dict*)malloc(sizeof(matches_dict));
                initMDict(*dict);
        }
        return add_in_mdict(*dict,reads,first,second);
}

/*
in: mdict
out: void
viengono visualizzati tutti i dizionari presenti nella lista di dizionari
*/

void viewHashMDict(hash_mdict* mdict){
        for(int i=0;i<mdict->size;i++){
                if(mdict->dicts_list[i]){
                        //printf("ciao\n");
                        //printf("%d\n",hdict->dicts_list[i]->size);
                        viewMDict(mdict->dicts_list[i]);
                }
        }
}
