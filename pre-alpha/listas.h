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


struct TpMateria{
    char Materia[20];
    int Frequencia;
    float Nota0, Nota2;
    TpMateria *prox;
};

struct TpDescritorM{
    int Qtde;
    TpMateria *Inicio, *Fim;

};
struct TpAlunos{
    char Nome[30],Curso[30], Rua[30], Bairro[30], Cidade[30], Estado[25];
    int Endereco,Dia,Mes,Ano;
    TpDescritorM DescM;
    TpMateria *ListaNotas;
    TpAlunos *Ant,*Prox;
};

struct TpDescritorA{
    int Qtde;
    TpAlunos *Inicio, *Fim;
};

//DESCRITORES
void IniciarDescA(TpDescritorA &DescA);
void IniciarDescM(TpDescritorA &DescM);

//ALUNOS
TpAlunos BuscarAlunos(char Nome[], TpDescritorA Desc);
TpAlunos *NovaCaixa(char Nome[]);
void AdcionarAlunos(TpDescritorA &Desc, char Nome[]);
void ExcluirAlunos(char Nome[], TpDescritorA &Desc);
void AlterarAluno(char nome[], TpDescritorA &Desc);
void ConsultarAluno(TpDescritorA Desc, char Nome[]);
void exibirAlunos(TpDescritorA Desc);

//MATERIAS
TpMateria BuscarNotas(TpMateria ListaN, char Materia[]);
TpMateria *NovaCaixaM(char Materia[]);
void AdcionarMaterias(TpDescritorM &Desc);
void ExcluirMateria(char nome[], TpDescritorM &DescM);
void AlterarMateria(char materia[], TpDescritorM &Desc);
void ConsultarMateria(TpDescritorA Desc, char Nome[]);
void ExibirMaterias(TpDescritorA Desc);

//INICIO DOS DESCRITOR
void IniciarDescA(TpDescritorA &DescA){
    DescA.Inicio = DescA.Fim = NULL;
    DescA.Qtde = 0;
}
void IniciarDescM(TpDescritorM &DescM){
    DescM.Inicio = DescM.Fim = NULL;
    DescM.Qtde = 0;
}

//ALUNOS
//BUSCA ALUNOS
TpAlunos BuscarAlunos(char Nome[], TpDescritorA Desc) {
	TpAlunos reg, *lista;
	
	strcpy(reg.Nome, "");
	lista = Desc.Inicio;
	
	while(lista != NULL && strcmp(Nome,lista -> Nome) != 0) {
		lista = lista -> Prox;
	}
	
	if(lista != NULL) {
		reg = *lista;
	}
	
	return reg;
}


//Caixa Alunos
TpAlunos *NovaCaixa(char Nome[]){
	TpAlunos *Caixa = new TpAlunos;
    char aux[30];
	

	strcpy(Caixa -> Nome, Nome);
    printf("\nDigite o Curso: ");
    gets(aux);
    strcpy(Caixa -> Curso,aux);
    printf("\nDigite a Cidade: ");
    gets(aux);
    strcpy(Caixa -> Cidade,aux);
    printf("\nDigite o Bairro: ");
    gets(aux);
    strcpy(Caixa -> Bairro,aux);
    printf("\nDigite a Rua: ");
    gets(aux);
    strcpy(Caixa -> Rua,aux);
    printf("\nDigite o Estado: ");
    gets(aux);
    strcpy(Caixa -> Estado,aux);
    printf("\nDigite o Endereco: ");
    scanf("%d",&Caixa -> Endereco);
    IniciarDescM(Caixa->DescM);
    Caixa -> Prox = Caixa -> Ant = NULL;
   
	return Caixa;  
}


//Adciona alunos
void AdcionarAlunos(TpDescritorA &Desc, char Nome[]){
    TpAlunos *NC = NovaCaixa(Nome), *P;

	Desc.Qtde++;

    if(Desc.Inicio == NULL){//Lista Vazia
        Desc.Inicio = Desc.Fim = NC;
    }
	else if(strcmp(Desc.Inicio -> Nome, NC -> Nome) > 0 ){//Inicio
        NC -> Prox = Desc.Inicio;
        Desc.Inicio -> Ant = NC;
        Desc.Inicio = NC;
    }
    else if(strcmp(Desc.Fim -> Nome, NC -> Nome) < 0 ){//Ultimo
        NC -> Ant = Desc.Fim;
        Desc.Fim -> Prox = NC;
        Desc.Fim = NC;
    }
    else{//meio
       	P = Desc.Inicio -> Prox;
       	while(P -> Prox != NULL && strcmp(P -> Nome, NC  -> Nome) < 0){
            P = P -> Prox;
		}
	    NC -> Prox = P;
	    NC -> Ant = P-> Ant;
	    P -> Ant -> Prox = NC;
	    P -> Ant = NC;
    }   
}

