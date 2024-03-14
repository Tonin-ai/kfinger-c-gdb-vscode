
#include<malloc.h>
#include"overlap_list_entry.h"

typedef struct olist{

	olistentry** entries;
	unsigned int used;
	unsigned int size;

}olist;


void initolist(olist* dict);

olistentry* add_olist_entry(olist* dict, int id1,int flag1,int id2,int flag2,int lenght1,int lenght2,int start1,int end1,int start2,int end2,int strand);

void stampolist(olist* list);

void initolist(olist* dict){
	dict->size=1000;
        dict->entries = (olistentry**)malloc(dict->size*sizeof(olistentry*));
        dict->used=0;
}

olistentry* add_olist_entry(olist* dict, int id1,int flag1,int id2,int flag2,int lenght1,int lenght2,int start1,int end1,int start2,int end2,int strand){
        if (dict->size == dict->used){//Controlla se si deve allocare altra memoria
                dict->size*=2;
                dict->entries = realloc(dict->entries, dict->size * sizeof(olistentry*));
        }
        dict->entries[dict->used++]=createolistoentry(id1,flag1,id2,flag2,lenght1,lenght2,start1,end1,start2,end2,strand);
        return dict->entries[dict->used-1];
}

void stampolist(olist* list){


	for(int i=0;i<list->used;i++){

		int* temp=list->entries[i]->elements;

		for(int j=0;j<11;j++){
			printf("%d ",temp[j]);
		}
		printf("\n");

	}


}
