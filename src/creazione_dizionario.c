
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>
#include <pthread.h>
#include "menu.h"
#include "fingerprint.h"
#include "hash_dict.h"
#include "hash_functions.h"
#include "list_operations.h"
#include "parameters.h"

#define NUM_THREADS 1

pthread_mutex_t *mutex;

typedef struct threadparams
{
    unsigned int start;
    unsigned int end;
} thparams;

void *crea_dizionario_prima_parte(void *arg);
void *crea_dizionario_prima_parte_2(void *arg);
void *crea_dizionario_seconda_parte_2(void *arg);
int *kmer, *tmp; // array di appoggio

fingerprint *f_list;
unsigned int f_list_size;
hash_dict *hdict;
hash_dict *hdicttemp;
parameters* p_dict;

hash_dict *crea_dizionario(fingerprint *_f_list, unsigned int _f_list_size, hash_dict *_hdict, hash_dict *_hdicttemp, pthread_mutex_t *_mutex,parameters* _p)
{
    f_list = _f_list;
    f_list_size = _f_list_size;
    hdict = _hdict;
    hdicttemp = _hdicttemp;
    mutex = _mutex;
    p_dict=_p;

    pthread_t threads[NUM_THREADS];

    /*
    for (int j1 = 0; j1 < f_list_size + 1; j1 = j1 + NUM_THREADS)
    { // per goni read
        // fingerprint* f_list_temp = f_list=f_list+j1;
        int n_threads = NUM_THREADS;
        if (f_list_size - j1 < NUM_THREADS)
            n_threads = f_list_size - j1;
        for (int j = 0; j < n_threads; j++)
        {
            //
            thparams *x=(thparams *)malloc(sizeof(thparams));
            (*x).j1=j1+j;
            (*x).f_list=f_list;
            (*x).f_list_size=f_list_size;
            (*x).hdict=hdict;
            (*x).hdicttemp=hdicttemp;
            //

            int *x = (int *)malloc(sizeof(int));
            *x = j1 + j;
            if (pthread_create(threads + j, NULL, &crea_dizionario_prima_parte, x) != 0)
            {
                perror("Failed to create thread.");
            }
        }
        for (int j = 0; j < n_threads; j++)
        {
            if (pthread_join(threads[j], NULL) != 0)
            {
                perror("Failed to create thread.");
            }
        }
    }
    */
    f_list_size++;

    unsigned int num_task_per_thread = (f_list_size) / NUM_THREADS;

    //printf("Dimensione dizionario: %u\n",f_list_size);
    for (unsigned int j = 0; j < NUM_THREADS; j++)
    {
        thparams *x = (thparams *)malloc(sizeof(thparams));
        (*x).start = num_task_per_thread * j;
        (*x).end = num_task_per_thread * (j + 1);
        if ((*x).end > (f_list_size))
            (*x).end = (f_list_size);
        //printf("Start: %u | End:%u\n",(*x).start,(*x).end);
        if (pthread_create(threads + j, NULL, &crea_dizionario_prima_parte_2, x) != 0)
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

    /*
    for (unsigned int i = 0; i < (hdict->size); i++)
    {                                                    // per ogni entry di dict_occ_kmers
        dict_kmers *tempdict = hdicttemp->dicts_list[i]; // salviamo un puntatore temporaneo all'i-esimo diizonario
        if (tempdict)
        { // se è stata allocata memoria
            for (unsigned int j = 0; j < tempdict->used; j++)
            {                                                    // per ogni entry del dizionario
                dict_entry_kmers *tempentry = tempdict->head[j]; // viene salvato un puntatore alla j-esima entry del dizionario
                if (tempentry->used > 0 && (max_kmer_occurrence == -1 || tempentry->used <= max_kmer_occurrence))
                {
                    for (unsigned int z1 = 0; z1 < tempentry->used; z1++)
                    { // per  ogni coppia (READ,STAR)
                        int read = tempentry->head[z1]->read;
                        int start = tempentry->head[z1]->start;
                        add_in_hash_dict(&hdict->dicts_list[i], tempentry->kmer, read, start, k);
                    }
                }
            }
        }
    }
    */

    num_task_per_thread = (hdict->size) / NUM_THREADS;

    for (unsigned int j = 0; j < NUM_THREADS; j++)
    {
        thparams *x = (thparams *)malloc(sizeof(thparams));
        (*x).start = num_task_per_thread * j;
        (*x).end = num_task_per_thread * (j + 1);
        if ((*x).end > (hdict->size))
            (*x).end = (hdict->size);
        // printf("Start: %u | End:%u\n",(*x).start,(*x).end);
        if (pthread_create(threads + j, NULL, &crea_dizionario_seconda_parte_2, x) != 0)
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

    free(hdicttemp);
    return hdict;
}

void *crea_dizionario_prima_parte(void *arg)
{
    /*
    hash_dict *hdict=((thparams *)arg)->hdict;
    hash_dict *hdicttemp=((thparams *)arg)->hdicttemp;
    fingerprint *f_list=((thparams *)arg)->f_list;
    */

    int j1 = *(int *)arg;
    tmp = (f_list + j1)->list;
    for (int j2 = 0; j2 <= (f_list + j1)->used - p_dict->k; j2++)
    {                                               // finché posso prendere almeno k elemti
        int seed = addList(tmp, j2, p_dict->k) - p_dict->mintotlen; // viene verificata che la somma degli interi presenti all'iterno del kmer fa almeo mintotlen
        if (seed >= 0)
        {
            kmer = (int *)malloc(p_dict->k * sizeof(int));
            memcpy(kmer, tmp + j2, p_dict->k * sizeof(int));
            unsigned int key = getEntryKey(kmer, (hdicttemp->size), p_dict->k); // viene computata la chiave per hash dict

            pthread_mutex_lock(&mutex[key]);
            int esito = add_in_hash_dict(&hdicttemp->dicts_list[key], kmer, j1, j2, p_dict->k); // viene salvata all'inetro del dizionario che ha collizioni con la chiave l'entry che ha
                                                                                        // per chiave il kmer e valore la coppia (READ,START)
            pthread_mutex_unlock(&mutex[key]);
        }
    }
    free(arg);
}

void *crea_dizionario_prima_parte_2(void *arg)
{
    /*
    hash_dict *hdict=((thparams *)arg)->hdict;
    hash_dict *hdicttemp=((thparams *)arg)->hdicttemp;
    fingerprint *f_list=((thparams *)arg)->f_list;
    */

    unsigned int start = ((thparams *)arg)->start;
    unsigned int end = ((thparams *)arg)->end;

    for (unsigned int j1 = start; j1 < end; j1++)
    {
        tmp = (f_list + j1)->list;
        for (int j2 = 0; j2 <= (f_list + j1)->used - p_dict->k; j2++)
        {                                               // finché posso prendere almeno k elemti
            int seed = addList(tmp, j2, p_dict->k) - p_dict->mintotlen; // viene verificata che la somma degli interi presenti all'iterno del kmer fa almeo mintotlen
            if (seed >= 0)
            {
                kmer = (int *)malloc(p_dict->k * sizeof(int));
                memcpy(kmer, tmp + j2, p_dict->k * sizeof(int));
                unsigned int key = getEntryKey(kmer, (hdicttemp->size), p_dict->k); // viene computata la chiave per hash dict

                pthread_mutex_lock(&mutex[key]);
                int esito = add_in_hash_dict(&hdicttemp->dicts_list[key], kmer, j1, j2, p_dict->k); // viene salvata all'inetro del dizionario che ha collizioni con la chiave l'entry che ha
                                                                                            // per chiave il kmer e valore la coppia (READ,START)
                pthread_mutex_unlock(&mutex[key]);
            }
        }
    }
    free(arg);
}

void *crea_dizionario_seconda_parte_2(void *arg)
{

    unsigned int start = ((thparams *)arg)->start;
    unsigned int end = ((thparams *)arg)->end;

    for (unsigned int i = start; i < end; i++)
    {                                                    // per ogni entry di dict_occ_kmers
        dict_kmers *tempdict = hdicttemp->dicts_list[i]; // salviamo un puntatore temporaneo all'i-esimo diizonario
        if (tempdict)
        { // se è stata allocata memoria
            for (unsigned int j = 0; j < tempdict->used; j++)
            {                                                    // per ogni entry del dizionario
                dict_entry_kmers *tempentry = tempdict->head[j]; // viene salvato un puntatore alla j-esima entry del dizionario
                if (tempentry->used > 0 && (p_dict->max_kmer_occurrence == -1 || tempentry->used <= p_dict->max_kmer_occurrence))
                {
                    for (unsigned int z1 = 0; z1 < tempentry->used; z1++)
                    { // per  ogni coppia (READ,STAR)
                        int read = tempentry->head[z1]->read;
                        int start = tempentry->head[z1]->start;
                        
                        pthread_mutex_lock(&mutex[i]);
                        add_in_hash_dict(&hdict->dicts_list[i], tempentry->kmer, read, start, p_dict->k);
                        pthread_mutex_unlock(&mutex[i]);
                    }
                }
            }
        }
    }
}