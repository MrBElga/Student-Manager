#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include <time.h>
#include <string.h>


// ##################################################
// # STRUCTS E FUNCOES PARA MANIPULACAO DAS LISTAS  #
// ##################################################


struct TpNotas{
    char Materia[20];
    int Nota0, Nota2, Frequencia;
    TpNotas *prox;
};
struct TpAlunos{
    char Nome[30],Curso[30], Rua[30], Bairro[30], Cidade[30], Estado[25];
    int Endereco,Dia,Mes,Ano;
    TpNotas *ListaNotas;
    TpAlunos *Ant,*Prox;
};

struct TpDescritorA{
    int Qtde;
    TpAlunos *Inicio, *Fim;
};

void IniciarDescA(TpDescritorA &DescA);

//INICIO DOS DESCRITORES
void IniciarDescA(TpDescritorA &DescA){
    DescA.Inicio = DescA.Fim = NULL;
    DescA.Qtde = 0;
}

//ALUNOS
TpAlunos *NovaCaixa(char Nome[]){
	TpAlunos *Caixa = new TpAlunos;
    char aux[30];

	strcpy(Caixa->Nome, Nome[30]);
    printf("\nDigite o Curso: ");
    gets(aux);
    strcpy(Caixa->Curso,aux);
    printf("\nDigite a Cidade: ");
    gets(aux);
    strcpy(Caixa->Cidade,aux);
    printf("\nDigite o Bairro");
    gets(aux);
    strcpy(Caixa->Bairro,aux);
    printf("\nDigite a Rua: ");
    gets(aux);
    strcpy(Caixa->Rua,aux);
    printf("\nDigite o Estado: ");
    gets(aux);
    strcpy(Caixa->Estado,aux);
    printf("\nDigite o Endereco: ");
    gets(aux);
    strcpy(Caixa->Endereco,aux);
    printf("\nDigite o Ano");

    Caixa->Prox = Caixa->Ant = NULL;
	return Caixa;  
}

TpAlunos *AdcionarAlunos(TpAlunos *Lista,char Nome[]){
    TpAlunos *NC = NovaCaixa(Nome), *ant , *atual;
	Desc.Qtde++;
	if(Desc.Inicio==NULL){
		Desc.Inicio=Desc.Fim=NC;
	}
	else{
		if(Desc.Inicio->Info >= Elem){
			NC->prox = Desc.Inicio;
			Desc.Inicio = NC;
		}
		else{
			if(Desc.Fim->Info <= Elem){
				Desc.Fim->prox = NC;
				Desc.Fim = NC;
			}
			else{
				atual = Desc.Inicio;
				atual = Desc.Inicio->prox;
				
				while(atual->Info < Elem){
					ant = atual;
					atual = atual->prox;
				}
					
				NC->prox = atual;
				ant->prox = NC;
			}
		}
	}
    return Lista;
}


//NOTAS
