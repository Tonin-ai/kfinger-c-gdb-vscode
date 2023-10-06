
#include<malloc.h>
#include"overlap_list_entry.h"

typedef struct olist{

	olistentry** entries;
	int used;
	int size;

}olist;


void initolist(olist* dict);
olistentry* add_olist_entry(olist* dict, int x1,int x2,int x3,int x4,int x5,int x6,int x7,int x8,int x9);

void stampolist(olist* list);

void initolist(olist* dict){
	dict->size=1000;
        dict->entries = (olistentry**)malloc(dict->size*sizeof(olistentry*));
        dict->used=0;
}

olistentry* add_olist_entry(olist* dict, int x1,int x2,int x3,int x4,int x5,int x6,int x7,int x8,int x9){
        if (dict->size == dict->used){//Controlla se si deve allocare altra memoria
                dict->size*=2;
                dict->entries = realloc(dict->entries, dict->size * sizeof(olistentry*));
        }
        dict->entries[dict->used++]=createolistoentry(x1,x2,x3,x4,x5,x6,x7,x8,x9);
        return dict->entries[dict->used-1];
}

void stampolist(olist* list){


	for(int i=0;i<list->used;i++){

		int* temp=list->entries[i]->elements;

		for(int j=0;j<9;j++){
			printf("%d ",temp[j]);
		}
		printf("\n");

	}


}
