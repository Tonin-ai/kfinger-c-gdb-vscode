typedef struct fingerprint{
        int id;
        int isreverse;
        int* list;
        int size;
        int used;

} fingerprint;

extern void initArray(fingerprint *f);

int addInFingerprintList(fingerprint *f, int n);

void viewList(fingerprint *f);




