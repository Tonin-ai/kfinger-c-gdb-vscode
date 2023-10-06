#include <malloc.h>
#include <string.h>
#include "matches_dict_entry.h"
typedef struct matches_dict{

        matches_dict_entry** head; //primo elemento
        int size;
        int used;

}matches_dict;

void initMDict(matches_dict* dict);
matches_dict_entry* add_mdict_entry(matches_dict* dict, int* reads);
matches_dict_entry* find_mdict_entry(matches_dict* dict, int* reads);
int add_in_mdict(matches_dict* dict, int* reads,int first, int second);
void viewMDict(matches_dict* dict);
