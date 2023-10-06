#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>

typedef struct fingerprint{
	int id; //id della fingerprint
	int isreverse; //bool per vedere se la read è Reverse_and_Complement
	int* list; //lista di interi della fingerprint
	int size; //numero di entry stimate
	int used; //numero di entry effettivamente utilizzate

} fingerprint;

/*
in: f
out: void
prende in input una fingerprint e imposta numero di entry stimate
e alloca memoria per conservare gli interi
*/

void initArray(fingerprint *f) {
  	f->list = (int*)malloc(sizeof(int));
  	f->used = 0;
 	f->size = 1;
}

/*
in: f, n
out: 1 se l'elemto n viene inserito come ultimo elemto della lista
*/

int addInFingerprintList(fingerprint *f, int n){
  	// a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  	// Therefore a->used can go up to a->size 
  	if (f->used == f->size) {
    		f->size *= 2;
		//f->size+=1;
    		f->list = realloc(f->list, f->size * sizeof(int));
  	}
  	f->list[f->used++] = n;

}
/*
in: f
out: void
viene visualizzata la lista di interi memorizzati nella lista della fingerprint f
*/
void viewList(fingerprint *f){
	printf("%d_%d ",f->id,f->isreverse);
	for (int i = 0; i < f->used; i++){
		printf("%d ",f->list[i]);
	}
	printf("\n");
}
