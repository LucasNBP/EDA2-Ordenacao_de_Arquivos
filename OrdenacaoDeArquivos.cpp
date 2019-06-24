#include <iostream>
#include <iomanip>

#define TAM_CHAVE 20;
#define TAM_CONTEUDO 50;
#define FNAME "entrada.dat"
#define FEXIT "saida.dat"
#define MAXNARQS 100
#define MAXMEM 536870912
//no minimo trabalhamos com 7.456.540 registros

using namespace std;

struct Registro{
	char chave[TAM_CHAVE];
	char conteudo[TAM_CONTEUDO];
};

FILE *f;

int maximoRegistros(){
	return MAXMEM/TAM_CHAVE+TAM_CONTEUDO;
}

void abrirArquivo(){
    f = fopen(FNAME,"rb+");
    if (!f){
      //printf("erro ao abrir arquivo para leitura");
      f = fopen(FNAME,"wb+");
    }
}

void fecharAquivo(){
	
}

int main(){
	ios_base::sync_with_stdio(false);
	int maximoReg=maximoRegistros();
	
	
	
	return 0;
}
