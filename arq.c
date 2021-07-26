#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "arq.h"


FILE * abreArq(){
    FILE *arq = fopen(arquivoArvore, "rb+");

    return arq;
}

void mostraCab(Cab* cabecalho){
    printf("\nRaiz: %d\nTopo: %d\nLivre: %d\n",cabecalho->raiz,cabecalho->topo, cabecalho->livre);
}



Cab* leCab(FILE *arq){
    Cab *cab = (Cab*) malloc(sizeof(Cab));
	fseek(arq, 0, SEEK_SET);	// posiciona no in ́ıcio do arquivo
	fread(cab, sizeof(Cab), 1, arq);
	return cab;
}

void escreveCab(FILE *arq, Cab *cabecalho){
    fseek(arq, 0, SEEK_SET); //posiciona no in ́ıcio do arquivo
    fwrite(cabecalho, sizeof(Cab), 1, arq); 
}


No* leNoArquivo(FILE *arq, int pos){
    No *x = (No*) malloc(sizeof(No));
	fseek(arq, 0, SEEK_SET);	// posiciona no in ́ıcio do arquivo
	fseek(arq, sizeof(Cab) + pos* sizeof(No), SEEK_SET);
	fread(x, sizeof(No), 1, arq);
	return x;
}

void escrevenoArq(FILE *arq, No *no, int pos){
    fseek(arq, 0, SEEK_SET); //posiciona no in ́ıcio do arquivo
    fseek(arq, sizeof(Cab) + pos * sizeof(No), SEEK_SET);
    fwrite(no, sizeof(No), 1, arq);
}

int insereNoArq(FILE *arq, No *no){
    Cab * cab = leCab(arq);
    
    int pos = -1;

    if(cab->livre == -1){

        escrevenoArq(arq,no,cab->topo);
        pos = cab->topo;
        cab->topo = cab->topo +1;

    }else { 
        No *listaVazia = leNoArquivo(arq,cab->livre);

        pos = cab->livre;

        escrevenoArq(arq,no,cab->livre);
        cab->livre = listaVazia->numChaves;   
    }

    escreveCab(arq,cab);

    return pos;
}


void removeNoArq(FILE * arq, No* no, int pos){
    Cab* cab = leCab(arq);


    no->numChaves = cab->livre;
    cab->livre = pos;


    escrevenoArq(arq,no,pos);
    escreveCab(arq,cab);
}
