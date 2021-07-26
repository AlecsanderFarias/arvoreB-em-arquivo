#ifndef ARQUIVO
#define ARQUIVO

#include "arvore.h"


#define arquivoArvore "arvore.bin"

struct Cab {
    int raiz;
    int livre;
    int topo;
} typedef Cab;

FILE * abreArq();


//mostra no terminal o  cabecalho
//cabecalho = cabecalho do arquivo - não pode ser NULL
void mostraCab(Cab* cabecalho);

//le o cabecalho do arquivo
//arq = arquivo para ler
Cab* leCab(FILE *arq);

//escreve o cabecalho no arquivo
//arq = arquivo para escrever
//cabecalho = cabecalho do arquivo para escrever
void escreveCab(FILE *arq, Cab *cabecalho);

//le posicao no no arquivo
//arq = arquivo para ler
//pos = posicao para ler no arquivo
//returna o no e memoria
No* leNoArquivo(FILE *arq, int pos);


//escreve no no arquivo
//arq = arquivo para escrever
//no = No a ser escrito no arquivo - não pode ser NULL
//pos = posicao para escrever no arquivo
void escrevenoArq(FILE *arq, No *no, int pos);

//insere um no no arquivo trantando encademaneto de vazia o topo
//arq = arquivo para escrever
//no = No a ser escrito no arquivo - não pode ser NULL
//retorna a posicao em que foi escrito no arq
int insereNoArq(FILE *arq, No *no);

//remove no no arquivo e cuida do encadeamento vazio
//arq = arquivo para escrever
//no = No a ser removido no arquivo - não pode ser NULL
//pos = pos do no no arquivo
void removeNoArq(FILE * arq, No* no, int pos);

#endif