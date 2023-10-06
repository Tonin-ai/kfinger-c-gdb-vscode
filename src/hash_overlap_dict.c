#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include "overlap_dict.h"

typedef struct hash_odict{

        overlap_dict** dicts_list; //lista di puntatori a dizionari
        int size; //numero di dizionari

} hash_odict;

void initHashODict(hash_odict* odict,int size);
int add_in_hash_odict(overlap_dict** dict,int* reads,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9);
void viewHashODict(hash_odict* odict);

/*
in: mdict,dize
out: void
viene inizializzato il dizionario con un numero di entry passate come parametro
*/

void initHashODict(hash_odict* odict,int size){
        odict->size=size;
        odict->dicts_list=(overlap_dict**)malloc(odict->size * sizeof(overlap_dict*));
        for(int i=0;i<odict->size;i++) odict->dicts_list[i]=NULL;
}

/*
in: dict,reads,first,second
oud: 1 se viene inserito correttemente la coppia (FIRST_READ,SECOND_READ) all'inerno della entry con>
*/

int add_in_hash_odict(overlap_dict** dict,int* reads,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9){
        if(!*dict){//viene controllato de è allocata memoria per il dizionario dict
                *dict = (overlap_dict*)malloc(sizeof(overlap_dict));
                initODict(*dict);
        }
        return add_in_odict(*dict,reads,p1,p2,p3,p4,p5,p6,p7,p8,p9);
}

/*
in: mdict
out: void
viengono visualizzati tutti i dizionari presenti nella lista di dizionari
*/

void viewHashODict(hash_odict* odict){
        for(int i=0;i<odict->size;i++){
                if(odict->dicts_list[i]){
                        //printf("ciao\n");
                        //printf("%d\n",hdict->dicts_list[i]->size);
                        viewODict(odict->dicts_list[i]);
                }
        }
}

