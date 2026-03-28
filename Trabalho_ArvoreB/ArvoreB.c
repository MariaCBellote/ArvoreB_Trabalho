#include "ArvoreB.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* 
NÃO PRECISA MAIS PORQUE NOSSO CODIGO JA CRIA A ARVORE QUANDO NÃO TIVER
ArvB criarArvore(){
    return criarNo();
}

NO FIM NÃO FOI PRECISO
Busca recursivamente a folha onde a chave deve ser inserida
No* buscarFolha(ArvB B,int matricula){
     int i =0;
    while(i<B->n && matricula > B->chaves[i].matricula){
       i++;
    }
    if(B->folha==1){
        return B;
    }
    return buscarFolha(B->filhos[i], matricula);

}
*/

No *criarNo() {
    No *novo = (No*) malloc(sizeof(No));

    novo->n = 0;
    novo->folha = 1;

    for (int i = 0; i < F; i++)
        novo->filhos[i] = NULL;

    return novo;
}

// Pega o arquivo Gravados e salva a raiz
void gravarEmArquivo(ArvB B, char *arquivoArvore){
    FILE *f = fopen(arquivoArvore, "w");

    if (f == NULL){
        printf("Erro ao abrir arquivo\n");
        return;
    }

    // escreve endereço da raiz
    fprintf(f, "Raiz: %p\n", B);

    // percorre a árvore
    gravarNos(B, f);
    fclose(f);
}

// Depois do gravarEmArquivo() pecorre cada nó e salva em Gravados
void gravarNos(No *B, FILE *f){
    if (B == NULL) return;

    // escreve o nó atual
    fprintf(f, "%p | n=%d | folha=%d | chaves: ",B, B->n, B->folha);
    
    // salva cada chave no nó pagina
    for (int i = 0; i < B->n; i++){
        fprintf(f, "%d ", B->chaves[i].matricula);
    }
    // pula a linha para separar os nós
    fprintf(f, "\n");

    // Verifica se tem filhos
    if (!B->folha){
        for (int i = 0; i <= B->n; i++){
            // Salva os filhos
            gravarNos(B->filhos[i], f);
        }
    }
}

// Busca recursiva pecorrendo só na arvore com matricula
long buscarNaArvore(ArvB B, int matricula){ // retorna offset
    if (B == NULL) return -2; // caso a arvore n exista

    int i =0;

    while(i<B->n && matricula > B->chaves[i].matricula){
       i++;
    }

    if(i<B->n && matricula == B->chaves[i].matricula){
        return B->chaves[i].offset;
    }

    if(B->folha){
        return -1;
    }

    return buscarNaArvore(B->filhos[i], matricula);
}

// Depois de chamar o buscarNaArvore() vai no Registro e retorna os dados 
void PesquisarNoArquivo(ArvB B, int matricula, char *arquivoRegistros){
    
    long pos = buscarNaArvore(B, matricula);

    if (pos == -1){
        printf("Registro nao encontrado!\n");
        return;
    } else if(pos == -2) {
        printf("Arvore nao encontrado!\n");
        return;
    }

    FILE *f = fopen(arquivoRegistros,"r");
    if(f == NULL){
        printf("Falha ao abrir o arquivo!\n");
        return;
    }

    // Usa o offset para achar em Registro 
    fseek(f, pos, SEEK_SET);
    char linha[200];
    fgets(linha, sizeof(linha), f);
    // Printa as insformações
    printf("Registro: %s", linha);

    fclose(f);
}

// Chama o destroiArvore() e encerra o programa
void sair(ArvB B){
    destroiArvore(B);
    printf("Memoria liberada. Encerrando programa.\n");
    exit(0);

}

// Apaga a arvore da memoria local
void destroiArvore(ArvB B){
 if (B == NULL) return;

 if (!B->folha){
    for (int i = 0; i <= B->n; i++){
        destroiArvore(B->filhos[i]);
    }
}
free(B);
}

// Usa um vetor temporario para separar o nó em dois
void split(No *pai, int i, No *filho){

    // vetor temporário
    chave temp[M+1];

    // copia as chaves do filho
    for(int j = 0; j < M; j++){
        temp[j] = filho->chaves[j];
    }

    int total = filho->n;
    int meio = total / 2;

    // novo nó (lado direito)
    No *novo = criarNo();
    novo->folha = filho->folha;

    // copia lado direito
    novo->n = total - meio - 1;
    for(int j = 0; j < novo->n; j++){
        novo->chaves[j] = temp[j + meio + 1];
    }

    // filhos (se não for folha)
    if(!filho->folha){
        for(int j = 0; j <= novo->n; j++){
            novo->filhos[j] = filho->filhos[j + meio + 1];
        }
    }

    // reduz filho (lado esquerdo)
    filho->n = meio;

    // abre espaço no pai
    for(int j = pai->n; j > i; j--){
        pai->filhos[j+1] = pai->filhos[j];
        pai->chaves[j] = pai->chaves[j-1];
    }

    // liga novo filho
    pai->filhos[i+1] = novo;

    // sobe chave do meio
    pai->chaves[i] = temp[meio];

    pai->n++;
}

