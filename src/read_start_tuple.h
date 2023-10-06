#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct read_start_tuple{

        int read;  //posizione della read all'interno della lista di fing>
        int start; //posizione occorrenza kmer nella 

        //Le tuple sono ordinate per valore crescente del valore read e p>
        //una lista doppiamente concatenata ci velocizza il processo di i>
        struct read_start_tuple* prev;
        struct read_start_tuple* next; 

} rs_tuple;

rs_tuple* create_rs_tuple(int r, int s);


