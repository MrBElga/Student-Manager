#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <windows.h>

struct TpAlunos{
    char Curso[30], Rua[30], Bairro[30], Cidade[30], Estado[25];
    int Endereco,Dia,Mes,Ano;
    TpAlunos *Ant,*Prox;
};

struct TpDescritor{
    int Qtde;
    TpAlunos *Inicio,*Fim;
};

struct TpNotas{
    char Materia[20];
    int Nota0, Nota2, Frequencia;
    TpAlunos *Prox;
};

TpAlunos *AdcionarAluno(TpAlunos *Lista){
    system("cls");

    return Lista;
}