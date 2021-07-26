#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "material.h"
#include "arqMaterial.h"

Material* criaMaterial(int codigo, char nome[],int qtd,float preco,char localizacao[]){
  Material* novoMaterial = (Material *)malloc(sizeof(Material));

  novoMaterial->codigo = codigo;
  novoMaterial->qtd = qtd;
  novoMaterial->preco = preco; 


  //copy strings
  strcpy(novoMaterial->nome,nome); 
  strcpy(novoMaterial->localizacao,localizacao);

  return novoMaterial;
}

Material*  editaMaterial(Material* material,int campo, char valor[]){
  
  int option = -1;

  Material* novoMaterial = (Material *)malloc(sizeof(Material));

  novoMaterial-> codigo = material->codigo;
  novoMaterial->qtd = material->qtd;
  novoMaterial->preco = material->preco; 

  //copy strings
  strcpy(novoMaterial->localizacao,material->localizacao);
  strcpy(novoMaterial->nome,material->nome); 


  if(campo != -1){
    option = campo;
  }else {
    printf("Selecione o que deseja alterar: \n 1-> Estoque\n 2-> Preco\n 3-> Localizacao\n Outro -> cancelar\n");
    scanf("%d",&option);
  }

  printf("\n\n");

  switch(option){
    case 1: {
      if(valor != NULL){
        novoMaterial->qtd = atoi(valor);
      }else{
        int teste;
        printf("Insira o novo estoque: ");
        scanf("%d",&novoMaterial->qtd);
      }
      break;
    }

    case 2: {
      if(valor != NULL){
        novoMaterial->preco = atof(valor);
      }else{
        printf("Insira o novo preco: ");
        scanf("%f",&novoMaterial->preco);
      }
      break;
    }

    case 3: {
      if(valor != NULL){
        strcpy(novoMaterial->localizacao,valor);
      }else{
        printf("Insira a nova localizacao: ");
        scanf("%*c%[^\n]%*c",novoMaterial->localizacao);
      }
      break;
    }

    default: {
      printf("\n\n Operacao cancelada!! \n\n");
      break;
    }
  }

  return novoMaterial;

}

void mostraMaterial(Material* material){
 printf("\n\n");
  
  printf("codigo: %d\n",material->codigo);
  printf("nome: %s\n",material->nome);
  printf("preco: %f\n",material->preco);
  printf("estoque atual: %d\n",material->qtd);
  printf("localizacao: %s\n",material->localizacao); 

  printf("\n\n");
}

void mostraMaterialPorPos(int pos){
  FILE *arq = fopen(arquivoMaterial, "rb+");

  Material* material = leMaterialArq(arq,pos);

  mostraMaterial(material);

  fclose(arq);
}

void removeMaterial(int pos){
  FILE *arq = fopen(arquivoMaterial, "rb+");

  Material *materialDeletado = leMaterialArq(arq,pos);
  CabMaterial *cabecalho = leCabMaterial(arq);

  materialDeletado->codigo = cabecalho->posLivre;
  //não precisa limpar o arquivo - não esta nas especificacoes do trab;
  cabecalho->posLivre = pos;

  escreveCabMaterial(arq,cabecalho);
  escreveMaterialArq(arq,materialDeletado,pos);

  fclose(arq);
};

int insereMaterial(Material* material){
  FILE *arq = fopen(arquivoMaterial, "rb+");

  CabMaterial *cab = leCabMaterial(arq);

  int pos;

  if(cab->posLivre == -1){
    escreveMaterialArq(arq,material,cab->posTopo);

    pos = cab->posTopo;

    cab->posTopo++;
  }else {
    //pegar o encademanto de materiais deletado
    Material *materialDeletado = leMaterialArq(arq,cab->posLivre);

    //inserir o material na posicao encadeada deletada
    escreveMaterialArq(arq,material,cab->posLivre);

    pos = cab->posLivre;

    cab->posLivre = materialDeletado->codigo;
  }


  escreveCabMaterial(arq,cab);

  fclose(arq);

  return pos;
}