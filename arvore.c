#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "arvore.h"

#include "arq.h"

#include "material.h"


//abre o arquivo e o reseta para iniciar o programa
void iniciarArvore() {
  FILE * arq = fopen(arquivoArvore, "wb+");

  Cab * cab = (Cab * ) malloc(sizeof(Cab));

  cab -> raiz = -1;
  cab -> livre = -1;

  cab -> topo = 0;

  escreveCab(arq, cab);

  fclose(arq);
}

//verifica se o nó em questão tem overflow (quantidade de filhos = ORDEM)
//r = No em memoria
//retorna 1 se tiver overflow e 0 se não tiver overflow
int overflow(No * r) {
  return r -> numChaves == ORDEM;
}

int faltaChave(No * r) {
  return r -> numChaves < ORDEM / 2;
}

int ehFolha(No * r) {
  return r -> filho[0] == -1;
}

No * criaNo() {
  No * no = (No * ) malloc(sizeof(No));

  no -> numChaves = 0;

  for (int i = 0; i < ORDEM; i++) {
    no -> posDado[i] = -1;
    no -> chave[i] = -1;
    no -> filho[i] = -1;
  }

  no -> filho[ORDEM] = -1;

  return no;
}

int split(FILE * arq, No * no, AuxNo * auxNo) {
  No * novoNo = (No * ) malloc(sizeof(No));
  int q = no -> numChaves / 2;

  novoNo -> numChaves = no -> numChaves - q - 1;
  no -> numChaves = q;
  auxNo -> codigo = no -> chave[q];
  auxNo -> posDado = no -> posDado[q];

  int i = 0;
  novoNo -> filho[0] = no -> filho[q + 1];

  for (i = 0; i < novoNo -> numChaves; i++) {
    novoNo -> posDado[i] = no -> posDado[q + i + 1];
    novoNo -> chave[i] = no -> chave[q + i + 1];
    novoNo -> filho[i + 1] = no -> filho[q + i + 2];
  }

  int pos = insereNoArq(arq, novoNo);
  return pos;
}

void adicionaDireita(No * no, int pos, AuxNo * auxNo, int ultimoFilho) {
  int i;
  for (i = no -> numChaves; i > pos; i--) {
    no -> posDado[i] = no -> posDado[i - 1];
    no -> chave[i] = no -> chave[i - 1];
    no -> filho[i + 1] = no -> filho[i];
  }

  no -> posDado[pos] = auxNo -> posDado;
  no -> chave[pos] = auxNo -> codigo;
  no -> filho[pos + 1] = ultimoFilho;
  no -> numChaves++;
}

int buscaPos(No * no, AuxNo * auxNo) {
  for (int i = 0; i < no -> numChaves; i++) {
    if (auxNo -> codigo < no -> chave[i]) {
      return i;
    }
  }

  return no -> numChaves;
}

void insereCodigoAux(FILE * arq, int pos, AuxNo * auxNo) {
  No * no = leNoArquivo(arq, pos);

  int posAdd = buscaPos(no, auxNo);

  if (ehFolha(no)) {
    adicionaDireita(no, posAdd, auxNo, -1);
    escrevenoArq(arq, no, pos);

  } else {
    insereCodigoAux(arq, no -> filho[posAdd], auxNo);

    No * filho = leNoArquivo(arq, no -> filho[posAdd]);

    if (overflow(filho)) {
      AuxNo * novoAux = (AuxNo * ) malloc(sizeof(AuxNo));
      int posFilho = split(arq, filho, novoAux);

      //escrever filho esq atualizado
      escrevenoArq(arq, filho, no -> filho[posAdd]);

      adicionaDireita(no, posAdd, novoAux, posFilho);

      escrevenoArq(arq, no, pos);
    }

  }
}

