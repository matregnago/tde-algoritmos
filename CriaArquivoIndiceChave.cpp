#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


struct indice {
	int num;
	long long ultimo;
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


int main(){
	char arq_dados[10] = "dados.bin";
	FILE * dados = fopen(arq_dados, "rb");
	FILE * indice = fopen("indice1.bin", "wb");
	fseek(dados, 0, SEEK_END);
    long tamanho_arquivo = ftell(dados);
//    printf("%ld\n", tamanho_arquivo);
    fseek(dados, 0, SEEK_SET);
    int tamanho_bloco = 10000;
    long numero_registros = tamanho_arquivo/sizeof(ESTRUTURA);
//    printf("numero registros: %ld\n", numero_registros);
    INDICE ind;
    int i = 0;
    ESTRUTURA e;
    long offset = 10000 * sizeof(ESTRUTURA);
    int flag = 0;
    while(!flag){
    	ind.num = i;
    	i++;
    	fseek(dados, offset *i, SEEK_SET);
    	fread(&e,sizeof(ESTRUTURA),1,dados);
    	if(e.cod + 10000 < numero_registros){
//    	printf("id: %s\n", e.id);
//    	printf("cod: %lld\n", e.cod);
    	ind.ultimo = e.cod;
		fwrite(&ind,sizeof(INDICE),1,indice);
		}
		else{
//		printf("id: %s\n", e.id);
//    	printf("cod: %lld\n", e.cod);
    	ind.ultimo = e.cod;
		fwrite(&ind,sizeof(INDICE),1,indice);
		ind.num = i;	
		fseek(dados,(numero_registros * sizeof(ESTRUTURA)) - sizeof(ESTRUTURA), SEEK_SET);
		fread(&e,sizeof(ESTRUTURA),1,dados);
//		printf("idF: %s\n", e.id);
//    	printf("codF: %lld\n", e.cod);
    	ind.ultimo = e.cod;
		fwrite(&ind,sizeof(INDICE),1,indice);
			flag =1;
		}
	}
	fclose(dados);
	fclose(indice);
	indice = fopen("indice1.bin", "rb");
	fseek(indice, 0, SEEK_SET);
	flag = 0;
	while(!flag){
		fread(&ind ,sizeof(INDICE),1,dados);
		if(!feof(indice)){
		printf("%d | %lld\n", ind.num, ind.ultimo);
		}
		else{
			flag = 1;
		}
	}
}
