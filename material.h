#ifndef MATERIAL
#define MATERIAL

typedef struct Material
{   
  int codigo;
  char nome[50];
  int qtd;
  float preco;
  char localizacao[100];
} Material;

typedef struct auxMaterial
{
  int chave;  //codigo do material
  int posDado; //posicao do material no arquivo
} AuxMaterial;


//criar material em memoria
//retorna o material criado
//codigo = codigo do material
//nome = nome do material
//qtd = qtd do material
//preco = preco do material
//localizacao = localizacao do material
Material* criaMaterial(int codigo, char nome[],int qtd,float preco,char localizacao[]);

//editar o material
//cria uma copia do material antigo e  altera o campo em questao 
//material = material em memoria - não pode ser NULL
//campo= campo que deseja alterar do material, 1 = qtd , 2 = preco , 3 = localizacao 
//valor = novo valor a ser colocado no campo em questao
//retorna o material atualizado
Material*  editaMaterial(Material* material,int campo, char valor[]);

//mostra o material no terminal
//material = material em memoria - não pode ser NULL
void mostraMaterial(Material* material);

//mostra o material que esta na posicao pos do arquivo
//pos = posicao do material no arquivo
void mostraMaterialPorPos(int pos);

//remove o material pelo codigo
//pos = posicao do material a ser deletado , deve existir um material nessa posicao
void removeMaterial(int pos);

//insere o material em memoria no arquivo - não pode ser NULL
//retorna a posicao do material no arquivo
int insereMaterial(Material* material);


#endif