int insereCodigo(FILE * arq, int pos, AuxNo * auxNo) {
  if (pos == -1) {
    //criar raiz
    No * no = criaNo();
    no -> numChaves = 1;

    no -> posDado[0] = auxNo -> posDado;
    no -> chave[0] = auxNo -> codigo;

    int pos = insereNoArq(arq, no);

    return pos;
  } else {
    insereCodigoAux(arq, pos, auxNo);

    No * no = leNoArquivo(arq, pos);

    if (overflow(no)) {

      AuxNo * novoAux = (AuxNo * ) malloc(sizeof(AuxNo));
      int x = split(arq, no, novoAux);

      No * novaRaiz = criaNo();

      novaRaiz -> posDado[0] = novoAux -> posDado;
      novaRaiz -> chave[0] = novoAux -> codigo;
      novaRaiz -> filho[0] = pos;
      novaRaiz -> filho[1] = x;

      for (int i = (((int) ORDEM / 2) + 1); i < ORDEM; i++) {
        no -> filho[i] = -1;
      }

      escrevenoArq(arq, no, pos);

      novaRaiz -> numChaves = 1;
      int novaPosRaiz = insereNoArq(arq, novaRaiz);

      return novaPosRaiz;
    }

    return pos;
  }
}

void mostraNo(No * no) {

  printf("\n================================================================");
  printf("\nnumChaves: %d\n", no -> numChaves);

  printf("PosDados: [");
  for (int i = 0; i < no -> numChaves; i++) {
    printf("%d - ", no -> posDado[i]);
  }
  printf("]\n");

  printf("Chaves: [");
  for (int i = 0; i < no -> numChaves; i++) {
    printf("%d - ", no -> chave[i]);
  }
  printf("]\n");

  printf("\nFilhos: [");
  for (int i = 0; i < no -> numChaves; i++) {
    printf("%d ", no -> filho[i]);
  }
  printf("%d ", no -> filho[no -> numChaves]);
  printf("]\n");

  printf("================================================================\n");

}

void mostraMateriais(FILE * arq, int pos) {

  if (pos == -1) {
    return;
  }

  No * no = leNoArquivo(arq, pos);

  for (int i = 0; i < no -> numChaves; i++) {
    mostraMateriais(arq, no -> filho[i]);

    mostraMaterialPorPos(no -> posDado[i]);
  }

  mostraMateriais(arq, no -> filho[no -> numChaves]);

}

int posDado(FILE * arq, int pos, int codigo) {
  if (pos == -1) {
    return -1;
  }

  No * no = leNoArquivo(arq, pos);

  for (int i = 0; i < no -> numChaves; i++) {
    if (codigo < no -> chave[i]) {
      //pode estar abaixo

      return posDado(arq, no -> filho[i], codigo);
    }

    if (codigo == no -> chave[i]) {
      //retornar a posicao do dado
      return no -> posDado[i];
    }
  }

  return posDado(arq, no -> filho[no -> numChaves], codigo);

}

void adicionaNaEsquerda(No * no, AuxNo * auxNo) {

  for (int i = no -> numChaves; i > 0; i--) {
    no -> posDado[i] = no -> posDado[i - 1];
    no -> chave[i] = no -> chave[i - 1];
    no -> filho[i] = no -> filho[i - 1];
  }

  no -> posDado[0] = auxNo -> posDado;
  no -> chave[0] = auxNo -> codigo;
  no -> filho[no -> numChaves + 1] = no -> filho[no -> numChaves];
  no -> numChaves++;
}

AuxNo * maiorCodigo(FILE * arq, int pos) {
  No * no = leNoArquivo(arq, pos);

  if (ehFolha(no)) {
    AuxNo * auxNo = (AuxNo * ) malloc(sizeof(AuxNo));

    auxNo -> codigo = no -> chave[no -> numChaves - 1];
    auxNo -> posDado = no -> posDado[no -> numChaves - 1];

    return auxNo;
  } else {
    return maiorCodigo(arq, no -> filho[no -> numChaves]);
  }
}

