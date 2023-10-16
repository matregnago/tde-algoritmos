#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct estrutura {
	long long cod;
	char nome[200];
	char id[200];
	char categoria[90];
	char rating[4];
};
typedef struct estrutura ESTRUTURA;

struct indice {
	long long cod;
	struct indice *prox;
};
typedef struct indice INDICE;


typedef struct No {
    char rating[4];
    struct No *esquerda;
    struct No *direita;
    INDICE *primeiro;
    INDICE *ultimo;
    int altura;
} No;

int altura(No *n) {
    if (n == NULL)
        return 0;
    return n->altura;
}


int max(int a, int b) {
    return (a > b) ? a : b;
}


No *novoNo(ESTRUTURA data) {
    No *novo = (No *)malloc(sizeof(No));
    INDICE *aux = (INDICE*)malloc(sizeof(INDICE));
    aux->cod = data.cod;
    aux->prox = NULL;
    strcpy(novo->rating,data.rating);
    novo->primeiro = aux;
    novo->ultimo = aux;
	novo->rating;
    novo->esquerda = NULL;
    novo->direita = NULL;
    novo->altura = 1;
//    printf("Nodo %s criado!\n", novo->rating);
    return novo;
}

No *rotacaoDireita(No *y) {
    No *x = y->esquerda;
    No *T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;
    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;

    return x;
}

No *rotacaoEsquerda(No *x) {
    No *y = x->direita;
    No *T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    x->altura = max(altura(x->esquerda), altura(x->direita)) + 1;
    y->altura = max(altura(y->esquerda), altura(y->direita)) + 1;

    return y;
}

int fatorBalanceamento(No *n) {
    if (n == NULL)
        return 0;
    return altura(n->esquerda) - altura(n->direita);
}

No *inserir(No *raiz, ESTRUTURA data) {
	INDICE *lista_indices;   
    if (raiz == NULL)
        return novoNo(data);

    if (strcmp(data.rating, raiz->rating) < 0)
        raiz->esquerda = inserir(raiz->esquerda, data);
    else if (strcmp(data.rating, raiz->rating) > 0)
        raiz->direita = inserir(raiz->direita, data);
    else{
    	lista_indices = raiz->ultimo;
		INDICE *novo = (INDICE*)malloc(sizeof(INDICE));
		novo->cod = data.cod;
		novo->prox = NULL;
		lista_indices->prox = novo;
		raiz->ultimo = novo;
//		printf("Codigo %lld adicionado ao nodo %s\n", lista_indices->cod, raiz->rating);
        return raiz;
	}

    raiz->altura = 1 + max(altura(raiz->esquerda), altura(raiz->direita));

    int balance = fatorBalanceamento(raiz);

    if (balance > 1 && strcmp(data.rating, raiz->esquerda->rating) < 0)
        return rotacaoDireita(raiz);

    if (balance < -1 && strcmp(data.rating, raiz->direita->rating) > 0)
        return rotacaoEsquerda(raiz);

    if (balance > 1 && strcmp(data.rating, raiz->esquerda->rating) > 0) {
        raiz->esquerda = rotacaoEsquerda(raiz->esquerda);
        return rotacaoDireita(raiz);
    }

    if (balance < -1 && strcmp(data.rating, raiz->direita->rating) < 0) {
        raiz->direita = rotacaoDireita(raiz->direita);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

void percorrerEmOrdem(No *raiz) {
    if (raiz != NULL) {
        percorrerEmOrdem(raiz->esquerda);
        printf("\nRating: %s\n",raiz->rating);
        INDICE *lista_indices = raiz->primeiro;
        while(lista_indices != NULL){
        	printf(" - %lld", lista_indices->cod);
        	lista_indices = lista_indices ->prox;
		}
        percorrerEmOrdem(raiz->direita);
    }
}


No *lerDadosEConstruirArvore(char *nomeArquivo) {
	int z=0;
    FILE *arquivo = fopen(nomeArquivo, "rb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    No *raiz = NULL;
    ESTRUTURA estrutura;

    while (!feof(arquivo)) {
//		while(z < 100000){
        fread(&estrutura, sizeof(ESTRUTURA), 1, arquivo);
        raiz = inserir(raiz, estrutura);
//    	z++;
	}

    fclose(arquivo);
    return raiz;
}

No *consultarElemento(No *raiz, char rating [4]) {
    if (raiz == NULL)
        return NULL;

    if (strcmp(rating, raiz->rating) < 0) {
        return consultarElemento(raiz->esquerda, rating);
    } else if (strcmp(rating, raiz->rating) > 0) {
        return consultarElemento(raiz->direita, rating);
    } else {

        return raiz;
    }
}

int main() {
    char nomeArquivo[20] = "dados.bin";
    No *raiz = lerDadosEConstruirArvore(nomeArquivo);
    int x;

//    printf("Dados na arvore AVL:\n");
//    percorrerEmOrdem(raiz);

    char rating[4] = "4.7";
    long long cod = 91668;

   No *resultado = consultarElemento(raiz, rating);

    if (resultado != NULL) {
    	INDICE *lista_indices;
    	lista_indices = resultado->primeiro;
    	while(lista_indices != NULL){
    		if(lista_indices->cod == cod){
    			ESTRUTURA estrutura;
    			FILE *arquivo = fopen(nomeArquivo, "rb");
    			fseek(arquivo, cod*sizeof(ESTRUTURA), SEEK_SET);
    			fread(&estrutura, sizeof(ESTRUTURA), 1, arquivo);
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
				break;		
			}
			lista_indices = lista_indices->prox;
		}
    	
    } else {
        printf("Elemento com ID %lld não encontrado na Arvore.\n", cod);
    }

    return 0;

}
