#ifndef NO
#define NO

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define arquivoArvore "arvore.bin"

#define ORDEM 5

//estrutura da arvore
typedef struct no 
{
  int posDado[ORDEM]; // posicao do material no aquivo de materiais

  int chave[ORDEM]; //ordem para comportar o verflow
  int filho[ORDEM +1]; //ordem + 1para comportar o verflow
  int numChaves; //vai ser uzado para encadeamento de nos livres tambem (indicando o posicionamento no arquvio do proximo nó ja deletado)
} No;

//estrutura auxiliar para inserção dentro da arvore
typedef struct auxNo 
{
  int posDado; //posicao do dado no arquivo de material
  int codigo; //codigo do material
} AuxNo;


//abre o arquivo e o reseta para iniciar o programa
void iniciarArvore();

//verifica se o nó em questão tem overflow (quantidade de filhos = ORDEM)
//r = No em memoria
//retorna 1 se tiver overflow e 0 se não tiver overflow
int overflow(No *r);

//verifica se o nó em questão tem chaves faltando
//retorna 0 caso não tenha e 1 caso tenha chave faltando
int faltaChave(No *r);

//retorn se o no eh folha
//r: nó para teste -> não pode ser null
//retorn 0 se não folha e 1 se for
int ehFolha(No *r);

//cria um nó em memoria e o retorna
No* criaNo();

//retorna a posicao do novo filho e altera o valor que sera adicionado no pai
//splita o nó criando um novo nó (registrando no arq) e alterando o antigo
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//no : no em memoria que sera splitado -> não pode ser nullptr
//auxNo: estrutura aux para controlar posicao do dado e codigo
int split(FILE *arq,No *no, AuxNo * auxNo);

//adiciona o codigo e posicao do dado nas posicao e empurra os outros elementos pra direita
//no: no em memoria onde sera adicionado
//pos: pos onde sera adicionado no no
//auxNo: estrutura aux para controlar posicao do dado e codigo
//ultimoFilho: posicao do ultimo filho
void adicionaDireita(No* no, int pos ,AuxNo * auxNo, int ultimoFilho);


//busca pos onde devera ser adicionado o valor no no atual
//no: no em memoria onde sera adicionado
//auxNo: estrutura aux para controlar posicao do dado e codigo
//retorna a posicao onde as informacoes foram colocadas
int buscaPos(No* no, AuxNo * auxNo);

//funcao auxiliar recursiva de insercao
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//pos: posicao atual de navegacao do arquivo de nos
//auxNo: estrutura aux para controlar posicao do dado e codigo
void insereCodigoAux(FILE *arq,int pos, AuxNo * auxNo);

//insere o codigo e o posDado na arvore
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//pos: posicao da raiz
//auxNo: estrutura aux para controlar posicao do dado e codigo
int insereCodigo(FILE *arq,int pos, AuxNo * auxNo);

//mostra o no no terminal
//apenas para teste
//no: no em memoria
void mostraNo(No* no);

//mostra os materiais por ordem de codigo
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//pos: posicao da raiz
void mostraMateriais(FILE *arq, int pos);

//busca pelo codigo e retorna a posicao do dado daquele codigo
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//pos: posicao da raiz
//codigo: codigo a ser buscado
int posDado(FILE *arq, int pos, int codigo);

//retorna o maio codigo apartir dessa posicao
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//pos: posicao da raiz ou apartir de onde queira
AuxNo *maiorCodigo(FILE *arq, int pos);

//o no raiz deve retorna a sua posicao ou -1 caso for deletado
//os nos não raiz devem retornar 1 caso tenha chave faltando e 0 caso não tenha
int removeCodigo(FILE * arq, int pos, int codigo, int posPai,int desceDireita);


//descobre a altura da arvore
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//pos: posicao da raiz ou apartir de onde queira
int alturaDaArvore(FILE *arq, int pos);

//mostra os codigos de um nivel da arovre
//arq = arquivo .b onde esta os nos salvos -> não pode ser null
//pos: posicao da raiz ou apartir de onde queira
//nivel: nivel que quer imprimir
//nivelAtual: nivel atual onde esta
void mostraNivel(FILE *arq,int pos, int nivel, int nivelAtual);


//mostra os codigos por nivel da arovre
void arvorePorNivel();


#endif