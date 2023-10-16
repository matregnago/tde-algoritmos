#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct estrutura {
	long long cod;
	char nome[200];
	char id[200];
	char categoria[90];
	char rating[4];
};
typedef struct estrutura ESTRUTURA;


struct indice {
	int num;
	long long int ultimo;
};
typedef struct indice INDICE;
ESTRUTURA e;
int pesquisa_binaria_arquivo(char nome_arquivo[10], long long elemento, long long inicio, long long fim) {
    FILE * arquivo = fopen(nome_arquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo");
        return -1;
    }
//    if(inicio == elemento){
//    	fseek(arquivo, inicio * sizeof(ESTRUTURA), SEEK_SET);
//        fread( &e, sizeof(ESTRUTURA), 1, arquivo);
//        return 0;
//	}
//	else if(fim == elemento){
//    	fseek(arquivo, fim * sizeof(ESTRUTURA), SEEK_SET);
//        fread( &e, sizeof(ESTRUTURA), 1, arquivo);
//        return 0;
//	}
    long long meio;
    ESTRUTURA elemento_meio;
    while (inicio <= fim) {
        meio = (inicio + fim) / 2;
        long offset = meio * sizeof(ESTRUTURA);
        fseek(arquivo, offset, SEEK_SET);
        fread(&elemento_meio, sizeof(ESTRUTURA), 1, arquivo);
//        printf("\nINICIO: %lld\n", inicio);
//   		printf("FIM: %lld\n", fim);
//        printf("MEIO: %lld \n",meio);
//        printf("Teste: %lld com %lld", elemento_meio.cod, elemento);
        if (elemento_meio.cod == elemento) {
        	e = elemento_meio;
            fclose(arquivo);
            return meio;
        } else if (elemento_meio.cod < elemento) {
            inicio = meio + 1;
        } else {
            fim = meio - 1;
        }
    }
    fclose(arquivo);
    return -1;
}

void pesquisa_binaria_arquivo_dados(long long elemento, long long inicio, long long fim){
	char nome_arquivo[10] = "dados.bin";
    long long posicao = pesquisa_binaria_arquivo(nome_arquivo, elemento, inicio, fim);
    if (posicao != -1) {
  		int x=0;
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
        printf("\nO nome %s nao foi encontrado no arquivo.\n", elemento);
	}
}


void pesquisa_binaria_indice(char nome_arquivo[10], long long elemento) {
    FILE * arquivo = fopen(nome_arquivo, "rb");
    fseek(arquivo, 0, SEEK_END);
    long tamanho_arquivo = ftell(arquivo);
    fseek(arquivo, 0, SEEK_SET);
    int aux;
    long long tamanho_registro = sizeof(INDICE);
    long long quantidade_registros = tamanho_arquivo / tamanho_registro;
    INDICE inicio;
    fread( &inicio, sizeof(INDICE), 1, arquivo);
    INDICE fim;
    fseek(arquivo, (quantidade_registros-1)*sizeof(INDICE) , SEEK_SET);
	fread( &fim, sizeof(INDICE), 1, arquivo);
	fseek(arquivo, 0, SEEK_SET);
    INDICE meio;
    long long i;
    while (inicio.num <= fim.num) {
        aux = (inicio.num + fim.num) / 2;
        fseek(arquivo, aux * tamanho_registro, SEEK_SET);
        fread( &meio, sizeof(INDICE), 1, arquivo);
        fseek(arquivo, meio.num * tamanho_registro, SEEK_SET);
//        printf("\nINICIO: %d\n", inicio.num);
//   			printf("FIM: %d\n", fim.num);
//        printf("MEIO: %d | %lld\n",meio.num, meio.ultimo);
        
	if(elemento >= meio.num * 10000 && elemento <= meio.ultimo) {
    		pesquisa_binaria_arquivo_dados(elemento, meio.num*10000, meio.ultimo);
    		fclose(arquivo);   
    		return;
		}
	else if((quantidade_registros-1)*10000 < elemento ){
		pesquisa_binaria_arquivo_dados(elemento, fim.num*10000, fim.ultimo);
		fclose(arquivo);   
    	return;
	}	
      else if (meio.num * 10000 < elemento) {
       		fseek(arquivo, meio.num * tamanho_registro, SEEK_SET);
       		fread( &inicio, sizeof(INDICE), 1, arquivo);
            fseek(arquivo, meio.num * tamanho_registro, SEEK_SET);
        } 
		else if (meio.num * 10000 > elemento){
            fseek(arquivo, (meio.num ) * tamanho_registro, SEEK_SET);
       		fread( &fim, sizeof(INDICE), 1, arquivo);
            fseek(arquivo, meio.num * tamanho_registro, SEEK_SET);
        }
    }
    fclose(arquivo); 
}

void pesquisa_binaria_arquivo_indice(long long elemento){
	char nome_arquivo[12] = "indice1.bin";
    pesquisa_binaria_indice(nome_arquivo, elemento);
}


int main() {
	long long elemento = 873493;
	pesquisa_binaria_arquivo_indice(elemento);
}