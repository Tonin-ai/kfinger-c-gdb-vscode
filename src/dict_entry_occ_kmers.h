#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "read_start_tuple.h"
typedef struct dict_entry_occ_kmers{

        int* kmer; //chiave
        rs_tuple** head; //primo elemento
        int size;
	int used;

} dict_entry_kmers;


dict_entry_kmers* create_dict_entry(int* k);
int add_in_dict_entry_kmers(dict_entry_kmers* entry,int r, int s);

