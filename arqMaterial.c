#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "material.h"

#include "arqMaterial.h"


void iniciaArquivo()
{
  FILE *arq = fopen(arquivoMaterial, "wb+");

  CabMaterial *cabecalho = (CabMaterial *)malloc(sizeof(CabMaterial));

  cabecalho->posLivre = -1;
  cabecalho->posTopo = 0;

  escreveCabMaterial(arq,cabecalho);
  

  fclose(arq);
}



void mostraCabMaterial(CabMaterial *cabecalho){
	printf("\nTopo: %d\nLivre:%d\n", cabecalho->posTopo, cabecalho->posLivre);
}

void escreveMaterialArq(FILE *arq, Material *material, int pos) {
		fseek(arq, 0, SEEK_SET); //posiciona no in ́ıcio do arquivo
    fseek(arq, sizeof(CabMaterial) + pos * sizeof(Material), SEEK_SET);
    fwrite(material, sizeof(Material), 1, arq);
}

Material* leMaterialArq(FILE *arq, int pos){
	Material *x = malloc(sizeof(Material));
	fseek(arq, 0, SEEK_SET);	// posiciona no in ́ıcio do arquivo
	fseek(arq, sizeof(CabMaterial) + pos* sizeof(Material), SEEK_SET);
	fread(x, sizeof(Material), 1, arq);
	return x;
}

CabMaterial* leCabMaterial(FILE *arq){
	CabMaterial *cab = (CabMaterial*) malloc(sizeof(CabMaterial));
	fseek(arq, 0, SEEK_SET);	// posiciona no in ́ıcio do arquivo
	fread(cab, sizeof(CabMaterial), 1, arq);
	return cab;
}

void escreveCabMaterial(FILE *arq, CabMaterial *cabecalho) {
  fseek(arq, 0, SEEK_SET); //posiciona no in ́ıcio do arquivo
  fwrite(cabecalho, sizeof(CabMaterial), 1, arq); 
}