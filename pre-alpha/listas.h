// ######################################################################
// #   STRUCTS E FUNCOES PARA MANIPULACAO DAS LISTAS                    #
// ######################################################################

#include <conio2.h>
#include <time.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h

struct TpNotas{
    char Materia[20];
    int Nota0, Nota2, Frequencia;
    TpNotas *prox;
};

struct TpDescritorN{
    int Qtde;
    TpNotas *Inicio, *Fim;
};

struct TpAlunos{
    char Curso[30], Rua[30], Bairro[30], Cidade[30], Estado[25];
    int Endereco,Dia,Mes,Ano;
    TpDescritorN DescM;
    TpNotas *ListaNotas;
    TpAlunos *Ant,*Prox;
};

struct TpDescritorA{
    int Qtde;
    TpAlunos *Inicio, *Fim;
};
void IniciarDescA(TpDescritorA &DescA);
void IniciarDescN(TpDescritorN &DescN);

//INICIO DOS DESCRITORES

void IniciarDescA(TpDescritorA &DescA){
    DescA.Inicio = DescA.Fim = NULL;
    DescA.Qtde = 0;
}

void IniciarDescN(TpDescritorN &DescN){
    DescN.Inicio = DescN.Fim = NULL;
    DescN.Qtde = 0;
}

//ALUNOS



//NOTAS