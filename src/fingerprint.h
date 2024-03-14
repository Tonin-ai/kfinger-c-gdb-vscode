typedef struct fingerprint{
        unsigned int id;
        unsigned int isreverse;
        unsigned int* list;
        unsigned int size;
        unsigned int used;

} fingerprint;

extern void initArray(fingerprint *f);

int addInFingerprintList(fingerprint *f, int n);

void viewList(fingerprint *f);




