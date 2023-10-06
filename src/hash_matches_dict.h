#include "matches_dict.h"

typedef struct hash_mdict{

        matches_dict** dicts_list;
        int size;

} hash_mdict;

void initHashMDict(hash_mdict* mdict,int size);
int add_in_hash_mdict(matches_dict** dict,int* reads,int first, int second);
void viewHashMDict(hash_mdict* mdict);
