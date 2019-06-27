#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <string.h>

#define TAM_CHAVE 20
#define TAM_CONTEUDO 50
#define TAM_TOKEN 72

#define TAM_NOME_ARQUIVOS 2

#define FNAME "entrada.dat"
#define FEXIT "saida.dat"

#define MAXNARQS 100
#define MAXMEM 536870912

using namespace std;

struct Registro{
	string chave;
	string conteudo;
};

//estrutura a ser utilizada quando comecar a ordenacao P caminho
struct MinimoHeap{
	Registro registro;
	int indexArquivo;
};

//funcao de comparacao para a ordenacao das runs iniciais
bool cmp(Registro a, Registro b){
	return a.chave < b.chave;
}

//arquivo de entrada principal
FILE *f;

//criando a quantidade maxima de arquivos disponiveis
FILE *arquivosP[MAXNARQS];

void abrirArquivoLeitura(){
    f = fopen(FNAME,"rb+");
}

void abrirArquivoEscrita(){
    f = fopen(FNAME,"wb+");
}

void fecharAquivo(){
	fclose(f);
}


void abrirArquivosAuxLeitura(){
	//estrutura para nomear e abrir todos os arquivos do P caminho
	char nomeArquivosP[TAM_NOME_ARQUIVOS+5];

	for(int i=0; i<MAXNARQS; i++){
		snprintf(nomeArquivosP, sizeof(nomeArquivosP),"%d.dat", i); //converte o nome do valor inteiro para string.dat
		arquivosP[i] = fopen(nomeArquivosP, "rb+");
	}
}

void abrirArquivosAuxEscrita(){
	//estrutura para nomear e abrir todos os arquivos do P caminho
	char nomeArquivosP[TAM_NOME_ARQUIVOS+5];

	for(int i=0; i<MAXNARQS; i++){
		snprintf(nomeArquivosP, sizeof(nomeArquivosP),"%d.dat", i); //converte o nome do valor inteiro para string.dat
		arquivosP[i] = fopen(nomeArquivosP, "wb+");
	}
}

void fecharArquivosAux(){
	//fechar todos os arquivos
	for(int i=0; i<MAXNARQS; i++){
		fclose(arquivosP[i]);
	}
}

//calcular o maximo de registros disponiveis atraves dos valores de memoria e quantidade gasta na linha
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

//funcao que gera os arquivos que conterao as runs
void criarArquivos(int maximoReg){
	int contadorReg = 0;
	int contadorArq = 0;
	char token[TAM_TOKEN];
	Registro registro;

	//vetor de registros para caber a quantidade maxima na run e ordenar futuramente
	vector <Registro> vetorRegistro;
	
	bool temLeitura = true;

	abrirArquivosAuxEscrita();
	abrirArquivoLeitura();

	while(temLeitura){

		while((contadorReg < maximoReg)){

			if(!fgets(token, sizeof(token), f)){
				temLeitura = false;
				break;
			}

			registro=extrairRegistro(token);
			vetorRegistro.push_back(registro);
			contadorReg++;
		}

		//ordenando a runs para armazenar num arquivo
		sort(vetorRegistro.begin(), vetorRegistro.end(), cmp);

		//armazenando a run num arquivo
		for(int i=0; i<vetorRegistro.size();i++){

			char escritaChave[TAM_CHAVE];
			char escritaConteudo[TAM_CONTEUDO];
			strcpy(escritaChave, vetorRegistro[i].chave.c_str());
			strcpy(escritaConteudo, vetorRegistro[i].conteudo.c_str());

			fprintf(arquivosP[contadorArq], "%s,", escritaChave);
			fprintf(arquivosP[contadorArq], "%s\n", escritaConteudo);
		}

		//por ser P caminho, apenas a primeira metade e usada para pegar as runs iniciais
		//faco entao o controle para que ao alcançar a metade, volte a armazenar no arquivo 0
		contadorArq++;
		if(!(contadorArq < MAXNARQS/2)){
			contadorArq=0;
		}

		vetorRegistro.clear();
	}

	fecharArquivosAux();
	fecharAquivo();
}

void ordenarPcaminho(){
	
}

int main(){
	ios_base::sync_with_stdio(false);
	
	//calcular quantidade maxima de registros que a memoria suporta
	int maximoReg=maximoRegistros();
	//criar os arquivos que vao conter as runs
	criarArquivos(maximoReg);
		
	return 0;
}