//Excluir Aluno
void ExcluirAlunos(char Nome[], TpDescritorA &Desc) {
	TpAlunos *aux;
    TpMateria *auxN;
	Desc.Qtde--; 

    //deletar Materias do aluno
	aux = Desc.Inicio;
	while(strcmp(aux->Nome,Nome)!=0)
		aux = aux->Prox;
	auxN = aux->DescM.Inicio;
	while(auxN != NULL){
		ExcluirMateria(auxN->Materia,aux->DescM);
		auxN = auxN->prox;
	}
	
	if(Desc.Qtde == 0) {
		aux = Desc.Inicio; 
		Desc.Inicio = Desc.Fim = NULL;
		delete(aux);
	}
	else if(strcmp(Desc.Inicio ->  Nome, Nome) == 0) {
		//inicio
		aux = Desc.Inicio; 
		aux -> Prox -> Ant = NULL;
		Desc.Inicio = aux -> Prox;
		delete(aux);
	}
	else if(strcmp(Desc.Fim ->  Nome, Nome) == 0) {
		//fim
		aux = Desc.Fim; 
		aux -> Ant -> Prox = NULL;
	    Desc.Fim = aux -> Ant;
		delete(aux);
	}
	else {
		//meio
		aux = Desc.Inicio -> Prox; 
		
		while(strcmp(aux -> Nome, Nome) != 0) {
			aux = aux -> Prox;
		}
		
		aux -> Prox -> Ant = aux -> Ant;
		aux -> Ant -> Prox = aux -> Prox;
		delete(aux);
		
	}
}

// Alterar Aluno
void AlterarAluno(char nome[], TpDescritorA &Desc, TpAlunos Alunos) {
	TpAlunos *lista = Desc.Inicio;

	while(strcmp(lista -> Nome, nome)!= 0) {
		lista = lista -> Prox;
	}
	
	strcpy(lista -> Nome, Alunos.Nome);
	strcpy(lista -> Curso, Alunos.Curso);
	strcpy(lista -> Cidade, Alunos.Cidade);
	strcpy(lista -> Bairro, Alunos.Bairro);
	strcpy(lista -> Rua, Alunos.Rua);
	strcpy(lista -> Estado, Alunos.Estado);
    lista->Endereco = Alunos.Endereco;
	//Daniel Elias Fonseca Rumin
    //Ciencia da Computacao
    //Alfredo Marcondes 
    //Benak 
    //Estrada Municipal
    //SaoPaulo
    //3
	// alterar usuarios no servidor

	
}

//Consultar Alunos  
void ConsultarAluno(TpDescritorA Desc, char Nome[]){
    TpAlunos *Lista = Desc.Inicio;

    system("cls");
    while(strcmp(Nome,Lista -> Nome)!=0) 
        Lista = Lista -> Prox;
    if(strcmp(Nome,Lista -> Nome)==0){
    	printf("-------%s-------\n",Lista -> Nome);
        printf("%s\n",Lista -> Curso);
        printf("%s\n",Lista -> Rua);
        printf("%s\n",Lista -> Bairro);
        printf("%s\n",Lista -> Cidade);
        printf("%d\n\n",Lista -> Endereco);
    }
    else
        printf("\nAluno nao encontrado");
    getch();
}

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

//Materia
//BUSCA Materia
TpMateria BuscarNotas(TpDescritorM Desc, char Materia[]) {
	TpMateria reg, *lista = Desc.Inicio;
	
	strcpy(reg.Materia, "");
	while(lista != NULL && strcmp(Materia,lista->Materia) != 0) {
		lista = lista -> prox;
	}
	
	if(lista != NULL) {
		reg = *lista;
	}
	return reg;
}

