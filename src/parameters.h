typedef struct params{
    int min_shared_kmers, min_region_length, min_overlap_length, max_kmer_occurrence, i, k, mintotlen;
	float min_region_kmer_coverage, max_diff_region_percentage, min_overlap_coverage;

}parameters;

parameters* init_parameters();