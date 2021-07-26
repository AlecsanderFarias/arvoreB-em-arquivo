#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "menu.h"
#include "arvore.h"
#include "arqMaterial.h"

//comando para rodar compilar o programa
//gcc index.c arvore.c arvoreArquivo.c material.c materialArquivo.c menu.c


int main() {
  iniciarArvore(); //arvore.bin
  iniciaArquivo(); //material.bin
  
  printf("Bem vindo ao Sitemas de gestão de materiais em C !!\n");

  menuEntrada();

  printf("Obrigado !!\n");

  return 0;
}