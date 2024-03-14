#include <malloc.h>
#include "parameters.h"

parameters* init_parameters(){
    parameters* x = (parameters*)malloc(sizeof(parameters));

    x->min_shared_kmers=4;//4
    x->min_region_length=0; //100
    x->min_overlap_length=600; //600
    x->max_kmer_occurrence=-1; //-1
    x->i=-1; //-1
    x->k=7; //7
    x->mintotlen=40; //40

    x->min_region_kmer_coverage=0.27;
    x->max_diff_region_percentage=0.0;
    x->min_overlap_coverage=0.70; //0.70;

    return x;
}