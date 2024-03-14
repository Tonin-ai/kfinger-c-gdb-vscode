#include "hash_functions.h"
#include "list_operations.h"
#include "fingerprint.h"
#include "hash_dict.h"
#include "hash_matches_dict.h"
#include "hash_overlap_dict.h"
#include "parameters.h"
#include <pthread.h>

#define NUM_THREADS 1

pthread_mutex_t *mutex_odict;

typedef struct threadparams
{
    unsigned int start;
    unsigned int end;

} thparams_odict;

int abs(int x);
int min(int x1, int x2);
int max(int x1, int x2);
void *crea_odict_prima_parte(void *arg);

fingerprint *f_list_odict;
hash_mdict *hmdict_odict;
hash_odict *hodict_odict;
pthread_mutex_t *mutex_odict;
parameters *p_odic;

hash_odict *crea_odict(fingerprint *_f_list, hash_mdict *_hmdict, hash_odict *_hodict, pthread_mutex_t *_mutex, parameters *_p)
{
    f_list_odict = _f_list;
    hmdict_odict = _hmdict;
    hodict_odict = _hodict;
    mutex_odict = _mutex;
    p_odic = _p;

    pthread_t threads[NUM_THREADS];

    /*
    for (unsigned int i = 0; i < hdictsize; i++)
    {
        matches_dict *tempdict = hmdict->dicts_list[i]; // salviamo un puntatore temporaneo all'i-esimo diizonario
        if (tempdict)
        { // se è stata allocata memoria
            // printf("%d\n",tempdict->used);
            for (unsigned int j = 0; j < tempdict->used; j++)
            { // per ogni entry del dizionario
                matches_dict_entry *tempentry = tempdict->head[j];
                // if(tempentry->reads[0]==65 && tempentry->reads[1]==376){printf("TROVATO\n");}
                // printf("%d %d\n",tempentry->value[3],tempentry->value[1]);
                if ((min_shared_kmers == 1 || tempentry->count >= min_shared_kmers) && (tempentry->value[3] >= tempentry->value[1]))
                {
                    // printf("%d %d\n",tempentry->value[3],tempentry->value[1]);
                    int start1 = tempentry->value[0], end1 = tempentry->value[2] + k, start2 = tempentry->value[1], end2 = tempentry->value[3] + k;
                    int up1, up2, l1, l2, read1_length, read2_length;
                    int *list0 = (f_list + tempentry->reads[0])->list, *list1 = (f_list + tempentry->reads[1])->list;
                    up1 = addList(list0, 0, start1);
                    up2 = addList(list1, 0, start2);
                    l1 = addList(list0, start1, end1 - start1);
                    l2 = addList(list1, start2, end2 - start2);
                    read1_length = addList(list0, 0, (f_list + tempentry->reads[0])->used);
                    read2_length = addList(list1, 0, (f_list + tempentry->reads[1])->used);
                    int min_cov_number = min_region_kmer_coverage * min(l1, l2) / mintotlen;
                    min_cov_number = min(min_cov_number, 15);
                    // if(abs(l1-l2) <= max_diff_region_percentage * max(l1,l2)){printf("diff 0\n");}
                    // printf("%d %d %d\n",tempmsentry->value >= min_cov_number,abs(l1-l2) <= max_diff_region_percentage * max(l1,l2),max(l1,l2)>= min_region_length);
                    // printf("%d %f %d\n",abs(l1-l2),max_diff_region_percentage,max(l1,l2));
                    if ((tempentry->count >= min_cov_number) && (abs(l1 - l2) <= max_diff_region_percentage * max(l1, l2) && max(l1, l2) >= min_region_length))
                    {
                        // printf("o\n");
                        int min_up = min(up1, up2);
                        int start_ov1 = up1 - min_up;
                        int start_ov2 = up2 - min_up;
                        int min_down = min(read1_length - (up1 + l1), read2_length - (up2 + l2));
                        int end_ov1 = up1 + l1 + min_down;
                        int end_ov2 = up2 + l2 + min_down;
                        int ov_length = min(end_ov1 - start_ov1, end_ov2 - start_ov2);
                        if ((min(l1, l2) >= min_overlap_coverage * ov_length) && ov_length >= min_overlap_length)
                        {
                            // printf("%d %d\n",tempentry->reads[0],tempentry->reads[1]);

                            // printf("%d %d %d %d\n",(f_list+tempentry->reads[0])->id,(f_list+tempentry->reads[1])->id,(f_list+tempentry->reads[0])->isreverse,(f_list+tempentry->reads[1])->isreverse);
                            int *readids = (int *)malloc(2 * sizeof(int));
                            readids[0] = (f_list + tempentry->reads[0])->id;
                            readids[1] = (f_list + tempentry->reads[1])->id;
                            int key = getEntryKey(readids, hdictsize, 2);
                            // printf("a\n");
                            add_in_hash_odict(&hodict->dicts_list[key], readids, (f_list + tempentry->reads[0])->isreverse, (f_list + tempentry->reads[1])->isreverse, read1_length, read2_length, start_ov1, end_ov1, start_ov2, end_ov2, ov_length);
                        }
                    }
                }
            }
        }
    }
    */

    unsigned int num_task_per_thread = (hmdict_odict->size) / NUM_THREADS;

    // printf("Dimensione dizionario: %u\n",(hdict_msdict->size));
    for (unsigned int j = 0; j < NUM_THREADS; j++)
    {
        thparams_odict *x = (thparams_odict *)malloc(sizeof(thparams_odict));
        (*x).start = num_task_per_thread * j;
        (*x).end = num_task_per_thread * (j + 1);
        if ((*x).end > (hmdict_odict->size))
            (*x).end = (hmdict_odict->size);
        // printf("Start: %u | End:%u\n",(*x).start,(*x).end);
        if (pthread_create(threads + j, NULL, &crea_odict_prima_parte, x) != 0)
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

    return hodict_odict;
}

int abs(int x)
{
    if (x >= 0)
        return x;
    return x * -1;
}
int min(int x1, int x2)
{
    if (x1 <= x2)
        return x1;
    return x2;
}
int max(int x1, int x2)
{
    if (x1 >= x2)
        return x1;
    return x2;
}

void *crea_odict_prima_parte(void *arg)
{

    unsigned int start = ((thparams_odict *)arg)->start;
    unsigned int end = ((thparams_odict *)arg)->end;

    for (unsigned int i = start; i < end; i++)
    {
        matches_dict *tempdict = hmdict_odict->dicts_list[i]; // salviamo un puntatore temporaneo all'i-esimo diizonario
        if (tempdict)
        { // se è stata allocata memoria
            // printf("%d\n",tempdict->used);
            for (unsigned int j = 0; j < tempdict->used; j++)
            { // per ogni entry del dizionario
                matches_dict_entry *tempentry = tempdict->head[j];
                // if(tempentry->reads[0]==65 && tempentry->reads[1]==376){printf("TROVATO\n");}
                // printf("%d %d\n",tempentry->value[3],tempentry->value[1]);
                if ((p_odic->min_shared_kmers == 1 || tempentry->count >= p_odic->min_shared_kmers) && (tempentry->value[3] >= tempentry->value[1]))
                {
                    // printf("%d %d\n",tempentry->value[3],tempentry->value[1]);
                    int start1 = tempentry->value[0], end1 = tempentry->value[2] + p_odic->k, start2 = tempentry->value[1], end2 = tempentry->value[3] + p_odic->k;
                    int up1, up2, l1, l2, read1_length, read2_length;
                    //In list0 e list1 ci sono i numeri nelle fingerprint
                    int *list0 = (f_list_odict + tempentry->reads[0])->list, *list1 = (f_list_odict + tempentry->reads[1])->list;
                    up1 = addList(list0, 0, start1);
                    up2 = addList(list1, 0, start2);
                    l1 = addList(list0, start1, end1 - start1);
                    l2 = addList(list1, start2, end2 - start2);
                    read1_length = addList(list0, 0, (f_list_odict + tempentry->reads[0])->used);
                    read2_length = addList(list1, 0, (f_list_odict + tempentry->reads[1])->used);
                    int min_cov_number = p_odic->min_region_kmer_coverage * min(l1, l2) / p_odic->mintotlen;
                    min_cov_number = min(min_cov_number, 15);
                    // if(abs(l1-l2) <= max_diff_region_percentage * max(l1,l2)){printf("diff 0\n");}
                    // printf("%d %d %d\n",tempmsentry->value >= min_cov_number,abs(l1-l2) <= max_diff_region_percentage * max(l1,l2),max(l1,l2)>= min_region_length);
                    // printf("%d %f %d\n",abs(l1-l2),max_diff_region_percentage,max(l1,l2));
                    if ((tempentry->count >= min_cov_number) && (abs(l1 - l2) <= p_odic->max_diff_region_percentage * max(l1, l2) && max(l1, l2) >= p_odic->min_region_length))
                    {
                        // printf("o\n");
                        int min_up = min(up1, up2);
                        int start_ov1 = up1 - min_up;
                        int start_ov2 = up2 - min_up;
                        int min_down = min(read1_length - (up1 + l1), read2_length - (up2 + l2));
                        int end_ov1 = up1 + l1 + min_down;
                        int end_ov2 = up2 + l2 + min_down;
                        int ov_length = min(end_ov1 - start_ov1, end_ov2 - start_ov2);
                        if ((min(l1, l2) >= p_odic->min_overlap_coverage * ov_length) && ov_length >= p_odic->min_overlap_length)
                        {
                            // printf("%d %d\n",tempentry->reads[0],tempentry->reads[1]);

                            // printf("%d %d %d %d\n",(f_list+tempentry->reads[0])->id,(f_list+tempentry->reads[1])->id,(f_list+tempentry->reads[0])->isreverse,(f_list+tempentry->reads[1])->isreverse);
                            int *readids = (int *)malloc(2 * sizeof(int));
                            readids[0] = (f_list_odict + tempentry->reads[0])->id;
                            readids[1] = (f_list_odict + tempentry->reads[1])->id;
                            unsigned int key = getEntryKey(readids, hodict_odict->size, 2);
                            // printf("a\n");
                            pthread_mutex_lock(&mutex_odict[key]);
                            add_in_hash_odict(&hodict_odict->dicts_list[key], readids, (f_list_odict + tempentry->reads[0])->isreverse, (f_list_odict + tempentry->reads[1])->isreverse, read1_length, read2_length, start_ov1, end_ov1, start_ov2, end_ov2, ov_length);
                            pthread_mutex_unlock(&mutex_odict[key]);
                        }
                    }
                }
            }
        }
    }
}