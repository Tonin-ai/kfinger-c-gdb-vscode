#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include "dict_occ_kmers.h"

typedef struct hash_dict{

        dict_kmers** dicts_list;
        int size;

} hash_dict;

void initHashDict(hash_dict* hdict,int size);
int add_in_hash_dict(dict_kmers** dict,int* kmer,int r,int s,int k);
void viewHashDict(hash_dict* hdict,int k);
