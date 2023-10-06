#include <malloc.h>
typedef struct min_sharing_dict_entry{

        int* reads;
        int value;

}min_sharing_dict_entry;

min_sharing_dict_entry* createMSDictEntry(int *r);

