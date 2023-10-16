#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>	
struct estrutura {
	long long cod;
	char nome[200];
	char id[200];
	char categoria[90];
	char rating[4];
};
typedef struct estrutura ESTRUTURA;

int main() {
	struct estrutura a;
	int l=0;
	int flag;
	long k;
	int z=0;
	long long cod=0;
	char *result;
	char Linha[700];
	char csv[30] = "arquivo_dados.txt";
	FILE *f = fopen(csv, "rt");
	FILE *g = fopen("dados.bin", "wb");
//	while(z < 3){
	while(!feof(f)){
		flag=0;
        result = fgets(Linha, 700, f); 
      	a.cod = cod;
//      	printf("%lld\n", a.cod);
      	cod++;
	  k=0;
      l=0;
	while(Linha[k] == '"' || Linha[k] == ',' || Linha[k] == '-'){
		k++;
	} 
    while(!flag){
    	if(Linha[k] == '"'){
    		if(Linha[k+1] == ','){
					flag = 1;
    				break;
			}
		}
		else if(Linha[k] == '-'){
			a.nome[l] = ' ';
		}
      else if(Linha[k] >= 0 && Linha[k] <= 255){
      		a.nome[l] = Linha[k];
		  }
		else{
			a.nome[l] = 'X';
		}
		l++;
      	k++;
	  }
	  while(Linha[k] == '"' || Linha[k] == ',' || Linha[k] == '-'){
		k++;
	}
	while(l < 199){
		a.nome[l] = ';';
		l++;
	}
	  a.nome[l] = '\0';
//	  printf("nome: %s\n", a.nome);
      l=0;
      while(Linha[k] != '"'){
      		a.id[l] = Linha[k];	
		l++;
      	k++;
	  }
	 while(l < 199){
		a.id[l] = ' ';
		l++;
	}
	  a.id[l] = '\0';
//	  printf("id: %s\n", a.id);
	  k = k+3;
	  l=0;
      while(Linha[k] != '"'){
        a.categoria[l] = Linha[k];
		l++;
		k++;
	  }
	while(l < 89){
		a.categoria[l] = ';';
		l++;
	}
	  a.categoria[l] = '\0';
//	  printf("categoria: %s\n", a.categoria);
	  k=k+3;
	  l=0;
      while(Linha[k] != '"'){
        a.rating[l] = Linha[k];
		l++;
		k++;
	  }
	  a.rating[l] = '\0';
//	  printf("rating: %s\n\n", a.rating);
	fwrite(&a,sizeof(ESTRUTURA),1,g);
	z++;
  }
  fclose(f);
  fclose(g);
  g = fopen("dados.bin", "rb");
  struct estrutura b; 
  int flag1=0;
  while(!flag1){
//while(h <3 ){
  	fread(&b,sizeof(ESTRUTURA),1,g); 
  	if(!feof(g)){
//	  printf("cod:%lld\nnome:%s\nid:%s\ncategoria:%s\nrating:%s\nemail:%s\n\n",b.cod, b.nome, b.id, b.categoria, b.rating, b.email);
	  }
	  else{
	  	flag1=1;
	  }
  }
	printf("Arquivo de dados gerado com sucesso.");
}
 	
