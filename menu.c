#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arvore.h"
#include "material.h"
#include "arq.h"
#include "arqMaterial.h"

#include "menu.h"

void mostraOpcoes()
{
  printf("\n\nMenu principal\n\n");
  printf("Selecione uma das opcoes abaixo\n\n");

  printf("1-> Inserir material\n");  //feito                   
  printf("2-> Remover material\n");  //feito             
  printf("3-> Alterar material\n");  //feito     
  printf("4-> Carregar informacoes de arquivo texto\n"); 
  printf("5-> Ver informacoes de um material\n"); //feito
  printf("6-> Listar materiais\n"); //feito        
  printf("7-> Imprimir arvore por nivel\n"); //feito         
  printf("8-> Imprimir posicoes livres Dados\n"); //feito      
  printf("9-> Imprimir posicoes livres Indices\n"); //feito             
  printf("10-> Sair\n\n");
}

void inserirMaterialPorArquivo(Material* material){
  FILE *arq = fopen(arquivoArvore, "rb+");

  Cab *cab = leCab(arq);


  int posMaterial = posDado(arq,cab->raiz,material->codigo);
  

  if(posMaterial != -1){
    printf("\n\n !!! Parece que esse código ja existe no sistema !!!\n");
    printf("Cadastro cancelado devido ao codigo repetido!\n\n");
    fclose(arq);

    return;
  }


  AuxNo *auxNo = (AuxNo *)malloc(sizeof(AuxNo));

  auxNo->posDado = insereMaterial(material);
  auxNo->codigo = material->codigo;
  
  int posRaiz = insereCodigo(arq,cab->raiz,auxNo);

  cab = leCab(arq);
  cab->raiz = posRaiz;


  escreveCab(arq,cab);

  fclose(arq);


}

void removeMaterialPorArquivo(int codigo){
  FILE *arq = fopen(arquivoArvore, "rb+");

  Cab *cab = leCab(arq);


  int posMaterial = posDado(arq,cab->raiz,codigo);
  
  if(posMaterial == -1){
    printf("\n\n !!! Parece que esse código não existe no sistema !!!\n");
    printf("Remoção cancelada devido ao codigo não existir!\n\n");
    fclose(arq);

    return;
  }
  
  int posRaiz = removeCodigo(arq,cab->raiz,codigo,-1,0);

  cab = leCab(arq);

  cab->raiz = posRaiz;

  escreveCab(arq,cab);

  fclose(arq);
}

//menu contendo todas as opcoes do sistema
void menuEntrada()
{
  int option = -1;

  while (option != 10)
  {
    mostraOpcoes();

    scanf("%d", &option);

    switch (option)
    {
    case 1:
    {
      opcao1();
      break;
    }

    case 2:
    {
      opcao2();
      break;
    }

    case 3:
    {
      opcao3();
      break;
    }

    case 4:
    {
      opcao4();
      break;
    }

    case 5:
    {
      opcao5();
      break;
    }

    case 6:
    {
      opcao6();
      break;
    }

    case 7:
    {
      opcao7();
      break;
    }

    case 8:
    {
      opcao8();
      break;
    }

    case 9:
    {
      opcao9();
      break;
    }

    case 10:
    {
      break;
    }

    default:
    {
      break;
    }
    }
  }
}

//inserir
void opcao1(){
  printf("Inserir um material\n");
  printf("Inserir os dados: \n");

  int codigo;
  printf("Codigo: ");
  scanf("%d",&codigo);
  printf("\n");


  FILE *arq = fopen(arquivoArvore, "rb+");

  Cab *cab = leCab(arq);


  int posMaterial = posDado(arq,cab->raiz,codigo);
  

  if(posMaterial != -1){
    printf("\n\n !!! Parece que esse código ja existe no sistema !!!\n");
    printf("Cadastro cancelado devido ao codigo repetido!\n\n");

    return;
  }

  char nome[50];
  int qtd;
  float preco;
  char localizacao[100];

  printf("Nome: ");
  scanf ("%*c%[^\n]%*c", nome);
  printf("\n");

  printf("Estoque: ");
  scanf("%d",&qtd);
  printf("\n");

  printf("Preco: ");
  scanf("%f",&preco);
  printf("\n");

  printf("Localizacao: ");
  scanf("%*c%[^\n]%*c",localizacao);
  printf("\n");


  Material* material = criaMaterial(codigo,nome,qtd,preco,localizacao); 

  AuxNo *auxNo = (AuxNo *)malloc(sizeof(AuxNo));

  auxNo->posDado = insereMaterial(material);
  auxNo->codigo = codigo;
  
  int posRaiz = insereCodigo(arq,cab->raiz,auxNo);

  cab = leCab(arq);
  cab->raiz = posRaiz;


  escreveCab(arq,cab);

  printf("\n\n Material adicionado com sucesso!! \n\n");

  fclose(arq);
}

//arrumar quando 
//remover
void opcao2(){
  printf("remover um material\n");
  printf("Inserir o codigo a ser removido: \n");

  int codigo;
  printf("Codigo: ");
  scanf("%d",&codigo);
  printf("\n");


  FILE *arq = fopen(arquivoArvore, "rb+");

  Cab *cab = leCab(arq);


  int posMaterial = posDado(arq,cab->raiz,codigo);
  

  if(posMaterial == -1){
    printf("\n\n !!! Parece que esse material não existe no sistema !!!\n");
    printf("remoção cancelada devido ao codigo repetido!\n\n");

    return;
  }

  int posRaiz = removeCodigo(arq,cab->raiz,codigo,-1,0);

  cab = leCab(arq);

  cab->raiz = posRaiz;

  escreveCab(arq,cab);

  printf("\n\n Material removido com sucesso!! \n\n");

  fclose(arq);
}

