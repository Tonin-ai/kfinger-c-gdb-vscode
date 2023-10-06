#include <string.h>
#include "min_sharing_dict_entry.h"
typedef struct min_sharing_dict{

	min_sharing_dict_entry** head;
	int size;
	int used;

}min_sharing_dict;

void initMSDict(min_sharing_dict* dict);
min_sharing_dict_entry*  add_msdict_entry(min_sharing_dict* dict, int* reads);
min_sharing_dict_entry* find_msdict_entry(min_sharing_dict* dict, int* reads);
int add_in_msdict(min_sharing_dict* dict, int* reads);
void viewMSDict(min_sharing_dict* dict);

/*
in: dict
out: void
viene inizializzato il dizionario dict a cui vengono date 10 entry
*/
void initMSDict(min_sharing_dict* dict){
        dict->size=10;
        dict->head=(min_sharing_dict_entry**)malloc(dict->size*sizeof(min_sharing_dict_entry*));
        dict->used=0;
}

/*
in: dict,reads
out: min_sharing_dict_entry
aggiunge all'interno del dizionario dict una entry che ha come chiave reads
*/
min_sharing_dict_entry*  add_msdict_entry(min_sharing_dict* dict, int* reads){
        if (dict->size == dict->used){
                dict->size*=2;
                dict->head = realloc(dict->head, dict->size * sizeof(min_sharing_dict_entry**));
        }
        dict->head[dict->used++] = createMSDictEntry(reads);
        return dict->head[dict->used-1];
}

/*
in: dict,reads
out: min_sharing_dict_entry
restituisce l'indirizzo della entry che ha come chiave reads passato in input, NULL altrimenti
*/
min_sharing_dict_entry* find_msdict_entry(min_sharing_dict* dict, int* reads){
        for (int i = 0;i<dict->used;i++){if(!memcmp(dict->head[i]->reads,reads,2*sizeof(int))) return dict->head[i];}
        return NULL;
}

/*
in: dict, reads
out: 1 se è stato possibile aggiornare il valore presente all'interno della entry con chiave reads
*/
int add_in_msdict(min_sharing_dict* dict, int* reads){
        min_sharing_dict_entry* entry = find_msdict_entry(dict,reads);
        if(entry != NULL){entry->value++;return 1;}

        else{add_msdict_entry(dict,reads)->value++;return 1;}
}

/*
in: dict
out: void
vengono visualizzate le entry del dizionario dict
*/
void viewMSDict(min_sharing_dict* dict){
	for(int i=0;i<dict->used;i++){
		printf("[%d,%d]:%d ",dict->head[i]->reads[0],dict->head[i]->reads[1],dict->head[i]->value);
	}
}
