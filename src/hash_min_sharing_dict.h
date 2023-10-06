#include "min_sharing_dict.h"

typedef struct hash_msdict{

        min_sharing_dict** dicts_list;
        int size;

} hash_msdict;

void initHashMSDict(hash_msdict* msdict,int size);
int add_in_hash_msdict(min_sharing_dict** dict,int* reads);
void viewHashMSDict(hash_msdict* msdict);
