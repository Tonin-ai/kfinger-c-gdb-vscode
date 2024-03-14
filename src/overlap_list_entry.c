#include<malloc.h>
typedef struct olistentry{

	int* elements;

}olistentry;

olistentry* createolistoentry(int id1,int flag1,int id2,int flag2,int lenght1,int lenght2,int start1,int end1,int start2,int end2,int strand);

olistentry* createolistoentry(int id1,int flag1,int id2,int flag2,int lenght1,int lenght2,int start1,int end1,int start2,int end2,int strand){
	
	olistentry* x = (olistentry*)malloc(sizeof(olistentry));
	x->elements = (int*)malloc(sizeof(int)*11);

	x->elements[0]=id1;
	x->elements[1]=flag1;
	x->elements[2]=id2;
	x->elements[3]=flag2;
	x->elements[4]=lenght1;
	x->elements[5]=lenght2;
	x->elements[6]=start1;
	x->elements[7]=end1;
	x->elements[8]=start2;
	x->elements[9]=end2;
	x->elements[10]=strand;

	return x;

}
