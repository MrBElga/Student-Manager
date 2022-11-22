#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include <time.h>
#include <string.h>

struct TpMateria{
    char Materia[20],Nome[30];
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
TpAlunos *NovaCaixa(TpAlunos alunos);
void AdcionarAlunos(TpDescritorA &Desc, TpAlunos alunos);
void ExcluirAlunos(char Nome[], TpDescritorA &Desc);
void AlterarAluno(char nome[], TpDescritorA &Desc, TpAlunos Alunos);
void ConsultarAluno(TpDescritorA Desc, char Nome[]);

//MATERIAS
TpMateria BuscarNotas(TpDescritorM Desc, char Materia[]);
TpMateria *NovaCaixaM(TpMateria Mat);
void AdcionarMaterias(TpMateria materia,TpDescritorM &Desc);
void ExcluirMateria(char nome[], TpDescritorM &DescM);
void AlterarMateria(char materia[], TpDescritorM &Desc, TpMateria materias);
void ConsultarMateria(TpDescritorA Desc, char Nome[]);
void ExibirMaterias(TpDescritorA Desc);

//getters
TpAlunos getNome(TpAlunos &Reg);
TpAlunos getCurso(TpAlunos &Reg);
TpAlunos getCidade(TpAlunos &Reg);
TpAlunos getBairro(TpAlunos &Reg);
TpAlunos getRua(TpAlunos &Reg);
TpAlunos getEstado(TpAlunos &Reg);
TpAlunos getData(TpAlunos &Reg);
TpAlunos getEndereco(TpAlunos &Reg);
TpMateria getMateria(TpMateria &Reg);
TpMateria getNota0(TpMateria &Reg);
TpMateria getNota2(TpMateria &Reg);
TpMateria getFrequencia(TpMateria &Reg);

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
TpAlunos *NovaCaixa(TpAlunos alunos){
	TpAlunos *Caixa = new TpAlunos;

	strcpy(Caixa -> Nome, alunos.Nome);
    strcpy(Caixa -> Curso,alunos.Curso);
    strcpy(Caixa -> Cidade,alunos.Cidade);
    strcpy(Caixa -> Bairro,alunos.Bairro);
    strcpy(Caixa -> Rua,alunos.Rua);
    strcpy(Caixa -> Estado,alunos.Estado);
    Caixa -> Endereco = alunos.Endereco;
	Caixa -> Dia = alunos.Dia;
	Caixa -> Mes = alunos.Mes;
	Caixa -> Ano = alunos.Ano; 
    IniciarDescM(Caixa->DescM);
    Caixa -> Prox = Caixa -> Ant = NULL;
	return Caixa;  
}


//Adciona alunos
void AdcionarAlunos(TpDescritorA &Desc, TpAlunos alunos){
    TpAlunos *NC = NovaCaixa(alunos), *P;

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
	else if(strcmp(Desc.Inicio ->  Nome, Nome) == 0){//inicio
		aux = Desc.Inicio; 
		aux -> Prox -> Ant = NULL;
		Desc.Inicio = aux -> Prox;
		delete(aux);
	}
	else if(strcmp(Desc.Fim ->  Nome, Nome) == 0){//fim
		aux = Desc.Fim; 
		aux -> Ant -> Prox = NULL;
	    Desc.Fim = aux -> Ant;
		delete(aux);
	}
	else {//meio
		aux = Desc.Inicio -> Prox; 
		while(strcmp(aux -> Nome, Nome) != 0){
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
}

//Consultar Alunos  
void ConsultarAluno(TpDescritorA Desc, char Nome[]){
    TpAlunos *Lista = Desc.Inicio;

    while(strcmp(Nome,Lista -> Nome)!=0) 
        Lista = Lista -> Prox;
    if(strcmp(Nome,Lista -> Nome)==0){
    	printf("-------%s-------\n",Lista -> Nome);
        printf("%s\n",Lista -> Curso);
        printf("%s\n",Lista -> Rua);
        printf("%s\n",Lista -> Bairro);
        printf("%s\n",Lista -> Cidade);
        printf("%d\n",Lista -> Endereco);
	 	printf("%d/%d/%d\n\n",Lista -> Dia, Lista -> Mes, Lista -> Ano);
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
		printf("%s\n",lista ->Estado);
        printf("%d\n",lista -> Endereco);
		printf("%d/%d/%d\n\n",lista -> Dia, lista -> Mes, lista -> Ano);
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
TpMateria *NovaCaixaM(TpMateria Mat){
	TpMateria *Caixa = new TpMateria;
    
	strcpy(Caixa -> Materia, Mat.Materia);
	strcpy(Caixa ->Nome, Mat.Nome);
    Caixa -> Nota0 = Mat.Nota0;
    Caixa -> Nota2 = Mat.Nota2;
    Caixa -> Frequencia = Mat.Frequencia;
    Caixa -> prox = NULL;
	return Caixa;  
}

//Adciona Materias 
void AdcionarMaterias(TpMateria materia,TpDescritorM &Desc){
    TpMateria *NC;
    Desc.Qtde++;

    NC = NovaCaixaM(materia);
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
	else if(strcmp(DescM.Inicio ->Materia,nome) == 0) {//inicio
		aux = DescM.Inicio; 
		DescM.Inicio = aux -> prox;
		delete(aux);
	}
	else if(strcmp(DescM.Fim -> Materia,nome) == 0) {//fim
		ant -> prox = NULL;
		DescM.Fim = ant;
		delete(aux);
	}
	else {//meio
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
    ListaN = Lista->DescM.Inicio;
    if(ListaN != NULL){
        while(ListaN != NULL){
            printf("-------%s-------\n",ListaN ->Materia);
            printf("%.2f\n",ListaN -> Nota0);
            printf("%.2f\n",ListaN -> Nota2);
            printf("%d%\n",ListaN -> Frequencia);
            ListaN = ListaN -> prox;
        }
    }
    else
        printf("\nMaterias nao encontradas");
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
 
TpAlunos getNome(TpAlunos &Reg){
	printf("Digite o Nome do Aluno: ");
	fflush(stdin);
	gets(Reg.Nome);
	return Reg;
}

TpAlunos getCurso(TpAlunos &Reg){
	printf("\nDigite o Curso: ");fflush(stdin);
	gets(Reg.Curso);
	return Reg;
}

TpAlunos getCidade(TpAlunos &Reg){
	printf("\nDigite a Cidade: ");fflush(stdin);
	gets(Reg.Cidade);
}

TpAlunos getBairro(TpAlunos &Reg){
	printf("\nDigite o Bairro: ");fflush(stdin);
	gets(Reg.Bairro);
	return Reg;
}

TpAlunos getRua(TpAlunos &Reg){
	printf("\nDigite a Rua: ");fflush(stdin);
	gets(Reg.Rua);
	return Reg;
}

TpAlunos getEstado(TpAlunos &Reg){
	printf("\nDigite o Estado: ");fflush(stdin);
	gets(Reg.Estado);
		return Reg;
}

TpAlunos getEndereco(TpAlunos &Reg){
	printf("\nDigite o Endereco: ");
	scanf("%d",&Reg.Endereco);
	return Reg;
}

TpAlunos getData(TpAlunos &Reg){
	printf("Digite o Dia: ");
	scanf("%d",&Reg.Dia);
	printf("Digite o Mes: ");
	scanf("%d",&Reg.Mes);
	printf("Digite o Ano: ");
	scanf("%d",&Reg.Ano);
	return Reg;
}

TpMateria getMateria(TpMateria &Reg){
	printf("Digite o Nome da Materia: ");
	fflush(stdin);
	gets(Reg.Materia);
	return Reg;
}

TpMateria getNota0(TpMateria &Reg){
	printf("Digite a nota do primeiro bim: ");
	scanf("%f", &Reg.Nota0);
	return Reg;
}

TpMateria getNota2(TpMateria &Reg){
	printf("Digite a nota do segundo bim: ");
	scanf("%f", &Reg.Nota2);
	return Reg;
}

TpMateria getFrequencia(TpMateria &Reg){
	printf("Digite a frequencia: ");
	scanf("%d", &Reg.Frequencia);
	return Reg;
}

void Relatorio(TpDescritorA Desc){
    TpAlunos *Lista = Desc.Inicio;
    TpMateria *ListaN;
	float media=0;
	
    while(Lista != NULL){
        printf("-----Aluno: %s----- \n", Lista -> Nome);
        
        ListaN = Lista->DescM.Inicio;
        while(ListaN != NULL){
        	if(strcmp(ListaN->Nome,Lista->Nome)==0){
        	
	        	printf("%s\n",ListaN->Materia);
				media = (ListaN->Nota0 + ListaN->Nota2)/2;
				printf("%.2f \n",media);
				
				if(media >=6 )
				 	printf("Aprovado\n");
				else
					printf("Reprovado\n");
			
	          
				media = 0;
			}
			ListaN = ListaN->prox;
        }
        printf("\n");	
	
        Lista = Lista->Prox;
    }
    getch();
 }

void RelatorioReprovas(TpDescritorA Desc){
    TpAlunos *Lista = Desc.Inicio;
    TpMateria *ListaN;
	float media=0,cont=0;
	
    while(Lista != NULL){
      
        
        ListaN = Lista->DescM.Inicio;
        while(ListaN != NULL){
        	if(strcmp(ListaN->Nome,Lista->Nome)==0){
				media = (ListaN->Nota0 + ListaN->Nota2)/2;
				if(media<6 ){
					if(cont==0)
						printf("-----Aluno: %s----- \n", Lista -> Nome);
					printf("%s\n",ListaN->Materia);
					printf("%.2f \n",media);
					printf("Reprovado\n\n");
					cont++;
				}
	          
				media = 0;
			}
			ListaN = ListaN->prox;
        }
		cont =0;
        Lista = Lista->Prox;
    }
    getch();
 }
 
void RelatorioM(TpDescritorA Desc, char Mat[]){
 	    TpAlunos *Lista = Desc.Inicio;
 	    TpMateria *ListaN;
 	    while(Lista != NULL){
 	    	ListaN = Lista->DescM.Inicio;
 	    	while(ListaN != NULL){
 	    		if(strcmp(ListaN->Materia,Mat)==0){
 	    			printf("------%s------\n",ListaN->Nome);
 	    			printf("%.2f\n",ListaN->Nota0);
 	    			printf("%.2f\n\n",ListaN->Nota2);
 	    		}
 	    		ListaN = ListaN->prox;
 	    	}
 	    	Lista = Lista->Prox;
 	    }
}

  void RelatorioF(TpDescritorA Desc){
    TpAlunos *Lista = Desc.Inicio;
    TpMateria *ListaN;
	float cont=0;
	
    while(Lista != NULL){
      
        
        ListaN = Lista->DescM.Inicio;
        while(ListaN != NULL){
        	if(strcmp(ListaN->Nome,Lista->Nome)==0){
				
				if(ListaN->Frequencia<80){
					if(cont==0)
						printf("-----Aluno: %s----- \n", Lista -> Nome);
					printf("%s\n",ListaN->Materia);
					printf("%d% \n",ListaN->Frequencia);
					printf("Reprovado\n\n");
					cont++;
				}
			}
			ListaN = ListaN->prox;
        }
		cont =0;
        Lista = Lista->Prox;
    }
    getch();
 }