//Caixa Materias
TpMateria *NovaCaixaM(char Materia[]){
	TpMateria *Caixa = new TpMateria;
    
    int aux;
	float aux1;

	strcpy(Caixa -> Materia, Materia);
    printf("\nDigite a nota do primeiro bim: ");
    scanf("%f",&aux1);
    Caixa -> Nota0 = aux1;
    printf("\nDigite a nota do segundo bim: ");
    scanf("%f",&aux1);
    Caixa -> Nota2 = aux1;
    printf("\nDigite a frequencia do aluno: ");
    scanf("%d",&aux);
    Caixa -> Frequencia = aux;

    Caixa -> prox = NULL;
	return Caixa;  
}

//Adciona Materias 
void AdcionarMaterias(TpDescritorM &Desc){
    TpMateria *NC;
    Desc.Qtde++;

    char auxC[20];

    system("cls");
    printf("\nDigite o Nome da materia: "); 
    fflush(stdin);
    gets(auxC);
 
    NC = NovaCaixaM(auxC);

    if(Desc.Inicio == NULL){//vazio
        Desc.Inicio = Desc.Fim = NC;
    }
    else{//Fim
        Desc.Fim->prox = NC;
        Desc.Fim = NC;
    }
}

//Excluir Materias
void ExcluirMateria(char nome[], TpDescritorM &DescM){
	TpMateria *aux ,*ant;
	DescM.Qtde--; 
	
	aux = DescM.Inicio;
	
	while(strcmp(aux ->Materia,nome) != 0) {
        ant = aux;
		aux = aux -> prox;
	}
	
	//deletar Materias
	if(DescM.Qtde == 0) {
		aux = DescM.Inicio; 
		DescM.Inicio =  DescM.Fim = NULL;
		delete(aux);
	}
	else if(strcmp(DescM.Inicio ->Materia,nome) == 0) {
		//inicio
		aux = DescM.Inicio; 
		DescM.Inicio = aux -> prox;
		delete(aux);
	}
	else if(strcmp(DescM.Fim -> Materia,nome) == 0) {
		//fim
		ant = DescM.Fim; 
		ant -> prox = NULL;
		DescM.Fim = ant;
		delete(aux);
	}
	else {
		//meio
		aux = DescM.Inicio -> prox; 
		
		while(strcmp(aux -> Materia,nome) != 0) {
			aux = aux -> prox;
		}
		ant->prox = aux->prox;
		delete(aux);	
    }
}

// Alterar MAteria
void AlterarMateria(char materia[], TpDescritorM &Desc, TpMateria materias) {
	TpMateria *lista = Desc.Inicio;

	while(strcmp(lista -> Materia, materia)!= 0) {
		lista = lista -> prox;
	}

	strcpy(lista -> Materia, materias.Materia);
	lista -> Nota0 = materias.Nota0;
	lista -> Nota2 = materias.Nota2;
    lista -> Frequencia = materias.Frequencia;
}

//Consultar Materias
void ConsultarMateria(TpDescritorA Desc, char Nome[]){
    TpAlunos *Lista = Desc.Inicio;
    TpMateria *ListaN;

    while(strcmp(Nome,Lista -> Nome)!=0) 
        Lista = Lista -> Prox;
    ListaN = Lista->ListaNotas;
    if(ListaN != NULL){
        while(ListaN != NULL){
            printf("-------%s-------\n",ListaN -> Materia);
            printf("%.2f\n",ListaN -> Nota0);
            printf("%.2f\n",ListaN -> Nota2);
            printf("%d%\n",ListaN -> Frequencia);
            ListaN = ListaN -> prox;
        }
    }
    else
        printf("\nAluno nao encontrado");
    getch();
}

//Exibir Materias 
void ExibirMaterias(TpDescritorA Desc){
    TpAlunos *Lista = Desc.Inicio;
    TpMateria *ListaN;

    while(Lista != NULL){
        printf("Aluno: %s", Lista -> Nome);
        ListaN = Lista->DescM.Inicio;
        while(ListaN != NULL){
              printf("\n-----%s-----",ListaN->Materia);
              printf("\n%.2f",ListaN->Nota0);
             printf("\n%.2f",ListaN->Nota2);
             printf("\n%d%",ListaN->Frequencia);
             ListaN = ListaN->prox;
        }
        
        printf("\n");
        Lista = Lista->Prox;
    }
    getch();
 }