// Faz a inserção 
void inserirNaoCheio(No *no, int matri, long posicao) {

    int i = no->n - 1;

    // Confere se é folha
    if(no->folha){
        while (i >= 0 && matri < no->chaves[i].matricula) {
            no->chaves[i+1] = no->chaves[i];
            i--;
        }

        no->chaves[i+1].matricula = matri;
        no->chaves[i+1].offset = posicao;
        no->n++;
    }

    else{
        while (i >= 0 && matri < no->chaves[i].matricula) {
            i--;
        }
        i++;

        // filho está cheio
        if(no->filhos[i]->n == M){
            split(no, i, no->filhos[i]);

            // decide lado correto depois do split
            if (matri > no->chaves[i].matricula){
                i++;
            }
        }

        inserirNaoCheio(no->filhos[i], matri, posicao);
    }
}

// Pede a matricula, chama cadastrar(), e chama split() ou salvar em direto com inserirNaoCheio()
ArvB inserirArv(ArvB B, char *arquivoRegistros){

    int matricula;

    printf("Digite sua matricula: ");
    scanf("%d", &matricula);

    // evita duplicado
    if (buscarNaArvore(B, matricula) != -1){
        printf("Matricula ja existe!\n");
        return B;
    }

    // pega offset
    long pos = cadastrar(&matricula, arquivoRegistros);

    // árvore vazia
    if(B == NULL){
        B = criarNo();
        B->chaves[0].matricula = matricula;
        B->chaves[0].offset = pos;
        B->n = 1;
        return B;
    }

    // raiz cheia então cria nova raiz
    if(B->n == M){
        No *novaRaiz = criarNo();
        novaRaiz->folha = 0;
        novaRaiz->filhos[0] = B;

        split(novaRaiz, 0, B);

        inserirNaoCheio(novaRaiz, matricula, pos);

        return novaRaiz;
    }

    // raiz não cheia
    inserirNaoCheio(B, matricula, pos);
    return B;
}

// Recebe a matricula do inserirArv() e pefe nome e telefone para salvar em registro
long cadastrar(int *matricula, char *arquivoRegistros){ // Retornar o offset
    char nome[100];
    char telefone[50];

    printf("Digite seu nome: ");
    scanf(" %[^\n]", nome);


    printf("Digite seu telefone: ");
    scanf(" %[^\n]", telefone);

    FILE *f = fopen(arquivoRegistros, "a+");
    if (f == NULL) {
        printf("Erro ao abrir arquivo\n");
        return -1;
    }

    fseek(f, 0, SEEK_END);
    long pos = ftell(f);

    fprintf(f, "%d;%s;%s\n", *matricula, nome, telefone);

    fclose(f);

    return pos;
}

// Inicia o porgrama com a arvore salva em Registro
ArvB carregarArvore(char *arquivoRegistros){
    FILE *f = fopen(arquivoRegistros, "r");

    if (f == NULL){
        printf("Arquivo nao existe ainda.\n");
        return NULL;
    }

    ArvB B = NULL;
    char linha[200];

    while (1){
        long pos = ftell(f); // pega posição antes de ler

        if (fgets(linha, sizeof(linha), f) == NULL){
            break;
        }

        int matricula;
        char nome[100], telefone[50];

        sscanf(linha, "%d;%[^;];%[^\n]", 
               &matricula, nome, telefone);

        // insere direto na árvore
        if (B == NULL){
            B = criarNo();
            B->chaves[0].matricula = matricula;
            B->chaves[0].offset = pos;
            B->n = 1;
        } else {
            if (B->n == M){
                No *novaRaiz = criarNo();
                novaRaiz->folha = 0;
                novaRaiz->filhos[0] = B;

                split(novaRaiz, 0, B);
                inserirNaoCheio(novaRaiz, matricula, pos);
                B = novaRaiz;
            } else {
                inserirNaoCheio(B, matricula, pos);
            }
        }
    }

    fclose(f);
    return B;
}