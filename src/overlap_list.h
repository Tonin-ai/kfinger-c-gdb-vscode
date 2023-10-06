

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
