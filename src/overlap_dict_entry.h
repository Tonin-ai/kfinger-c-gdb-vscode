#include <malloc.h>
typedef struct overlap_dict_entry{

        int* reads;
        int* value;

}overlap_dict_entry;

overlap_dict_entry* createODictEntry(int *r);
int update_overlap_dict_entry(overlap_dict_entry* entry,int p1,int p2,int p3,int p4,int p5,int p6,int p7,int p8,int p9);

