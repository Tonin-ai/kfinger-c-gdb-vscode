/*
in: tmp,j2,k
out: la somma di k interi del vetttore temp partendo dalla posizione j2
*/
int addList(int* tmp, int j2,int k){
	int tot=0;
	for(int i=0;i<k;i++){tot+=tmp[j2+i];}
	return tot;
}
