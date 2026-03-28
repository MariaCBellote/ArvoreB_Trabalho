#include <stdio.h>
#include <stdlib.h>
#include "ArvoreB.h"

// para rodar: ./programa Registro.txt Gravados.txt



// pega os nomes doa arquivos quando executado
int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("Uso: %s <arquivo_registros> <arquivo_arvore>\n", argv[0]);
        return 1;
    }

    char *arquivoRegistros = argv[1];
    char *arquivoArvore = argv[2];

    ArvB arvore = carregarArvore(arquivoRegistros);    
    int opcao, matricula;

    do {
        printf("\n1 - Cadastrar\n2 - Pesquisar\n3 - Gravar\n4 - Sair\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                arvore = inserirArv(arvore, arquivoRegistros);
                break;

            case 2:
                printf("Digite a matricula: ");
                scanf("%d", &matricula);
                PesquisarNoArquivo(arvore, matricula, arquivoRegistros);
                break;

            case 3:
                gravarEmArquivo(arvore, arquivoArvore);
                break;

            case 4:
                sair(arvore);
                break;
        }

    } while(opcao != 4);

    return 0;
}