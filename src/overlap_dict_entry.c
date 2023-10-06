#include <malloc.h>
typedef struct overlap_dict_entry{

        int* reads;
        int* value;

}overlap_dict_entry;

overlap_dict_entry* createODictEntry(int *r);
int update_overlap_dict_entry(overlap_dict_entry* entry,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9);

/*
in: r
out: matches_dict_entry
viene creato un puntatore a una entry che ha come chiave r (sarebbe reads)
*/
overlap_dict_entry* createODictEntry(int *r){
        overlap_dict_entry* p = (overlap_dict_entry*)malloc(sizeof(overlap_dict_entry));
        p->reads=r;
        p->value=NULL;
        return p;
}

int update_overlap_dict_entry(overlap_dict_entry* entry,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9){

	if(!entry->value || p9>entry->value[8]){
        	if(!entry->value){entry->value=(int*)malloc(9*sizeof(int));}
        	entry->value[0]=p1;
        	entry->value[1]=p2;
        	entry->value[2]=p3;
        	entry->value[3]=p4;
        	entry->value[4]=p5;
        	entry->value[5]=p6;
        	entry->value[6]=p7;
        	entry->value[7]=p8;
        	entry->value[8]=p9;
	}

        return 1;
}