int removeCodigo(FILE * arq, int pos, int codigo, int posPai, int desceDireita) {
  No * no = leNoArquivo(arq, pos);

  if (ehFolha(no)) {
    //faca a exclusao aqui

    if (desceDireita) {
      //tera que remover o utlimo

      no -> posDado[no -> numChaves - 1] = -1;
      no -> chave[no -> numChaves - 1] = -1;
      no -> numChaves--;

      escrevenoArq(arq, no, pos);

      return faltaChave(no);
    }

    for (int i = 0; i < no -> numChaves; i++) {

      if (codigo == no -> chave[i]) {
        removeMaterial(no -> posDado[i]);
      }

      if (codigo <= no -> chave[i]) {
        no -> posDado[i] = no -> posDado[i + 1];
        no -> chave[i] = no -> chave[i + 1];
      }
    }

    no -> posDado[no -> numChaves] = -1;
    no -> chave[no -> numChaves] = -1;
    no -> numChaves = no -> numChaves - 1;

    escrevenoArq(arq, no, pos);

    if (posPai == -1) {
      //eh raiz

      if (no -> numChaves == 0) {
        //acabou a arvore
        return -1;
      }

      return pos;
    }

    return faltaChave(no);
  }

  int filhoEstaFaltando = -1;

  if (desceDireita) {
    filhoEstaFaltando = removeCodigo(arq, no -> filho[no -> numChaves], codigo, pos, 1);
  } else {
    int i = 0;

    while (i < no -> numChaves) {
      if (codigo < no -> chave[i] || codigo == no -> chave[i]) {
        break;
      }

      i++;
    }

    if (codigo == no -> chave[i]) {
      //deletar no meio da arvore;

      removeMaterial(no -> posDado[i]);

      AuxNo * auxNo = maiorCodigo(arq, no -> filho[i]);
      no -> chave[i] = auxNo -> codigo;
      no -> posDado[i] = auxNo -> posDado;

      filhoEstaFaltando = removeCodigo(arq, no -> filho[i], codigo, pos, 1);
    } else {
      filhoEstaFaltando = removeCodigo(arq, no -> filho[i], codigo, pos, 0);
    }

  }


  if (filhoEstaFaltando == 0) {
    //não precisa arrumar filho
    escrevenoArq(arq, no, pos);

    if (posPai == -1) {
      //eh raiz

      return pos;
    }

    return 0;
  }

  //tem que arrumar o filho

  int indexFilhoArrumar = -1;
  int indexChave = -1;

  for (int j = 0; j < no -> numChaves; j++) {
    No * filhoArrumarTest = leNoArquivo(arq, no -> filho[j]);

    if (faltaChave(filhoArrumarTest)) {

      indexChave = j;
      indexFilhoArrumar = j;
    }
  }

  if (indexFilhoArrumar == -1) {
    indexFilhoArrumar = no -> numChaves;
  }

  if (indexChave == -1) {
    indexChave = no -> numChaves - 1;
  }

  //teste para direita
  if (indexFilhoArrumar < no -> numChaves) {
    No * noFilhoDirTest = leNoArquivo(arq, no -> filho[indexFilhoArrumar + 1]);

    if (noFilhoDirTest -> numChaves > (ORDEM / 2)) {
      //logica com filho da dir
      No * noFilhoArrumar = leNoArquivo(arq, no -> filho[indexFilhoArrumar]);

      noFilhoArrumar -> chave[noFilhoArrumar -> numChaves] = no -> chave[indexFilhoArrumar];
      noFilhoArrumar -> posDado[noFilhoArrumar -> numChaves + 1] = no -> posDado[indexFilhoArrumar];

      no -> chave[indexFilhoArrumar] = noFilhoDirTest -> chave[0];
      no -> posDado[indexFilhoArrumar] = noFilhoDirTest -> posDado[0];

      for (int i = 0; i < noFilhoDirTest -> numChaves; i++) {
        noFilhoDirTest -> chave[i] = noFilhoDirTest -> chave[i + 1];
        noFilhoDirTest -> posDado[i] = noFilhoDirTest -> posDado[i + 1];
      }

      //remover a ultima casa
      noFilhoDirTest -> chave[noFilhoDirTest -> numChaves] = -1;
      noFilhoDirTest -> posDado[noFilhoDirTest -> numChaves] = -1;

      noFilhoArrumar -> numChaves++;
      noFilhoDirTest -> numChaves--;

      escrevenoArq(arq, no, pos);
      escrevenoArq(arq, noFilhoArrumar, no -> filho[indexFilhoArrumar]);
      escrevenoArq(arq, noFilhoDirTest, no -> filho[indexFilhoArrumar + 1]);

      if (posPai == -1) {
        //eh raiz

        return pos;
      }

      return 0;
    }
  }

  //teste para esq
  if (indexFilhoArrumar != 0) {
    No * noFilhoEsqTest = leNoArquivo(arq, no -> filho[indexFilhoArrumar - 1]);

    if (noFilhoEsqTest -> numChaves > (ORDEM / 2)) {
      //logica com filho da esq

      No * noFilhoArrumar = leNoArquivo(arq, no -> filho[indexFilhoArrumar]);

      //jogar tudo pra direita 
      for (int i = 0; i < noFilhoArrumar -> numChaves; i++) {
        noFilhoArrumar -> chave[i + 1] = noFilhoArrumar -> chave[i];
        noFilhoArrumar -> posDado[i + 1] = noFilhoArrumar -> posDado[i];
      }
      
      noFilhoArrumar -> chave[0] = no -> chave[indexChave];
      noFilhoArrumar -> posDado[0] = no -> posDado[indexChave];

      no -> chave[indexChave] = noFilhoEsqTest -> chave[noFilhoEsqTest -> numChaves - 1];
      no -> posDado[indexChave] = noFilhoEsqTest -> posDado[noFilhoEsqTest -> numChaves - 1];

      //remover a ultima casa da esq
      noFilhoEsqTest -> chave[noFilhoEsqTest -> numChaves - 1] = -1;
      noFilhoEsqTest -> posDado[noFilhoEsqTest -> numChaves - 1] = -1;

      noFilhoEsqTest -> numChaves--;
      noFilhoArrumar -> numChaves++;

      escrevenoArq(arq, no, pos);
      escrevenoArq(arq, noFilhoArrumar, no -> filho[indexFilhoArrumar]);
      escrevenoArq(arq, noFilhoEsqTest, no -> filho[indexFilhoArrumar - 1]);

      if (posPai == -1) {
        //eh raiz

        return pos;
      }

      return 0;

    }
  }

  //logica que irmãos não podem emprestar
  int indexJunta = -1;

  //é a ultima casa junta com a esq
  if (indexFilhoArrumar == no -> numChaves) {
    indexJunta = indexFilhoArrumar - 1;
  } else {
    indexJunta = indexFilhoArrumar + 1;
  }

  int posFilhoJunta = no -> filho[indexJunta];
  No * filhoJunta = leNoArquivo(arq, posFilhoJunta);

  int posFilhoArrumar = no -> filho[indexFilhoArrumar];
  No * noFilhoArrumar = leNoArquivo(arq, posFilhoArrumar);

  if (indexJunta < indexFilhoArrumar) {
    //junta com o da esq

    //desce do pai pro filho
    AuxNo * auxNo = (AuxNo * ) malloc(sizeof(AuxNo));

    auxNo -> codigo = no -> chave[indexChave];
    auxNo -> posDado = no -> posDado[indexChave];

    adicionaNaEsquerda(noFilhoArrumar, auxNo);

    //passa tudo do filho da esq pro da direita;
    for (int k = filhoJunta -> numChaves - 1; k >= 0; k--) {

      auxNo -> codigo = filhoJunta -> chave[k];
      auxNo -> posDado = filhoJunta -> posDado[k];

      adicionaNaEsquerda(noFilhoArrumar, auxNo);
    }

    for (int k = 0; k < no -> numChaves; k++) {
      if (k >= indexChave) {
        no -> posDado[k] = no -> posDado[k + 1];
        no -> chave[k] = no -> posDado[k + 1];
      }

      if (k > indexFilhoArrumar) {
        no -> filho[k] = no -> filho[k + 1];
      }
    }

    //arruma pai
    no -> posDado[no -> numChaves - 1] = -1;
    no -> chave[no -> numChaves - 1] = -1;
    no -> filho[no -> numChaves] = -1;
    no -> numChaves--;

    //escreve o filho que foi arrumado
    escrevenoArq(arq, noFilhoArrumar, posFilhoArrumar);

    //exlui filho que foi juntado
    int quebrouAraiz = 0;

    if (posPai == -1 && no -> numChaves == 0) {
      //a raiz passou a ser o nó filho da esq

      quebrouAraiz = 1;

      removeNoArq(arq, no, pos);
    }

    removeNoArq(arq, filhoJunta, posFilhoJunta);

    if (quebrouAraiz) {
      return posFilhoArrumar;
    } else {
      return faltaChave(no);
    }
  } else {
    //junta com o da direta

    //desce do pai pro filho
    noFilhoArrumar -> posDado[noFilhoArrumar -> numChaves] = no -> posDado[indexChave];
    noFilhoArrumar -> chave[noFilhoArrumar -> numChaves] = no -> chave[indexChave];
    noFilhoArrumar -> numChaves++;

    //passa tudo do filho da direta pro da esq;
    for (int k = 0; k < filhoJunta -> numChaves; k++) {
      noFilhoArrumar -> posDado[noFilhoArrumar -> numChaves] = filhoJunta -> posDado[k];
      noFilhoArrumar -> chave[noFilhoArrumar -> numChaves] = filhoJunta -> chave[k];
      noFilhoArrumar -> numChaves++;
    }

    for (int k = 0; k < no -> numChaves; k++) {
      if (k >= indexChave) {
        no -> posDado[k] = no -> posDado[k + 1];
        no -> chave[k] = no -> posDado[k + 1];
      }

      if (k > indexFilhoArrumar) {
        no -> filho[k] = no -> filho[k + 1];
      }
    }

    //arruma pai
    no -> posDado[no -> numChaves - 1] = -1;
    no -> chave[no -> numChaves - 1] = -1;
    no -> filho[no -> numChaves] = -1;
    no -> numChaves--;

    //escreve o filho que foi arrumado
    escrevenoArq(arq, noFilhoArrumar, posFilhoArrumar);

    //exlui filho que foi juntado
    int quebrouAraiz = 0;

    if (posPai == -1 && no -> numChaves == 0) {
      //a raiz passou a ser o nó filho da esq
      quebrouAraiz = 1;

      removeNoArq(arq, no, pos);
    }

    removeNoArq(arq, filhoJunta, posFilhoJunta);

    if (quebrouAraiz) {
      return posFilhoArrumar;
    } else {
      return faltaChave(no);
    }
  }

}

int alturaDaArvore(FILE * arq, int pos) {
  if (pos == -1) {
    return 0;
  }

  No * no = leNoArquivo(arq, pos);

  if (ehFolha(no)) {
    return 1;
  } else {
    return 1 + alturaDaArvore(arq, no -> filho[0]);
  }
}

void mostraNivel(FILE * arq, int pos, int nivel, int nivelAtual) {

  if (pos == -1) {
    return;
  }

  No * no = leNoArquivo(arq, pos);

  if (nivel == nivelAtual) {

    printf("[");
    for (int i = 0; i < no -> numChaves; i++) {
      printf("%d,", no -> chave[i]);
    }

    printf("] ");

    return;
  }

  for (int i = 0; i <= no -> numChaves; i++) {
    mostraNivel(arq, no -> filho[i], nivel, nivelAtual + 1);
  }
};

void arvorePorNivel() {
  FILE * arq = fopen(arquivoArvore, "rb+");

  Cab * cab = leCab(arq);

  int altura = alturaDaArvore(arq, cab -> raiz);

  printf("Altura da arvore é %d\n", altura);

  for (int i = 1; i <= altura; i++) {
    mostraNivel(arq, cab -> raiz, i, 1);
    printf("\n");
  }

  fclose(arq);

}