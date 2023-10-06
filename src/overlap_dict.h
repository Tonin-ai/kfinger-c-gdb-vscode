#include <malloc.h>
#include <string.h>
#include "overlap_dict_entry.h"
typedef struct overlap_dict{

        overlap_dict_entry** head; //primo elemento
        int size;
        int used;

}overlap_dict;

void initODict(overlap_dict* dict);
overlap_dict_entry* add_odict_entry(overlap_dict* dict, int* reads);
overlap_dict_entry* find_odict_entry(overlap_dict* dict, int* reads);
int add_in_odict(overlap_dict* dict, int* reads,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9);
void viewODict(overlap_dict* dict);
