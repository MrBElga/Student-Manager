#include <stdio.h>
#include <stdlib.h>
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

//INICIO DOS DESCRITOR
void IniciarDescA(TpDescritorA &DescA){
    DescA.Inicio = DescA.Fim = NULL;
    DescA.Qtde = 0;
}

//ALUNOS

//BUSCA ALUNOS
TpAlunos BuscarAlunos(char Nome[], TpDescritorA Desc) {
	TpAlunos reg, *lista;
	
	strcpy(reg.Nome,"");
	lista = Desc.Inicio;
	
	while(lista != NULL && strcmp(Nome,lista -> Nome) != 0) {
		lista = lista -> Prox;
	}
	
	if(lista != NULL) {
		reg = *lista;
	}
	
	return reg;
}

//CRIA NOVA CAIXA 
TpAlunos *NovaCaixa(char Nome[]){
	TpAlunos *Caixa = new TpAlunos;
    char aux[30];
	

	strcpy(Caixa->Nome, Nome);
    printf("\nDigite o Curso: ");
    gets(aux);
    strcpy(Caixa->Curso,aux);
    printf("\nDigite a Cidade: ");
    gets(aux);
    strcpy(Caixa->Cidade,aux);
    printf("\nDigite o Bairro: ");
    gets(aux);
    strcpy(Caixa->Bairro,aux);
    printf("\nDigite a Rua: ");
    gets(aux);
    strcpy(Caixa->Rua,aux);
    printf("\nDigite o Estado: ");
    gets(aux);
    strcpy(Caixa->Estado,aux);
    printf("\nDigite o Endereco: ");
    scanf("%d",&Caixa->Endereco);

    Caixa->Prox = Caixa->Ant = NULL;
	return Caixa;  
}

//Adciona alunos
void AdcionarAlunos(TpAlunos Lista, TpDescritorA &Desc, char Nome[]){
    TpAlunos *NC = NovaCaixa(Nome), *P;
	Desc.Qtde++;

    if(Desc.Inicio == NULL){ //Lista Vazia
        Desc.Inicio = Desc.Fim = NC;
    }
	else{
        if(strcmp(NC->Nome,Desc.Inicio->Nome) > 0 ){//Inicio
            NC -> Prox = Desc.Inicio;
            Desc.Inicio -> Ant = NC;
            Desc.Inicio = NC;
        }
        else{//Ultimo
            if(strcmp(NC->Nome,Desc.Fim->Nome) < 0 ){
                NC -> Ant = Desc.Fim;
                Desc.Fim -> Prox = NC;
                Desc.Fim = NC;
            }
            else{//meio
                    P = Desc.Inicio -> Prox;
                    while(P -> Prox != NULL && strcmp(P -> Nome,NC -> Nome) < 0) {
                        P = P -> Prox;
                    }
                    NC -> Prox = P;
                    NC -> Ant = P-> Ant;
                    P -> Ant -> Prox = NC;
                    P -> Ant = NC;
                }
        }
    }
}


//NOTAS



//Exibir Alunos

void exibirAlunos(TpDescritorA Desc) {
	TpAlunos *lista = Desc.Inicio;
	printf("## ALUNO(S) ##\n");
	while(lista != NULL) {
		
		printf("-------%s-------\n",lista -> Nome);
        printf("%s\n",lista -> Curso);
        printf("%s\n",lista -> Rua);
        printf("%s\n",lista -> Bairro);
        printf("%s\n",lista -> Cidade);
        printf("%d\n\n",lista -> Endereco);
     
		lista = lista -> Prox;
	}
	getch();
}
