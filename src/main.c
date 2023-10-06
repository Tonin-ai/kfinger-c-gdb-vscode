#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>
#include "menu.h"
#include "fingerprint.h"
#include "hash_dict.h"
#include "hash_matches_dict.h"
#include "hash_min_sharing_dict.h"
#include "hash_overlap_dict.h"
#include "overlap_list.h"
#define MAX_LINE_LENGTH 10


int abs(int x);
int min(int x1,int x2);
int max(int x1,int x2);
int addList(int* tmp, int j2,int k);
//int getEntryKey(int* kmer,int seed,int k);
//unsigned short int getEntryKey(int* kmer,int seed,int k);
int getEntryKey(int* kmer,int hdictsize,int k);

int main(int argc, char **argv){
  	fingerprint* f_list,*f_temp; //lista di puntatori a fingerprint
  	char line[MAX_LINE_LENGTH], temp[10];//stringhe di appoggio
  	FILE* fp = fopen("./inputtest.txt", "r"); //apertura file input
	hash_dict* hdict=(hash_dict*)malloc(sizeof(hash_dict));//creazion hash_dict
	hash_dict* hdicttemp=(hash_dict*)malloc(sizeof(hash_dict));//creazion hash_dict
	int hdictsize=100000000; //parametro size per tutti gli hash dict
	int min_shared_kmers = 4,min_region_length = 100,min_overlap_length = 600,max_kmer_occurrence = -1;
	float min_region_kmer_coverage = 0.27,max_diff_region_percentage = 0.0,min_overlap_coverage = 0.70;
	initHashDict(hdict,hdictsize); //inizializzazione di hdict
	initHashDict(hdicttemp,hdictsize); //inizializzazione di hdicttemp

  	if (fp == NULL) { //controllo se è presente il file input
     		printf("no such file.");
     		return 0;
  	}
  	f_list = (fingerprint*)malloc(sizeof(fingerprint) * 21000);//inizializzazione della lista di read con quante read ci sono all'interno del file
	init_menu("./intro.txt"); //visualizzazione intto

 	 //creariamo le fingerprint con i relativi id e il parametro reverse and complement
  	int i=-1,k=7,mintotlen = 40; //inizialiaziamo i parametri k (fa riferimenti ai k mer) e mintotlen(valore minimo che deve assumere la somma dei valori presenti nel kmer)
	long int rscount=0,rscount2=0; //vairabili per la visualizzazione di parametri

	time_t seconds=time(NULL); //comincio a prendere il tempo
  	while(fscanf(fp,"%s", line)>0) { //finchè c'è qualcosa da leggere ne file
        	if(strcmp(line, "|")){ //ignoriamo i |
	   		int linetemp = strlen(line);
	   		if(linetemp>=3 && line[linetemp-2] == '_'){ //verifico se è una stringa che come penultimo carattere ha _
				//printf("%d\n",(f_list+i)->size);
				//if(!atoi(line)){
	     			//if(i>=0) viewList(f_list+i); //visualizzo l'ultimo fingerprint
	     			i++;
             			sscanf(line,"%[^_]",temp);
	     			(f_list+i)->id = atoi(temp);
             			sscanf(line,"%*[^_]%*c%s",temp);
	     			(f_list+i)->isreverse = atoi(temp);
				initArray(f_list+i);//viene inizializzata la fingerprint che avrà l'id e isreverse letti
	     			//printf("[Id : %d ,Reverse: %d]\n",(f_list+i)->id,(f_list+i)->isreverse);
	   		}

 	   		else{addInFingerprintList(f_list+i, atoi(line));rscount++;} //viene aggiunto l'intero alla fingerprint
		}
  	}
	printf("Secondi lettura linee: %ld\n",time(NULL)-seconds); //display tempo richiesto

	if(i==-1){printf("Non sono state lette righe.\n"); return 0;} 

	//for(int j1=0;j1<=i;j1++){printf("\n");viewList(f_list+j1);}

	int *kmer,*tmp;//array di appoggio

	seconds=time(NULL);//viene resettato il tempo
	for(int j1=0;j1<=i;j1++){//per goni read
		//fingerprint* f_list_temp = f_list=f_list+j1;
		tmp=(f_list+j1)->list;
		for(int j2=0;j2<=(f_list+j1)->used - k;j2++){//finché posso prendere almeno k elemti
			int seed=addList(tmp,j2,k) - mintotlen; //viene verificata che la somma degli interi presenti all'iterno del kmer fa almeo mintotlen
			//printf("[");for(int z=0;z<k;z++){printf("%d ",tmp[j2+z]);}printf("] %d\n",seed);
			if(seed >= 0){
				kmer=(int*)malloc(k*sizeof(int));
				memcpy(kmer, tmp+j2, k*sizeof(int));
				//printf("[");for(int z=0;z<k;z++){printf("%d ",kmer[z]);}printf("] %d\n",seed);
				//for(int t=0;t<k;t++){printf("%d ",kmer[t]);}printf("\n");
				//printf("a%d - %d\n",j1,j2);
				//printf("%d\n",key);
				int key = getEntryKey(kmer,hdictsize,k);//viene computata la chiave per hash dict
				//printf("[");for(int z=0;z<k;z++){printf("%d ",kmer[z]);}printf("] %d\n",key);
				int esito = add_in_hash_dict(&hdicttemp->dicts_list[key],kmer,j1,j2,k); //viene salvata all'inetro del dizionario che ha collizioni con la chiave l'entry che ha 
														        //per chiave il kmer e valore la coppia (READ,START)
				//printf("[");for(int z=0;z<k;z++){printf("%d ",kmer[z]);}printf("] %d %d\n",key,esito);
				//viewDict(hdicttemp->dicts_list[key],k);
				//printf("aa\n");
				rscount2++;
			}
		}
		//printf("%d|%d - %d\n",(f_list)->id,(f_list)->isreverse,(f_list)->used);
		//printf("%ld rimanenti.\n",rscount-rscount2);
		//f_temp=f_list;
		//f_list+=1;
		//free(f_temp);
	}
	//printf("%d\n",dict->used);
	//viewHashDict(hdict,k);
	//printf("\n");
	//inizializzazione min_share_dict e matches_dict



	for(int i=0;i<hdictsize;i++){//per ogni entry di dict_occ_kmers
                dict_kmers *tempdict=hdicttemp->dicts_list[i];//salviamo un puntatore temporaneo all'i-esimo diizonario
                if(tempdict){//se è stata allocata memoria
                        for(int j=0;j<tempdict->used;j++){//per ogni entry del dizionario
                                dict_entry_kmers *tempentry = tempdict->head[j];//viene salvato un puntatore alla j-esima entry del dizionario
				if(tempentry->used > 0 && (max_kmer_occurrence == -1 ||  tempentry->used <= max_kmer_occurrence)){
					for(int z1=0;z1<tempentry->used;z1++){ //per  ogni coppia (READ,STAR>
						int read = tempentry->head[z1]->read;
                               	         	int start = tempentry->head[z1]->start;
						add_in_hash_dict(&hdict->dicts_list[i],tempentry->kmer,read,start,k);
                                	}
					//printf("[");for(int z=0;z<k;z++){printf("%d ",tempentry->kmer[z]);}printf("] %d\n",i);
				}
                        }
                }
        }
	free(hdicttemp);
        printf("Secondi creazione dizionario: %ld\n",time(NULL)-seconds);//diplsy tempo creazione di>



	hash_mdict* hmdict=(hash_mdict*)malloc(sizeof(hash_mdict));
        initHashMDict(hmdict,hdictsize);
	seconds=time(NULL);
	for(int i=0;i<hdictsize;i++){//per ogni entry di dict_occ_kmers
		dict_kmers *tempdict=hdict->dicts_list[i];//salviamo un puntatore temporaneo all'i-esimo diizonario
		if(tempdict){//se è stata allocata memoria
			for(int j=0;j<tempdict->used;j++){//per ogni entry del dizionario
				int read1,read2;
				int start1,start2;
				dict_entry_kmers *tempentry = tempdict->head[j];//viene salvato un puntatore alla j-esima entry del dizionario
				for(int z1=0;z1<tempentry->used;z1++){ //per  ogni coppia (READ,START) all'interno della entry
					read1 = tempentry->head[z1]->read;
					start1 = tempentry->head[z1]->start;
					for(int z2=z1+1;z2<tempentry->used;z2++){//per ogni coppia (READ,START) partendo dalla z1+1-esima posizione all'interno della entry
						//printf("a");
						read2 = tempentry->head[z2]->read;
						start2 = tempentry->head[z2]->start;
						int *reads=(int*)malloc(2*sizeof(int));
						reads[0]=read1;
						reads[1]=read2;
						if(reads[0]==65 && reads[1]==376){printf("TROVATO\n");}
						int key = getEntryKey(reads,hdictsize,2); //viene generata la chiave dei dizionari
						add_in_hash_mdict(&hmdict->dicts_list[key],reads,start1,start2); //viene aggiornata la entry che ha come chiave reads in min_saring_dict
					}
				}
			}
		}
	}
	printf("Secondi creazione msdict e mdict: %ld\n",time(NULL)-seconds);//viene mostrato quanto tempo ci è voluto a create matches_dict e min_sharing_dict
	//viewMSDict(msdict);
	//viewHashMSDict(hmsdict);
	//printf("\n");
	//viewHashMDict(hmdict);
	//printf("\n");

	hash_odict* hodict=(hash_odict*)malloc(sizeof(hash_odict));
        initHashODict(hodict,hdictsize);
	seconds=time(NULL);
	int cont=0;
	for(int i=0;i<hdictsize;i++){
		matches_dict *tempdict=hmdict->dicts_list[i];//salviamo un puntatore temporaneo all'i-esimo diizonario
                if(tempdict){//se è stata allocata memoria
			//printf("%d\n",tempdict->used);
                        for(int j=0;j<tempdict->used;j++){//per ogni entry del dizionario
				cont++;
				matches_dict_entry *tempentry = tempdict->head[j];
				//if(tempentry->reads[0]==65 && tempentry->reads[1]==376){printf("TROVATO\n");}
				//printf("%d %d\n",tempentry->value[3],tempentry->value[1]);
				if((min_shared_kmers==1 || tempentry->count >= min_shared_kmers) && (tempentry->value[3] >= tempentry->value[1])){
					//printf("%d %d\n",tempentry->value[3],tempentry->value[1]);
					int start1=tempentry->value[0], end1=tempentry->value[2]+k, start2=tempentry->value[1], end2=tempentry->value[3]+k;
					int up1,up2,l1,l2,read1_length,read2_length;
					int *list0=(f_list+tempentry->reads[0])->list,*list1=(f_list+tempentry->reads[1])->list;
					up1 = addList(list0,0,start1);
					up2 = addList(list1,0,start2);
					l1 = addList(list0,start1,end1-start1);
					l2 = addList(list1,start2,end2-start2);
					read1_length = addList(list0,0,(f_list+tempentry->reads[0])->used);
					read2_length = addList(list1,0,(f_list+tempentry->reads[1])->used);
					int min_cov_number = min_region_kmer_coverage * min(l1,l2)/mintotlen;
					min_cov_number = min(min_cov_number,15);
					//if(abs(l1-l2) <= max_diff_region_percentage * max(l1,l2)){printf("diff 0\n");}
					//printf("%d %d %d\n",tempmsentry->value >= min_cov_number,abs(l1-l2) <= max_diff_region_percentage * max(l1,l2),max(l1,l2)>= min_region_length);
					//printf("%d %f %d\n",abs(l1-l2),max_diff_region_percentage,max(l1,l2));
					if((tempentry->count >= min_cov_number) && (abs(l1-l2) <= max_diff_region_percentage * max(l1,l2) && max(l1,l2)>= min_region_length)){
						//printf("o\n");
						int min_up = min(up1,up2);
						int start_ov1 = up1 - min_up;
						int start_ov2 = up2 - min_up;
						int min_down = min(read1_length-(up1+l1), read2_length-(up2+l2));
						int end_ov1 = up1 + l1 + min_down;
						int end_ov2 = up2 + l2 + min_down;
						int ov_length = min(end_ov1-start_ov1, end_ov2-start_ov2);
						if ((min(l1,l2) >= min_overlap_coverage * ov_length) && ov_length >= min_overlap_length){
							//printf("%d %d\n",tempentry->reads[0],tempentry->reads[1]);

							//printf("%d %d %d %d\n",(f_list+tempentry->reads[0])->id,(f_list+tempentry->reads[1])->id,(f_list+tempentry->reads[0])->isreverse,(f_list+tempentry->reads[1])->isreverse);
							int *readids=(int*)malloc(2*sizeof(int));
                                                	readids[0]=(f_list+tempentry->reads[0])->id;
                                                	readids[1]=(f_list+tempentry->reads[1])->id;
                                                	int key = getEntryKey(readids,hdictsize,2);
							//printf("a\n");
							add_in_hash_odict(&hodict->dicts_list[key],readids,(f_list+tempentry->reads[0])->isreverse,(f_list+tempentry->reads[1])->isreverse,read1_length, read2_length, start_ov1, end_ov1, start_ov2, end_ov2, ov_length);
						}
					}
				}
			}
		}
	}
	//printf("%d\n",cont);
        printf("Secondi calcolo overlaps: %ld\n",time(NULL)-seconds);//viene mostrato quanto tempo ci è voluto a create matches_dict e min_sharing_dict
	

	olist* overlap_list=(olist*)malloc(sizeof(olist));
	initolist(overlap_list);

	for(int i=0;i<hdictsize;i++){
	
		overlap_dict* tempdict=hodict->dicts_list[i];
		if(tempdict){
			for(int j=0;j<tempdict->used;j++){

				overlap_dict_entry* tempentry=tempdict->head[j];
				int* tempvalues=tempentry->value;
				//memcpy(tempvalues,tempentry->value,sizeof(int)*9);
	
				int strand = 0;
				
				int flag1=tempvalues[0];
				int flag2=tempvalues[1];
				int lenght1=tempvalues[2];
				int lenght2=tempvalues[3];
				int start1=tempvalues[4];
				int end1=tempvalues[5];
				int start2=tempvalues[6];
				int end2=tempvalues[7];


				if(flag1==1 && flag2==0){
				
					start2=tempvalues[3]-tempvalues[7];
					end2=tempvalues[3]-tempvalues[6];
					strand=1;
				}
				else{
				
					start1=tempvalues[2]-tempvalues[5];
					end1=tempvalues[2]-tempvalues[4];
					if(flag2==0){
						start2=tempvalues[3]-tempvalues[7];
						end2=tempvalues[3]-tempvalues[6];
					}
					else{
					
						strand=1;
					
					}
				}
	
	
				//add_olist_entry(overlap_list,tempentry->reads[0],tempentry->reads[1],tempvalues[2],tempvalues[3],tempvalues[4],tempvalues[5],tempvalues[6],tempvalues[7],strand);
				add_olist_entry(overlap_list,flag1,flag2,lenght1,lenght2,start1,end1,start2,end2,strand);
	
			}
		}
	
	}

	if(argc == 2){
		int out = open("dict_occorrenze.log", O_RDWR|O_CREAT|O_APPEND, 0600);
		if (-1 == out) { perror("opening cout.log"); return 255; }

    		int save_out = dup(fileno(stdout));
    		if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }

		//printf("\nDIZIONARIO OCCORRENZE\n");
                viewHashDict(hdict,k);
                printf("\n");

		out = open("dict_match.log", O_RDWR|O_CREAT|O_APPEND, 0600);
                if (-1 == out) { perror("opening cout.log"); return 255; }
  
                save_out = dup(fileno(stdout));
                if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
        	//printf("\nDIZIONARIO MATCHES\n");
        	viewHashMDict(hmdict);
        	printf("\n");

		out = open("dict_overlap.log", O_RDWR|O_CREAT|O_APPEND, 0600);
                if (-1 == out) { perror("opening cout.log"); return 255; }
  
                save_out = dup(fileno(stdout));
                if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
        	//printf("\nDIZIONARIO OVERLAP\n");
        	viewHashODict(hodict);
        	printf("\n");

		out = open("list_overlap.log", O_RDWR|O_CREAT|O_APPEND, 0600);
                if (-1 == out) { perror("opening cout.log"); return 255; }
  
                save_out = dup(fileno(stdout));
                if (-1 == dup2(out, fileno(stdout))) { perror("cannot redirect stdout"); return 255; }
		//printf("\nLISTA OVERLAP\n");
		stampolist(overlap_list);
		printf("\n");


		if (!strcmp("-overlap_dict",argv[1])){
			 viewHashODict(hodict);
                         printf("\n");
                }

		if (!strcmp("-overlap_list",argv[1])){
                        stampolist(overlap_list);
                        printf("\n");
                }

		if (!strcmp("-matches_dict",argv[1])){
			viewHashMDict(hmdict);
			printf("\n");
                 }


	}
	
	free(hodict);
	free(hmdict);
	free(hdict);
	return 0;
}

