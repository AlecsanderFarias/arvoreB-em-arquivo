#ifndef ARQUIVOMATERIAL
#define ARQUIVOMATERIAL

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "material.h"

#define arquivoMaterial "material.bin"

typedef struct CabecalhoMaterial
{
    int posTopo;
    int posLivre;
} CabMaterial;

//inicia o arquivo de forma correta com cabecalho
void iniciaArquivo();

//mostra no terminal o  cabecalho
//cabecalho = cabecalho do arquivo - não pode ser NULL
void mostraCabMaterial(CabMaterial* cabecalho);

//escreve no no arquivo
//arq = arquivo para escrever
//no = No a ser escrito no arquivo - não pode ser NULL
//pos = posicao para escrever no arquivo
void escreveMaterialArq(FILE *arq, Material *material, int pos);

//le posicao no no arquivo
//arq = arquivo para ler
//pos = posicao para ler no arquivo
//return a MaterialNode in memnory
Material* leMaterialArq(FILE *arq, int pos);

//le o cabecalho do arquivo
//arq = arquivo para ler
CabMaterial* leCabMaterial(FILE *arq);

//escreve o cabecalho no arquivo
//arq = arquivo para escrever
//cabecalho = cabecalho do arquivo para escrever
void escreveCabMaterial(FILE *arq, CabMaterial *cabecalho);


#endif