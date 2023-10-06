#include <malloc.h>
typedef struct matches_dict_entry{

        int* reads;
        int* value;
	int count;

}matches_dict_entry;

matches_dict_entry* createMDictEntry(int *r);
int update_matches_dict_entry(matches_dict_entry* entry,int first,int second);