int abs(int x){if(x>=0)return x;return x*-1;}
int min(int x1,int x2){if(x1<=x2)return x1;return x2;}
int max(int x1,int x2){if(x1>=x2)return x1;return x2;}

/*
in: tmp,j2,k
out: la somma di k interi del vetttore temp partendo dalla posizione j2
*/
int addList(int* tmp, int j2,int k){
	int tot=0;
	for(int i=0;i<k;i++){tot+=tmp[j2+i];}
	return tot;
}

/*
int getEntryKey(int* kmer,int seed,int k){
	int tot=seed;
	for(int i=0;i<k;i++){tot+=kmer[i]*(i+1);}
	return tot%1000;
}
*/
/*
unsigned short int getEntryKey(int* kmer,int seed,int k){
	char str[128];
	int index = 0;
	for (int i=0; i<k; i++)
	   index += snprintf(&str[index], 128-index, "%d", kmer[i]);

	unsigned short int result = 0x5555;

	for(int i=0;i<strlen(str);i++){
       		result ^= (unsigned short int)str[i];
        	result = result<<3;
    	}
	return result;
}
*/

/*
funzione hash per la generazione di una chiave intera
*/
int getEntryKey(int* kmer,int hdictsize,int k){

        unsigned int result = 0x55555555;

        for(int i=0;i<k;i++){
                result ^= kmer[i];
                result = result<<5;
        }
	result%=hdictsize;
        return result;
}
