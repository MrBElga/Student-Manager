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
    int Frequencia;
    float Nota0, Nota2;
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

//CRIA NOVA CAIXA 

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

    Caixa -> Prox = Caixa -> Ant = NULL;
	return Caixa;  
}


//Adciona alunos
void AdcionarAlunos(TpAlunos Lista, TpDescritorA &Desc, char Nome[]){
    TpAlunos *NC = NovaCaixa(Nome), *P;
    NC->ListaNotas = NULL; 
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
    
//Consultar Alunos  
void consultarAluno(TpDescritorA Desc, char Nome[]){
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

//Caixa Materias
TpNotas *NovaCaixaM(char Materia[]){
	TpNotas *Caixa = new TpNotas;
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
void *AdcionarMaterias(TpDescritorA &Desc, char Nome[]){
	char aux[30];
    printf("Digite o Nome da materia: ");
	fflush(stdin);
	gets(aux);
    TpNotas *NC = NovaCaixaM(aux), *P;
    TpAlunos *Lista1 = Desc.Inicio;

    while(strcmp(Lista1->Nome,Nome)!=0){
			Lista1 = Lista1->Prox;
	}
    
    if(Lista1->ListaNotas == NULL)
        Lista1->ListaNotas = NC;
    else{
        P = Lista1->ListaNotas;
        while(P -> prox != NULL)
            P = P -> prox;
        P -> prox = NC;
    }
}

//Excluir Materias
void excluirNotas(TpDescritorA &Desc, char Nome[],char Materia[]){
    TpAlunos *Lista = Desc.Inicio;
    TpNotas *ListaN;
    while(strcmp(Lista->Nome, Nome)!=0){
			Lista = Lista->Prox;
	}

    


}

//Consultar Materias
void consultarNota(TpDescritorA Desc, char Nome[]){
    TpAlunos *Lista = Desc.Inicio;
    TpNotas *ListaN;

    system("cls");
    while(strcmp(Nome,Lista -> Nome)!=0) 
        Lista = Lista -> Prox;
    ListaN = Lista->ListaNotas;
    if(ListaN != NULL){
        while(ListaN != NULL){
            printf("-------%s-------\n",ListaN -> Materia);
            printf("%.2f\n",ListaN -> Nota0);
            printf("%.2f\n",ListaN -> Nota2);
            printf("%d\n",ListaN -> Frequencia);
            ListaN = ListaN -> prox;
        }
    }
    else
        printf("\nAluno nao encontrado");
    getch();
}


//Exibir Materias 
void exibirMaterias(TpDescritorA Desc){
    TpAlunos *Lista = Desc.Inicio;
    TpNotas *ListaN;

    system("cls");
    printf("Materias\n");
    while(Lista != NULL){
        printf("Aluno: %s", Lista -> Nome);
        ListaN = Lista -> ListaNotas;
        if(ListaN != NULL){
            while(ListaN != NULL){
                printf("\n-----%s-----",ListaN->Materia);
                printf("\n%.2f",ListaN->Nota0);
                printf("\n%.2f",ListaN->Nota2);
                printf("\n%d",ListaN->Frequencia);
                ListaN = ListaN->prox;
            }
        }
        printf("\n");
        Lista = Lista->Prox;
    }
    getch();
 }