//alterar
void opcao3(){
  printf("alterar um material\n");
  printf("Inserir os dados: \n");

  int codigo;
  printf("Codigo: ");
  scanf("%d",&codigo);
  printf("\n");

  FILE *arq = fopen(arquivoArvore, "rb+");
  Cab *cab = leCab(arq);
  int posMaterial = posDado(arq,cab->raiz,codigo);
  
  if(posMaterial == -1){
    printf("\n\n !!! Parece que esse código não existe no sistema !!!\n");
    printf("Alteração cancelada devido ao material não existir!\n\n");

    return;
  }

  fclose(arq);

  FILE *arqMaterial = fopen(arquivoMaterial, "rb+");
  Material *material = leMaterialArq(arqMaterial,posMaterial);
  material = editaMaterial(material,-1,NULL);

  escreveMaterialArq(arqMaterial,material,posMaterial);

  fclose(arqMaterial);

}

//carregar arquivo texto
void opcao4(){
  printf("Carregar informacoes de arquivo texto\n");

  FILE *arq = fopen("input.txt", "r");
  int bufferLength = 255;
  char buffer[bufferLength];

  while (fgets(buffer, bufferLength, arq)) {
    
    char * token = strtok(buffer, ";");

    if(strcmp(token,"I")== 0){
      //insert
      char * code = strtok(NULL, ";");
      char * name = strtok(NULL, ";");
      char * qtd = strtok(NULL, ";");
      char * price = strtok(NULL, ";");
      char * location = strtok(NULL, ";");

      Material* materialToAdd = criaMaterial(atoi(code),name,atoi(qtd),atof(price),location);

      inserirMaterialPorArquivo(materialToAdd);
    }

    if(strcmp(token,"R") == 0){
      //remove
      char * code = strtok(NULL, ";");

      removeMaterialPorArquivo(atoi(code));
    }

    if(strcmp(token,"A") == 0){
      //edit
      char * code = strtok(NULL, ";");
      char * name = strtok(NULL, ";");  //dont use
      char * qtd = strtok(NULL, ";");
      char * price = strtok(NULL, ";");
      char * location = strtok(NULL, ";");


      /* FILE *arq2 = fopen("input.txt", "r");
      Cab *cab = leCab(arq2);

      int position = posDado(arq2,cab->raiz,code); */

       /*printf("code = %s name = %s qtd = %s price = %s location = %s \n",
        code != NULL ? code : "NULL",
        name != NULL ? name : "NULL",
        qtd != NULL ? qtd : "NULL",
        price != NULL ? price : "NULL",
        location != NULL ? location : "NULL");

     if(position != -1){
        MaterialNode* node = getMaterialByCode(atoi(code));

        if(qtd != NULL){
          //update qtd
          node->material = editMaterial(node->material,1,qtd);
        }

        if(price != NULL){
          //update qtd
          node->material = editMaterial(node->material,2,price);
        }

        if(location != NULL){
          //update qtd
          node->material = editMaterial(node->material,3,location);
        }

        FILE *arq2 = fopen(file, "rb+");


        writeNodeOnFile(arq2,node,position);

        fclose(arq2);

      } 
 */
    }
  }

  fclose(arq);
}

//mostrar produto
void opcao5(){  
  printf("Mostrar um material\n");
  printf("Inserir o codigo: \n");

  int codigo;
  printf("Codigo: ");
  scanf("%d",&codigo);
  printf("\n");


  FILE *arq = fopen(arquivoArvore, "rb+");

  Cab *cab = leCab(arq);


  int posMaterial = posDado(arq,cab->raiz,codigo);
  

  if(posMaterial == -1){
    printf("\n\n !!! Parece que esse código não existe no sistema !!!\n");
    printf("Opreção cancelada devido ao codigo não existir!\n\n");

    return;
  }

  fclose(arq);


  mostraMaterialPorPos(posMaterial);

}

//listar produtos
void opcao6(){
  //listar produtos em ordem crescente de codigo
  FILE *arq = fopen(arquivoArvore, "rb+");

  Cab *cab = leCab(arq);


  mostraMateriais(arq,cab->raiz);

  fclose(arq);
}

//mostrar arvore (códigos) por nivel
void opcao7(){
  arvorePorNivel();
}

//mostar posicoes livres dados
void opcao8(){
  FILE *arq = fopen(arquivoMaterial, "rb+");

  CabMaterial *cab = leCabMaterial(arq);

  int pos = cab->posLivre;

  if(pos == -1){
    printf("Sem posições livres no arquvio de dados\n");
  }
  
  while(pos != -1){
    Material* aux = leMaterialArq(arq,pos);
    printf("Posição: %d\n",pos);
    pos = aux->codigo;
  }



  fclose(arq);
}

//mostar posicoes livres indices
void opcao9(){
  FILE *arq = fopen(arquivoArvore, "rb+");

  Cab *cab = leCab(arq);


  mostraCab(cab);

  int pos = cab->livre;

  if(pos == -1){
    printf("Sem posições livres no arquvio de indices\n");
  }
  
  while(pos != -1){
    No* aux = leNoArquivo(arq,pos);
    printf("Posição: %d\n",pos);
    pos = aux->numChaves;
  }

}