
#include <limits.h>
#include <pthread.h>
#include "hash_functions.h"
#include "hash_dict.h"
#include "hash_matches_dict.h"

#define NUM_THREADS 1

pthread_mutex_t *mutex_msdict;

typedef struct threadparams
{
    unsigned int start;
    unsigned int end;
} thparams_msdict;

hash_mdict *hmdict_msdict;
hash_dict *hdict_msdict;

void *calcola_msdict(void *i);
void *calcola_msdict_2(void *arg);

hash_mdict *crea_msdict(hash_mdict *_hmdict, hash_dict *_hdict, pthread_mutex_t *_mutex)
{
    mutex_msdict = _mutex;
    hmdict_msdict = _hmdict;
    hdict_msdict = _hdict;

    pthread_t threads[NUM_THREADS];
    /*
    for (unsigned int i = 0; i < hdictsize; i++)
    {                                                // per ogni entry di dict_occ_kmers
        calcola_msdict(i);
    }
    */
    /*
    for (unsigned int i = 0; i < (hdict_msdict->size); i=i+NUM_THREADS)
     {
         printf("%u\n",i);
         int n_threads=NUM_THREADS;
         if((hdict_msdict->size)-i<NUM_THREADS) n_threads=(hdict_msdict->size)-i;
         for(int j=0;j<n_threads;j++){
             unsigned int *x=(unsigned int *)malloc(sizeof(unsigned int));
             *x=i+j;
             if(pthread_create(threads+j,NULL,&calcola_msdict,x)!=0){
                 perror("Failed to create thread.");
                 return NULL;
             }
         }
         for(int j=0;j<n_threads;j++){
             if(pthread_join(threads[j],NULL)!=0){
                 perror("Failed to create thread.");
                 return NULL;
             }
         }
         //printf("============\n");
     }

    */

    unsigned int num_task_per_thread = (hdict_msdict->size) / NUM_THREADS;

    // printf("Dimensione dizionario: %u\n",(hdict_msdict->size));
    for (unsigned int j = 0; j < NUM_THREADS; j++)
    {
        thparams_msdict *x = (thparams_msdict *)malloc(sizeof(thparams_msdict));
        (*x).start = num_task_per_thread * j;
        (*x).end = num_task_per_thread * (j + 1);
        if ((*x).end > (hdict_msdict->size))
            (*x).end = (hdict_msdict->size);
        // printf("Start: %u | End:%u\n",(*x).start,(*x).end);
        if (pthread_create(threads + j, NULL, &calcola_msdict_2, x) != 0)
        {
            perror("Failed to create thread.");
            return NULL;
        }
    }
    for (unsigned int j = 0; j < NUM_THREADS; j++)
    {
        if (pthread_join(threads[j], NULL) != 0)
        {
            perror("Failed to create thread.");
            return NULL;
        }
    }

    return hmdict_msdict;
}

void *calcola_msdict(void *arg)
{

    unsigned int i = *(unsigned int *)arg;

    // printf("%u\n",i);

    dict_kmers *tempdict = hdict_msdict->dicts_list[i]; // salviamo un puntatore temporaneo all'i-esimo diizonario
    if (tempdict)
    { // se è stata allocata memoria
        for (unsigned int j = 0; j < tempdict->used; j++)
        { // per ogni entry del dizionario
            int read1, read2;
            int start1, start2;
            dict_entry_kmers *tempentry = tempdict->head[j]; // viene salvato un puntatore alla j-esima entry del dizionario
            for (int z1 = 0; z1 < tempentry->used; z1++)
            { // per  ogni coppia (READ,START) all'interno della entry
                read1 = tempentry->head[z1]->read;
                start1 = tempentry->head[z1]->start;
                for (int z2 = z1 + 1; z2 < tempentry->used; z2++)
                { // per ogni coppia (READ,START) partendo dalla z1+1-esima posizione all'interno della entry
                    read2 = tempentry->head[z2]->read;
                    start2 = tempentry->head[z2]->start;
                    int *reads = (int *)malloc(2 * sizeof(int));
                    reads[0] = read1;
                    reads[1] = read2;
                    unsigned int key = getEntryKey(reads, (hdict_msdict->size), 2); // viene generata la chiave dei dizionari

                    pthread_mutex_lock(&mutex_msdict[key]);
                    add_in_hash_mdict(&hmdict_msdict->dicts_list[key], reads, start1, start2); // viene aggiornata la entry che ha come chiave reads in min_saring_dict
                    pthread_mutex_unlock(&mutex_msdict[key]);
                }
            }
        }
    }

    free(arg);
}

void *calcola_msdict_2(void *arg)
{

    unsigned int start = ((thparams_msdict *)arg)->start;
    unsigned int end = ((thparams_msdict *)arg)->end;

    for (unsigned int i = start; i < end; i++)
    {
        dict_kmers *tempdict = hdict_msdict->dicts_list[i]; // salviamo un puntatore temporaneo all'i-esimo diizonario
        if (tempdict)
        { // se è stata allocata memoria
            for (unsigned int j = 0; j < tempdict->used; j++)
            { // per ogni entry del dizionario
                int read1, read2;
                int start1, start2;
                dict_entry_kmers *tempentry = tempdict->head[j]; // viene salvato un puntatore alla j-esima entry del dizionario
                for (unsigned int z1 = 0; z1 < tempentry->used; z1++)
                { // per  ogni coppia (READ,START) all'interno della entry
                    read1 = tempentry->head[z1]->read;
                    start1 = tempentry->head[z1]->start;
                    for (unsigned int z2 = z1 + 1; z2 < tempentry->used; z2++)
                    { // per ogni coppia (READ,START) partendo dalla z1+1-esima posizione all'interno della entry
                        read2 = tempentry->head[z2]->read;
                        start2 = tempentry->head[z2]->start;
                        int *reads = (int *)malloc(2 * sizeof(int));
                        reads[0] = read1;
                        reads[1] = read2;
                        unsigned int key = getEntryKey(reads, (hdict_msdict->size), 2); // viene generata la chiave dei dizionari

                        pthread_mutex_lock(&mutex_msdict[key]);
                        add_in_hash_mdict(&hmdict_msdict->dicts_list[key], reads, start1, start2); // viene aggiornata la entry che ha come chiave reads in min_saring_dict
                        pthread_mutex_unlock(&mutex_msdict[key]);
                    }
                }
            }
        }
    }
    free(arg);
}