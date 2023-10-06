#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <limits.h>
#include "overlap_dict.h"

typedef struct hash_odict{

        overlap_dict** dicts_list; //lista di puntatori a dizionari
        int size; //numero di dizionari

} hash_odict;

void initHashODict(hash_odict* odict,int size);
int add_in_hash_odict(overlap_dict** dict,int* reads,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9);
void viewHashODict(hash_odict* odict);

