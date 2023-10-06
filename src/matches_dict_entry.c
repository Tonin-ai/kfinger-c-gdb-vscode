#include <malloc.h>
typedef struct matches_dict_entry{

        int* reads;
        int* value;
	int count; //numero di volte in cui appaiono le read, va a sostituire il dizionareo min_shared_dict

}matches_dict_entry;

matches_dict_entry* createMDictEntry(int *r);
int update_matches_dict_entry(matches_dict_entry* entry,int first,int second);

/*
in: r
out: matches_dict_entry
viene creato un puntatore a una entry che ha come chiave r (sarebbe reads)
*/
matches_dict_entry* createMDictEntry(int *r){
        matches_dict_entry* p = (matches_dict_entry*)malloc(sizeof(matches_dict_entry));
        p->reads=r;
        p->value=NULL;
	p->count=0;
        return p;
}

/*
in: entry,first,second
out: 1 se è stato possibile aggiornare i valori in entry con first e second
*/
int update_matches_dict_entry(matches_dict_entry* entry,int first,int second){

	entry->count++;

	if(!entry->value){
		entry->value=(int*)malloc(4*sizeof(int));
		entry->value[0]=first;
		entry->value[1]=second;
		entry->value[2]=first;
                entry->value[3]=second;
		return 1;
	}

	if(entry->value[0]>first){
		entry->value[0]=first;
                entry->value[1]=second;
	}
	if(entry->value[2]<first){
		entry->value[2]=first;
                entry->value[3]=second;
	}
	return 1;
}
