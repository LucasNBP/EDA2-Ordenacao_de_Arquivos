#include <iostream>
#include <iomanip>
#include <algorithm>

#define TAM_CHAVE 20
#define TAM_CONTEUDO 50
#define TAM_TOKEN 72

#define FNAME "entrada.dat"
#define FEXIT "saida.dat"

#define MAXNARQS 100
#define MAXMEM 536870912
//no minimo trabalhamos com 7.669.584 registros

using namespace std;

struct Registro{
	string chave;
	string conteudo;
};

struct MinimoHeap{
	Registro registro;
	int indexArquivo;
};

bool cmp(MinimoHeap a, MinimoHeap b){
	return a.registro.chave > b.registro.chave;
}

FILE *f;

void abrirArquivoLeitura(){
    f = fopen(FNAME,"rb+");
}

void abrirArquivoEscrita(){
    f = fopen(FNAME,"wb+");
}

void fecharAquivo(){
	fclose(f);
}

int maximoRegistros(){
	return MAXMEM/TAM_TOKEN;
}

string extrairTokenChave(char token[]){
	string chave="";
	for(int i=0; i<TAM_CHAVE && token[i]!=','; i++){
		chave+=token[i];
	}
	return chave;
}

string extrairTokenConteudo(char token[]){
	string conteudo="";
	int i;
	for(i=0; i<TAM_CHAVE && token[i]!=','; i++){
	}
	for(int j=(i+1); j<TAM_CONTEUDO && token[j] != '\n'; j++){
		conteudo+=token[j];
	}
	return conteudo;
}

Registro extrairRegistro(char token[]){
	Registro registro;
	registro.chave = extrairTokenChave(token);
	registro.conteudo = extrairTokenConteudo(token);
	return registro;
}

void criarArquivos(int maximoReg){
	int contadorReg = 0;
	char token[TAM_TOKEN];
	Registro registro[maximoReg];
	
	abrirArquivoLeitura();
	

	while(fgets(token, sizeof(token), f)){
		registro[contadorReg]=extrairRegistro(token);
		contadorReg++;
	}
}

int main(){
	ios_base::sync_with_stdio(false);
	
	int maximoReg=maximoRegistros();
	criarArquivos(maximoReg);
	
	char token[TAM_TOKEN];
	Registro registro;
	abrirArquivoLeitura();
	
	fgets(token, sizeof(token), f);
	registro = extrairRegistro(token);
	cout<<"chave: "<<registro.chave<<" conteudo: "<<registro.conteudo<<endl;
	
	fgets(token, sizeof(token), f);
	registro = extrairRegistro(token);
	cout<<"chave: "<<registro.chave<<" conteudo: "<<registro.conteudo<<endl;
	
	fecharAquivo();
	
	return 0;
}

	/*char token[71];
	abrirArquivoLeitura();
	fread(token, sizeof(char),TAM_TOKEN, f);
	cout<<token<<endl;*/
