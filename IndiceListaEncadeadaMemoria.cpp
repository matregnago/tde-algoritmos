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



struct elemento {
	long long codigo;
	struct elemento *prox;
};
typedef struct elemento ELEMENTO;

struct categoria{
	ELEMENTO *primeiro;
	ELEMENTO *ultimo;
		char categoria[90];
	struct categoria *prox;
};
typedef struct categoria CATEGORIA;


CATEGORIA *cria_lista() {
	FILE* data = fopen("dados.bin", "rb");
	CATEGORIA *lista = NULL;
	char teste[90];
	CATEGORIA *aux_lista;
	ELEMENTO *lista_elemento;
	ELEMENTO *aux_ele;
	int j=0;
	CATEGORIA *aux_cat;
	ESTRUTURA est;
	int k;
	int flag_add=0;
//	fseek(data, 1000000*sizeof(ESTRUTURA),SEEK_SET);
//	while(j < 100000){
	while(!feof(data)){
		fread(&est,sizeof(ESTRUTURA),1,data);
		flag_add=0;
		k=0;
		while(est.categoria[k] != ';' && est.categoria[k] != '\0'){
			k++;
		}
		est.categoria[k] = '\0';
		k=0;
		while(est.id[k] != ' '){
			k++;
		}
		est.id[k] = '\0';
//		printf("\nFazendo: %s\n\n", est.categoria);
		if(lista == NULL){	
			aux_ele = (ELEMENTO*)malloc(sizeof(ELEMENTO));
			aux_ele->codigo = est.cod;
			aux_ele->prox = NULL;
			aux_cat = (CATEGORIA*)malloc(sizeof(CATEGORIA));	
			aux_cat->primeiro = aux_ele;
			aux_cat->ultimo = aux_ele;
			strcpy(aux_cat->categoria,est.categoria);
			aux_cat->prox = NULL;
			lista = aux_cat;
//			printf("1ELEM: %s criada\n", lista->categoria);
		}
		else{
		aux_lista = lista;
		while(aux_lista->prox != NULL){
//			printf("COMPARANDO: %s E %s \n\n", est.categoria, aux_lista->categoria);
			if(!strcmp(est.categoria,aux_lista->categoria)){
				lista_elemento = aux_lista->ultimo;
				aux_ele = (ELEMENTO*)malloc(sizeof(ELEMENTO));
				aux_ele->codigo = est.cod;
				aux_ele->prox = NULL;
				lista_elemento->prox = aux_ele;
				aux_lista->ultimo = aux_ele;
//				printf("ELEMADD: entidade %s recebeu %lld\n", aux_lista->categoria, aux_ele->codigo);
				flag_add = 1;
				break;
			}
			aux_lista = aux_lista->prox;	
		}
	if(!strcmp(est.categoria, aux_lista->categoria) && flag_add==0){
				lista_elemento = aux_lista->ultimo;
				aux_ele = (ELEMENTO*)malloc(sizeof(ELEMENTO));
				aux_ele->codigo = est.cod;
				aux_ele->prox = NULL;
				lista_elemento->prox = aux_ele;
				aux_lista->ultimo = aux_ele;
//				printf("ELEMADD2: entidade %s recebeu %lld\n", aux_lista->categoria, aux_ele->codigo);
		}
		
	else if(aux_lista->prox == NULL && flag_add==0){
//			printf("oii");
			aux_ele = (ELEMENTO*)malloc(sizeof(ELEMENTO));
			aux_ele->codigo = est.cod;
			aux_ele->prox = NULL;
			aux_cat = (CATEGORIA*)malloc(sizeof(CATEGORIA));	
			aux_cat->primeiro = aux_ele;
			aux_cat->ultimo = aux_ele;
			strcpy(aux_cat->categoria,est.categoria);
			aux_cat->prox = NULL;
			aux_lista->prox = aux_cat;
//			printf("CATADD:entidade %s criada\n", aux_lista->prox->categoria);
		}
		}
		j++;
	}
	fclose(data);
	return lista;
}
	void printa_lista(CATEGORIA *lista){
		ELEMENTO *elem;
		while(lista != NULL){
			printf("%s:\n", lista->categoria);
			elem = lista->primeiro;
			while(elem != NULL){
				printf(" - %s\n", elem->codigo);
				elem = elem->prox;
			}
			lista = lista->prox;
			printf("\n");
		}
		
	}
	
	
	void busca_elemento(char categoria[90], long long codigo, CATEGORIA *lista){
		ELEMENTO *lista_elemento;
		int x;
		ESTRUTURA estrutura;
		while(lista != NULL){
			if(!strcmp(lista->categoria, categoria)){
				lista_elemento = lista->primeiro;
//				printf("Achei a categoria: %s\n", lista->categoria);
				while(lista_elemento!=NULL){
//					printf("Testando %lld E %lld\n", codigo, lista_elemento->codigo);
					if(lista_elemento->codigo == codigo ){
						FILE* data = fopen("dados.bin", "rb");
						fseek(data, codigo*sizeof(ESTRUTURA),SEEK_SET);
						fread(&estrutura,sizeof(ESTRUTURA),1,data);	
						x=0;
		    			while(estrutura.id[x] != ' '){
		    				x++;
						}
						estrutura.id[x] = '\0';
						x=0;
		    			while(estrutura.nome[x] != ';'){
		    				x++;
						}
						estrutura.nome[x] = '\0';
							x=0;
		    			while(estrutura.categoria[x] != ';'){
		    				x++;
						}
						estrutura.categoria[x] = '\0';		
			    		printf("Elemento encontrado:\n");
			        	printf("ID: %s\nNome: %s\nCategoria: %s\nRating: %s\n", estrutura.id, estrutura.nome, estrutura.categoria, estrutura.rating);
						fclose(data);
						return;
					}
					lista_elemento = lista_elemento->prox;
				}
			printf("\nElemento nao encontrado\n");
			return;
			}
			lista = lista->prox;
		}
		printf("\nCategoria nao encontrada\n");
	}


int main() {
	CATEGORIA *lista = cria_lista();
//	printa_lista(lista);
	long long codigo = 713744;
	char categoria[90] = "Lifestyle";
	busca_elemento(categoria, codigo, lista);
}