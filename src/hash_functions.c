/*
funzione hash per la generazione di una chiave intera
*/
int getEntryKey(int* kmer,unsigned int hdictsize,int k){

        unsigned int result = 0x55555555;

        for(int i=0;i<k;i++){
                result ^= kmer[i];
                result = result<<5;
        }
	result%=hdictsize;
        return result;
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
