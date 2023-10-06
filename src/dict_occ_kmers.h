#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dict_entry_occ_kmers.h"
typedef struct dict_occ_kmers{

        dict_entry_kmers** head; //primo elemento
        int size;
        int used;

} dict_kmers;

void initDict(dict_kmers* dict);
dict_entry_kmers*  add_dict_entry(dict_kmers* dict, int* kmer);
dict_entry_kmers* find_dict_entry(dict_kmers* dict, int* kmer,int k);
int add_in_dict(dict_kmers* dict, int* kmer,int r, int s, int k);
int memCompare(dict_entry_kmers* entry, int* kmer, int k);
void viewDict(dict_kmers* dict,int k);
