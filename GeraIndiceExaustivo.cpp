#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <limits.h>	
struct estrutura {
	long long cod;
	char id[200];
};
typedef struct estrutura ESTRUTURA;

int main() {
	struct estrutura a;
	int l=0;
	int flag;
	long k;
	int z=0;
	long long cod=0;
	char aux[10];
	char *result;
	char Linha[300];
	char csv[30] = "dados_indice_secundario.txt";
	FILE *f = fopen(csv, "rt");
	FILE *g = fopen("indice2.bin", "wb");
//	while(z < 3){
	while(!feof(f)){
		flag=0;
        result = fgets(Linha, 300, f); 
	 	k=0;
      	l=0;
	while(Linha[k] == '"' || Linha[k] == '#' || Linha[k] == 39){
		k++;
	} 
    while(!flag){
    	if(Linha[k] == '"'){
    		flag=1;
    		break;
		}
      	a.id[l] = Linha[k];
		l++;
      	k++;
	  }
		k = k+2;
	while(l < 90){
		a.id[l] = ' ';
		l++;
	}
	  a.id[l] = '\0';
//	  printf("email: %s\n", a.email);
      l=0;
      while(Linha[k] != '\0'){
      	aux[l] = Linha[k];	
		l++;
      	k++;
	  }
	  aux[l] = '\0';
//	  printf("aux: %s\n", aux);
	  a.cod = atoll(aux);
	 	fwrite(&a,sizeof(ESTRUTURA),1,g);
//	  printf("cod: %lld\n", a.cod);

  }
  fclose(f);
  fclose(g);
  g = fopen("indice2.bin", "rb");
  struct estrutura b; 
  int h=0;
  int flag1=0;
  while(!flag1){
//while(h <10 ){
  	fread(&b,sizeof(ESTRUTURA),1,g); 
  	if(!feof(g)){
//	  printf("cod:%lld\nid:%s\n\n",b.cod, b.id);
	  }
	  else{
	  	flag1=1;
	  }
//	  h++;
  }
	printf("Arquivo de indices gerado com sucesso.");
}
 	
