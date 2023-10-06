#include <malloc.h>
#include <string.h>
#include "overlap_dict_entry.h"
typedef struct overlap_dict{

        overlap_dict_entry** head; //primo elemento
        int size;
        int used;

}overlap_dict;

void initODict(overlap_dict* dict);
overlap_dict_entry* add_odict_entry(overlap_dict* dict, int* reads);
overlap_dict_entry* find_odict_entry(overlap_dict* dict, int* reads);
int add_in_odict(overlap_dict* dict, int* reads,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9);
void viewODict(overlap_dict* dict);

/*
in: dict
out: void
Inizializza il dizionario dict passato come argomento e alloca spazio per poter inserire le entry
*/
void initODict(overlap_dict* dict){
        dict->size=10;
        dict->head=(overlap_dict_entry**)malloc(dict->size*sizeof(overlap_dict_entry*));
        dict->used=0;
}

/*
in: dict,reads
out: matches_dict_entry
aggiunge all'interno del dizionario duct una entry con chiave reads passata come argomento
*/

overlap_dict_entry* add_odict_entry(overlap_dict* dict, int* reads){
        if (dict->size == dict->used){//Controlla se si deve allocare altra memoria
                dict->size*=2;
                dict->head = realloc(dict->head, dict->size * sizeof(overlap_dict_entry*));
        }
        dict->head[dict->used++]= createODictEntry(reads);
        return dict->head[dict->used-1];
}

/*
in: dict,reads
out: matches_dict_entry
ritorna l'indirizzo della entry con chiave reads, NULL se non è presente
*/
overlap_dict_entry* find_odict_entry(overlap_dict* dict, int* reads){
        for (int i = 0;i<dict->used;i++){if(!memcmp(dict->head[i]->reads,reads,2*sizeof(int))) return dict->head[i];}
        return NULL;
}

/*
in: dict,reads,first,second
out: 1 se la entry con chiave reads all'interno di dict viene aggiornata con i valori di first e sec>
*/
int add_in_odict(overlap_dict* dict, int* reads,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9){
        overlap_dict_entry* entry = find_odict_entry(dict,reads);
        if(entry != NULL){return update_overlap_dict_entry(entry,p1,p2,p3,p4,p5,p6,p7,p8,p9);}

        else{return update_overlap_dict_entry(add_odict_entry(dict,reads),p1,p2,p3,p4,p5,p6,p7,p8,p9);}
}

/*
in: dict
out: void
viengono visualizzate tutte le entry del dizionario dict
*/
void viewODict(overlap_dict* dict){
        for(int i=0;i<dict->used;i++){
                int *r=dict->head[i]->reads;
                int *value=dict->head[i]->value;
                printf("%d %d %d %d %d %d %d %d %d %d %d\n",r[0],r[1],value[0],value[1],value[2],value[3],value[4],value[5],value[6],value[7],value[8]);
        }
}

