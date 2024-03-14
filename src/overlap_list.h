

#include<malloc.h>
#include"overlap_list_entry.h"

typedef struct olist{

	olistentry** entries;
	int used;
	int size;

}olist;


void initolist(olist* dict);
olistentry* add_olist_entry(olist* dict, int id1,int flag1,int id2,int flag2,int lenght1,int lenght2,int start1,int end1,int start2,int end2,int strand);
 void stampolist(olist* list);
