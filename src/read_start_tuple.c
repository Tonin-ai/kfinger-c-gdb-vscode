#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct read_start_tuple{
	
	int read;  //posizione della read all'interno della lista di fingerprint
	int start; //posizione occorrenza kmer nella fingerprint
	
	
} rs_tuple;

rs_tuple* create_rs_tuple(int r, int s);

/*
in: r,s
out: rs_tuple
restituisce un puntatore a una coppia (READ,START)
*/
rs_tuple* create_rs_tuple(int r, int s){
	rs_tuple* p1 = (rs_tuple*)malloc(sizeof(rs_tuple));
	
	p1->read  = r;
	p1->start = s;
	
	
	return p1;
}
