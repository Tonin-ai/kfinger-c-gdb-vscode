#include <malloc.h>
#include <string.h>
#include "matches_dict_entry.h"
typedef struct matches_dict{

	matches_dict_entry** head; //primo elemento
        int size;
        int used;

}matches_dict;

void initMDict(matches_dict* dict);
matches_dict_entry* add_mdict_entry(matches_dict* dict, int* reads);
matches_dict_entry* find_mdict_entry(matches_dict* dict, int* reads);
int add_in_mdict(matches_dict* dict, int* reads,int first, int second);
void viewMDict(matches_dict* dict);

/*
in: dict
out: void
Inizializza il dizionario dict passato come argomento e alloca spazio per poter inserire le entry
*/
void initMDict(matches_dict* dict){
        dict->size=1;
        dict->head=(matches_dict_entry**)malloc(dict->size*sizeof(matches_dict_entry*));
        dict->used=0;
}

/*
in: dict,reads
out: matches_dict_entry
aggiunge all'interno del dizionario duct una entry con chiave reads passata come argomento
*/

matches_dict_entry* add_mdict_entry(matches_dict* dict, int* reads){
        if (dict->size == dict->used){//Controlla se si deve allocare altra memoria
                dict->size*=2;
                dict->head = realloc(dict->head, dict->size * sizeof(matches_dict_entry*));
        }
        dict->head[dict->used++]= createMDictEntry(reads);
        return dict->head[dict->used-1];
}

/*
in: dict,reads
out: matches_dict_entry
ritorna l'indirizzo della entry con chiave reads, NULL se non è presente
*/
matches_dict_entry* find_mdict_entry(matches_dict* dict, int* reads){
        for (int i = 0;i<dict->used;i++){if(!memcmp(dict->head[i]->reads,reads,2*sizeof(int))) return dict->head[i];}
        return NULL;
}

/*
in: dict,reads,first,second
out: 1 se la entry con chiave reads all'interno di dict viene aggiornata con i valori di first e second
*/
int add_in_mdict(matches_dict* dict, int* reads,int first, int second){
        matches_dict_entry* entry = find_mdict_entry(dict,reads);
        if(entry != NULL){return update_matches_dict_entry(entry,first,second);}

        else{return update_matches_dict_entry(add_mdict_entry(dict,reads),first,second);}
}

/*
in: dict
out: void
viengono visualizzate tutte le entry del dizionario dict
*/
void viewMDict(matches_dict* dict){
	for(int i=0;i<dict->used;i++){
		int *r=dict->head[i]->reads;
		int *value=dict->head[i]->value;
		printf("(%d,%d)[%d,%d,%d,%d]\n",r[0],r[1],value[0],value[1],value[2],value[3]);
	}
}
