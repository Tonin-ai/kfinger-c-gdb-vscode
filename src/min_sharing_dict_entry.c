#include <malloc.h>
typedef struct min_sharing_dict_entry{

	int* reads;
	int value;

}min_sharing_dict_entry;

min_sharing_dict_entry* createMSDictEntry(int *r);

/*
in: r
out: min_sharing_dict_entry
Viene inizializzata una entry con chiave r e valore = 0
*/
min_sharing_dict_entry* createMSDictEntry(int *r){
	min_sharing_dict_entry* p = (min_sharing_dict_entry*)malloc(sizeof(min_sharing_dict_entry));
	p->reads=r;
	p->value=0;
	return p;
}
