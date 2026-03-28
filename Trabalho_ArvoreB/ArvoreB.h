
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define M 3
#define F (M+1)


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

// inserirNaoCheio, split e cadastrar
ArvB inserirArv(ArvB B, char *arquivoRegistros); //retorna no

long buscarNaArvore(ArvB B, int matricula);//retorna offset

// destruirArvore
void sair(ArvB B); // encera aplicação

// buscarNaArvore
void PesquisarNoArquivo(ArvB B, int matricula, char *arquivoRegistros); // printa o registro 

ArvB carregarArvore(char *arquivoRegistros);

// gravarNos
void gravarEmArquivo(ArvB B, char *arquivoArvore);










