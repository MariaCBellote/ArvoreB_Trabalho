#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define F 3
#define M 2

typedef struct chave {
int matricula; // valor matricula
long offset;  // possição no arquivos

}chave;
 
typedef struct No{
    int n;                  // quantidade de chaves no nó
    chave chaves[M];          // chaves
    //long posicaoR[M];       // posição do registro no arquivo

    struct No *filhos[F];   // ponteiros para filhos

    int folha;               // indica se é folha(ultimo)


}No;

typedef No *ArvB;

// criar arvore
No *criarNo();


// inserir 
// busca saber aonde vai sempre folha
// vazio? insere, se não acaba
// se no tiver cheio:
// insere
// split* e promotion
// adicionar ao offset
ArvB inserirArv(ArvB B, int chave, int posicao); //?

// buscar pesquisar
// busca nos
// busca chaves partindo de nos 
//
int buscarNaArvore(ArvB B, int matricula);//Chave *buscar();

// destruir arv
void destroiArvore(ArvB B);















