#include <string.h>
#include "min_sharing_dict_entry.h"
typedef struct min_sharing_dict{

        min_sharing_dict_entry** head;
        unsigned int size;
        unsigned int used;

}min_sharing_dict;

void initMSDict(min_sharing_dict* dict);
min_sharing_dict_entry*  add_msdict_entry(min_sharing_dict* dict, int* reads);
min_sharing_dict_entry* find_msdict_entry(min_sharing_dict* dict, int* reads);
int add_in_msdict(min_sharing_dict* dict, int* reads);
void viewMSDict(min_sharing_dict* dict);
