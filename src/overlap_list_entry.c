#include<malloc.h>
typedef struct olistentry{

	int* elements;

}olistentry;

olistentry* createolistoentry(int x1,int x2,int x3,int x4,int x5,int x6,int x7,int x8,int x9);

olistentry* createolistoentry(int x1,int x2,int x3,int x4,int x5,int x6,int x7,int x8,int x9){
	
	olistentry* x = (olistentry*)malloc(sizeof(olistentry));
	x->elements = (int*)malloc(sizeof(int)*9);

	x->elements[0]=x1;
	x->elements[1]=x2;
	x->elements[2]=x3;
	x->elements[3]=x4;
	x->elements[4]=x5;
	x->elements[5]=x6;
	x->elements[6]=x7;
	x->elements[7]=x8;
	x->elements[8]=x9;

	return x;

}
