#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct indice {
	long long cod;
	char id[200];
};
typedef struct indice INDICE;

struct estrutura {
	long long cod;
	char nome[200];
	char id[200];
	char categoria[90];
	char rating[4];
};
typedef struct estrutura ESTRUTURA;

ESTRUTURA e;
int pesquisa_binaria_arquivo(char elemento[200]) {
    FILE * indice = fopen("indice2.bin", "rb");
    if (indice == NULL) {
        printf("Erro ao abrir o arquivo");
        return -1;
    }
    fseek(indice, 0, SEEK_END);
    long tamanho_arquivo = ftell(indice);
    fseek(indice, 0, SEEK_SET);
    long long tamanho_registro = sizeof(INDICE);
    long long quantidade_registros = tamanho_arquivo / tamanho_registro;
    long long inicio=0;
    long long fim=quantidade_registros;
    long long meio;
    long long i;
    INDICE elemento_meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        fseek(indice, meio * sizeof(INDICE), SEEK_SET);
        fread(&elemento_meio, sizeof(INDICE), 1, indice);
        i = 0;
        while (elemento_meio.id[i] != ' ') {
            i++;
        }
        elemento_meio.id[i] = '\0';
//        printf("inicio: %lld, meio: %lld, fim: %lld\n", inicio, meio, fim);
//        printf("Teste: %s com %s\n", elemento_meio.id, elemento);
        if (!strcmp(elemento_meio.id, elemento)) {
        	FILE * dados = fopen("dados.bin", "rb");
        	fseek(dados, elemento_meio.cod * sizeof(ESTRUTURA), SEEK_SET);
        	fread(&e, sizeof(ESTRUTURA), 1, dados);
            fclose(dados);
            fclose(indice);
            return meio;
        } else if (strcmp(elemento_meio.id,elemento)< 0) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    fclose(indice);
    return -1;
}
int main() {
    char nome_arquivo[10] = "dados.bin";
    char elemento[200] = "ca.rncmedia.pop";
    long long posicao = pesquisa_binaria_arquivo(elemento);
    int x;
    if (posicao != -1) {
        	    		x=0;
						while(e.id[x] != ' '){
		    				x++;
						}
						e.id[x] = '\0';
						x=0;
		    			while(e.nome[x] != ';'){
		    				x++;
						}
						e.nome[x] = '\0';
							x=0;
		    			while(e.categoria[x] != ';'){
		    				x++;
						}
						e.categoria[x] = '\0';		
			    		printf("Elemento encontrado:\n");
			        	printf("ID: %s\nNome: %s\nCategoria: %s\nRating: %s\n", e.id, e.nome, e.categoria, e.rating);
    } else {
        printf("O nome %s nao foi encontrado no arquivo.\n", elemento);
    return 0;
	}
}