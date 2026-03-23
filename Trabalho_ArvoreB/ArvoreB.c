#include "ArvoreB.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//split
//destruir
//sair
//gravar


No *criarNo() {
    No *novo = (No*) malloc(sizeof(No));

    novo->n = 0;
    novo->folha = 1;

    for (int i = 0; i < F; i++)
        novo->filhos[i] = NULL;

    return novo;
}

ArvB criarArvore(){
    return criarNo();
}

long buscarNaArvore(ArvB B, int matricula){
    if (B == NULL) return -1; // caso a arvore n exista

    int i =0;

    while(i<B->n && matricula > B->chaves[i].matricula){
       i++;
    }

    if(i<B->n && matricula == B->chaves[i].matricula){

        return B->chaves[i].offset;
    }

    if(B->folha)
    {
        return -1;
    }

    return buscarNaArvore(B->filhos[i], matricula);
}

void PesquisarNoArquivo(buscarNaArvore(ArvB B, int matricula) pos){
    FILE *f =fopen("Registro.txt","r");
    if(f==NULL){
        printf("Falha ao abrir o arquivo!");
        return;
    }

    fseek(f,pos,SEEK_SET);
    char linha [200];

    fgets(linha, sizeof(linha), f);

    printf("Registro: %s.", linha);

    fclose(f);

}


long, int cadastrar(){
    string nome;
    int matricula;
    string telefone;
    
    printf("Digite seu nome: ");
    nome =scanf("%[^\n]",nome);
    printf("Digite sua matricula: ");
    matricula= scanf("%d", &matricula);
    printf("Digite seu telefone: ");
    telefone =scanf("%[^\n]",telefone);

    FILE *f =fopen("Registro.txt","a+");
    fseek(f,0,SEEK_END);
    long pos= ftell(f);

    fprintf(f,"%d;%s;%s", matricula, nome,telefone);
    fclose(f);

    return pos, matricula;


}




void gravarEmArquivo(){

}

void sair(){

}

No* buscarFolha(ArvB B,int matricula){
     int i =0;

    while(i<B->n && matricula > B->chaves[i].matricula){
       i++;
    }

    if(B->folha==1){
        return *B;
    }
    return buscarFolha(B->filhos[i], matricula);

}

void split (No *pai, int i, No *filho){
    

}

void inserirNaoCheio(No *no, int matri, long posicao) {
   int i= no->n-1;
   // é folha
   if(no->folha){
     // move as chaves maiores pra direita
        while (i >= 0 && matri < no->chaves[i].matricula) {
            no->chaves[i+1] = no->chaves[i];
            i--;
        }  

        no->chaves[i+1].matricula = matri;
        no->chaves[i+1].offset = posicao;
        no->n++;
   }
   //não folha
   else{
    //tenta achar filho correto
  while (i >= 0 && matri < no->chaves[i].matricula) {
            i--;
        }
        //coloca no intervalo correto
        i++;

        //se esta cheio
        if(no->filhos[i]->n==M){
            split(no,i,no->filhos[i]);

            // decide qual lado seguir
            if (matri > no->chaves[i].matricula) {
                i++;
            }
        }
   }
   inserirNaoCheio(B->filhos[i], matri, posicao );
}

ArvB inserirArv(ArvB B){

    long pos;
    int matricula;

    pos, matricula= cadastrar();

   //caso nula
   if(B==NULL){
    B= criarNo();
    B->chaves[0].matricula = matricula;
    B->chaves[0].offset= pos;
    B->n =1;
    return B;
    
   }
   //no cheio
   if(B->n == M){
    //cria nova raiz que será pai dos splitados
    No *novaRaiz= criarNo();
    novaRaiz->folha = 0;
    novaRaiz->filhos[0] = B;
     //split
     split(novaRaiz,0,B);

     inserirNaoCheio(novaRaiz, matricula, pos);

        return novaRaiz;
   }
   
   // caso no tenha espaço
   inserirNaoCheio(B, matricula, pos);
   return B;
     
  
}

void destroiArvore(ArvB B){
 
}