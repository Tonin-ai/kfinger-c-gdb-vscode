# pattern-matching-2


L’algoritmo Kfinger si pone l’obiettivo del calcolo degli Overlap tra lunghe reads genomiche, compito fondamentale, ad esempio, per costruire l’overlap graph. La tecnica proposta utilizza le fattorizzazioni di Lyndon. E’ ben noto che la fattorizzazionedi Lyndon di una stringa è una sequenza non crescente di fattori, che sono parole di Lyndon. Tale fattorizzazione è unica e può essere calcolata in tempo lineare. Viene utilizzata una rappresentazione delle reads come sequenza di interi, precisamente data dalla lunghezza delle parole di Lyndon che compongono la fattorizzazione della read (Lyndon Fingerprints). E’ stato dimostrato che due stringhe che condividono un overlap comune, condividono anche un insieme di fattori consecutivi nella loro fattorizzazione. Quindi, viene mostrato come individuare regioni comuni tra reads, utilizzando queste k-uple di interi (chiamate k-fingers o k-mers). Qui proponiamo una versione in C più efficiente di quella proposta originariamente in Python.

Bisogna utilizzare il comando "make" per compilare.
Il tool sviluppato consente di essere eseguito in due modalità:
- se si esegue con ./main, sarà un’esecuzione che calcolerà esclusivamente gli
overlap
- se si esegue con ./main -l, viene creato un file di log dei dizionari e delle
fingerprint
