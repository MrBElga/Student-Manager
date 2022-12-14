//Daniel Elias Fonseca Rumin 102113149
//Thales Jorge Da silva		 102012253

#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include <time.h>
#include <string.h>

char alunoValido(char Nome[], TpDescritorA Desc) {
	if(strcmp(BuscarAlunos(Nome,Desc).Nome,Nome) == 0) {
		return 0;
	}
	return 1;
}

char notaValida(char Nome[], TpDescritorM Desc) {
	
	if(strcmp(BuscarNotas(Desc,Nome).Materia,Nome) == 0) {
		
		return 0;
	}
	return 1;
}

void recuperarDadosAlunos(TpDescritorA &Desc, FILE *ptrArqMat){
	TpAlunos Reg;

	fscanf(ptrArqMat,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",&Reg.Nome,&Reg.Curso,&Reg.Cidade,&Reg.Bairro,&Reg.Rua,&Reg.Estado,&Reg.Endereco,&Reg.Dia,&Reg.Mes,&Reg.Ano);
	while(!feof(ptrArqMat)){
		AdcionarAlunos(Desc,Reg);
		fscanf(ptrArqMat,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d;%d;%d;%d\n",&Reg.Nome,&Reg.Curso,&Reg.Cidade,&Reg.Bairro,&Reg.Rua,&Reg.Estado,&Reg.Endereco,&Reg.Dia,&Reg.Mes,&Reg.Ano);
	}
	AdcionarAlunos(Desc,Reg);
}

void recuperarDadosMaterias(TpDescritorA &Desc,FILE *ptrArqMat){
	TpMateria Reg;
	TpAlunos *listaAlunos;

	fscanf(ptrArqMat,"%[^%;];%[^;];%f;%f;%d\n",&Reg.Nome,&Reg.Materia,&Reg.Nota0,&Reg.Nota2,&Reg.Frequencia);
	while(!feof(ptrArqMat)){
		listaAlunos = Desc.Inicio; 
		while(strcmp(listaAlunos->Nome,Reg.Nome) != 0) {
			listaAlunos = listaAlunos -> Prox;
		}
		AdcionarMaterias(Reg,listaAlunos->DescM);
		fscanf(ptrArqMat,"%[^%;];%[^;];%f;%f;%d\n",&Reg.Nome,&Reg.Materia,&Reg.Nota0,&Reg.Nota2,&Reg.Frequencia);
	}
	listaAlunos = Desc.Inicio; 
	while(strcmp(listaAlunos->Nome,Reg.Nome) != 0) {
		listaAlunos = listaAlunos -> Prox;
	}
	AdcionarMaterias(Reg,listaAlunos->DescM);
}

int getSize(char nome[])
{
    FILE *file = fopen(nome, "r");

    if(file == NULL)
        return 0;

    fseek(file, 0, SEEK_END);
    int size = ftell(file);
    fclose(file);

    return size;
}

void verificarArquivo(TpDescritorA &Desc){
	FILE *ptrArq;
	TpAlunos *listaAlunos;
	char nome1[20],nome2[20];
	strcpy(nome1,"Alunos.txt");
	strcpy(nome2,"Materias.txt");
	ptrArq = fopen("Alunos.txt","r");
	
	if(ptrArq == NULL){
		fclose(ptrArq);
		ptrArq = fopen("Alunos.txt","w");
	}
	else if(getSize(nome1) != 0){
		recuperarDadosAlunos(Desc, ptrArq);
		fclose(ptrArq);
	
		listaAlunos = Desc.Inicio;

		ptrArq = fopen("Materias.txt","r");
	
		if(ptrArq == NULL){		
			fclose(ptrArq);
			ptrArq = fopen("Materias.txt","w");
		}
		else if(getSize(nome2) != 0){
			recuperarDadosMaterias(Desc, ptrArq);		
		}
	}
	fclose(ptrArq);	
} 

void guadarDados(TpDescritorA &Desc){
	FILE *Alu = fopen("Alunos.txt","w");
	FILE *Mat = fopen("Materias.txt","w");
	
	TpAlunos *lista = Desc.Inicio;
	TpMateria *listaMat;

	while(lista != NULL) {
		fprintf(Alu,"%s;%s;%s;%s;%s;%s;%d;%d;%d;%d\n",lista->Nome,lista->Curso,lista->Cidade,lista->Bairro,lista->Rua,lista->Estado,lista->Endereco,lista->Dia,lista->Mes,lista->Ano);
		listaMat= lista -> DescM.Inicio;		
		while(listaMat != NULL) {
			fprintf(Mat,"%s;%s;%.2f;%.2f;%d\n",listaMat->Nome,listaMat -> Materia,listaMat ->Nota0, listaMat ->Nota2,listaMat->Frequencia);		
			listaMat = listaMat -> prox;
		}
		lista = lista -> Prox;
	}
	fclose(Alu);
	fclose(Mat);
} 

char menualt(){
	system("cls");
	printf("[A] - 	ALTERAR NOME\n");
	printf("[B] - 	ALTERAR CURSO\n");
	printf("[C] -  	ALTERAR RUA\n");
	printf("[D] -  	ALTERAR BAIRRO \n");
	printf("[E] - 	ALTERAR CIDADE\n");
	printf("[F] -  	ALTERAR ESTADO\n");
	printf("[G] -  	ALTERAR ENDERECO\n");
	printf("OPCAO: ");
	return toupper(getch());
}

char menualtM(){
	system("cls");
	printf("[A] - 	ALTERAR NOME\n");
	printf("[B] - 	ALTERAR NOTA DO PRIMEIRO BIM\n");
	printf("[C] -  	ALTERAR NOTA DO SEGUNDO BIM \n");
	printf("[D] - 	ALTERAR FREQUENCIA\n");
	printf("OPCAO: ");
	return toupper(getch());
}

char menu (){
	system("cls");
	printf("----------------------------------\n");
	printf("########## ALUNOS ########## \n" );
	printf("[A] - 	CADASTRAR ALUNOS\n");
	printf("[B] - 	EXCLUIR ALUNOS\n");
	printf("[C] - 	CONSULTAR ALUNOS\n");
	printf("[D] - 	ALTERAR ALUNOS\n");
	printf("[E] -  	EXIBIR ALUNOS\n");
	printf("----------------------------------\n");
	printf("########## MATERIAS ########## \n");
	printf("[F] -  	CADASTRAS MATERIA\n");
	printf("[G] -  	EXIBIR MATERIA\n");
	printf("[H] - 	ALTERAR NOTAS DE UM ALUNO\n");
	printf("[I] -  	CONSULTAR NOTAS DE UM ALUNO\n");
	printf("[J] - 	EXCLUIR MATERIA DE UM ALUNO\n");
	printf("----------------------------------\n");
	printf("########## RELATORIOS ########## \n");
	printf("[K] -  	NOTAS DE UMA MATERIA\n");
	printf("[L] -  	ALUNOS COM REPROVAS\n");
	printf("##################################\n");
	printf("[M] -  	STATUS DE APROVACAO/REPROVACAO DE CADA ALUNO\n");
	printf("[N] -  	ALUNOS REPROVADOS POR FREQUENCIA\n");
	printf("[O] -   EXCLUIR MATERIA\n");
	printf("----------------------------------\n");
	printf("[ESC] - FINALIZAR\n\n");
	printf("OPCAO: ");
	return toupper(getch());
}

int main(void){
	TpAlunos ListaA,*Lista,Reg;
	TpMateria ListaM,RegM,*auxP;
	TpDescritorA DescA;
	TpDescritorM DescM;

	char op,op2,aux[30],aux2[30],aux3[20];
	IniciarDescA(DescA);
	
	verificarArquivo(DescA);
	do{
		op = menu();
		switch(op)
		{	
			case 'A': 
				system("cls");
				printf("\n## CADASTRO DE ALUNOS ##\n");
				getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)==0 || strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
				getCurso(Reg);
				getCidade(Reg);
				getBairro(Reg);
				getRua(Reg);
				getEstado(Reg);
				getEndereco(Reg);
				getData(Reg);
				AdcionarAlunos(DescA, Reg);
			break;
			case 'B':
				system("cls");
				getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)!=0 || strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
				ExcluirAlunos(Reg.Nome,DescA);
			break;
			case 'C':
				system("cls");
				printf("## CONSULTA ##\n");
				getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)!=0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
				ConsultarAluno(DescA,Reg.Nome);
			break;
			case 'D':
				system("cls");
				printf("## ALTERAR ##\n");
				getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)!=0 || strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
					system("cls");
					Reg=BuscarAlunos(Reg.Nome,DescA);
					op2 = menualt();
					system("cls");
					switch(op2)
					{
						case 'A':
							printf("Digite o Novo Nome do Aluno: ");fflush(stdin);
							gets(ListaA.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;
						case 'B':
							strcpy(ListaA.Nome,Reg.Nome);
							printf("\nDigite o Novo Nome do Curso: ");fflush(stdin);
							gets(ListaA.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;
						case 'C':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							printf("\nDigite o Novo Nome da cidade: ");fflush(stdin);
							gets(ListaA.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;	
						case 'D':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							printf("\nDigite o Novo Nome do Bairro: ");fflush(stdin);
							gets(ListaA.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;		
						case 'E':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							printf("\nDigite o Novo Nome da Rua: ");fflush(stdin);
							gets(ListaA.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;					
						case 'F':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							printf("\nDigite o Novo Nome do Estado: ");fflush(stdin);
							gets(ListaA.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;		
						case 'G':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							printf("\nDigite o Novo endereco ");
							scanf("%d",&ListaA.Endereco);
						break;				
					}
				
				AlterarAluno(Reg.Nome,DescA,ListaA);
			break;
			case 'E':
				system("cls");
				exibirAlunos(DescA);
			break;
			case'F':
				system("cls");
				printf("## CADASTRAR MATERIAS ##\n");
				getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)!=0|| strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
				strcpy(ListaM.Nome,Reg.Nome);
				Lista = DescA.Inicio;
				while(strcmp(Lista->Nome,Reg.Nome) != 0) {
					Lista = Lista -> Prox;
				}
				getMateria(ListaM);
				while(strcmp(BuscarNotas(Lista->DescM,ListaM.Materia).Materia,ListaM.Materia)==0 || strcmp(ListaM.Materia," ")==0 || ListaM.Materia[0]=='\0'){
					getMateria(ListaM);
					Lista = DescA.Inicio;
					while(strcmp(Lista->Nome,Reg.Nome) != 0) {
						Lista = Lista -> Prox;
					}
				}
				getNota0(ListaM);
				getNota2(ListaM);
				getFrequencia(ListaM);

				AdcionarMaterias(ListaM,Lista->DescM);
			break;
			case 'G':
				system("cls");
				printf("## MATERIAS ##");
				ExibirMaterias(DescA);
			break;
			case 'H':
				system("cls");
				printf("## ALTERAR MATERIAS ##\n");
				getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)!=0 || strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
				Lista = DescA.Inicio;
				while(Lista!=NULL && strcmp(Lista->Nome,Reg.Nome)!=0){
					Lista = Lista->Prox;
				}
				getMateria(ListaM);
				while(strcmp(BuscarNotas(Lista->DescM,ListaM.Materia).Materia,ListaM.Materia)!=0  || strcmp(ListaM.Materia," ")==0 || ListaM.Materia[0]=='\0'){
					getMateria(ListaM);
					Lista = DescA.Inicio;
					while(Lista!=NULL && strcmp(Lista->Nome,Reg.Nome)!=0){
						Lista = Lista->Prox;
					}
				}
				RegM = BuscarNotas(Lista->DescM,ListaM.Materia);
				system("cls");
				
				op2 = menualtM();
				system("cls");
				switch(op2)
				{
					case 'A':
						printf("Digite o novo nome da materia: ");
						fflush(stdin);
						gets(aux3);
						strcpy(ListaM.Materia,aux3);
						ListaM.Nota0 = RegM.Nota0;
						ListaM.Nota2 = RegM.Nota2;
						ListaM.Frequencia = RegM.Frequencia;
					break;
					case 'B':
						strcpy(ListaM.Materia,RegM.Materia);
						printf("Digite a Nota do primeiro bim: ");
						scanf("%f",&ListaM.Nota0);
						ListaM.Nota2 = 	RegM.Nota2;
						ListaM.Frequencia = RegM.Frequencia;
					break;
					case 'C':
						strcpy(ListaM.Materia,RegM.Materia);
						ListaM.Nota0 = RegM.Nota0;
						printf("Digite a Nota do segundo bim: ");
						scanf("%f",&ListaM.Nota2);
						ListaM.Frequencia = RegM.Frequencia;
					break;	
					case 'D':
						strcpy(RegM.Materia, ListaM.Materia);
						ListaM.Nota0 = RegM.Nota0;
						ListaM.Nota2 = RegM.Nota2;
						printf("Digite a Frequencia: ");
						scanf("%d",&ListaM.Frequencia);
					break;
				}
				AlterarMateria(RegM.Materia,Lista->DescM,ListaM);
			break;
			case 'I':
				system("cls");
				printf("## CONSULTAR ##\n");
				getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)!=0|| strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
				ConsultarMateria(DescA,Reg.Nome);
			break;
			case 'J':
				system("cls");
				printf("## EXCLUIR MATERIA ##\n");
			getNome(Reg);
				while(alunoValido(Reg.Nome,DescA)!=0|| strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					getNome(Reg);
				}
				strcpy(ListaM.Nome,Reg.Nome);
				Lista = DescA.Inicio;
				while(strcmp(Lista->Nome,Reg.Nome) != 0) {
					Lista = Lista -> Prox;
				}
				getMateria(ListaM);
				while(strcmp(BuscarNotas(Lista->DescM,ListaM.Materia).Materia,ListaM.Materia)!=0 || strcmp(ListaM.Materia," ")==0 || ListaM.Materia[0]=='\0'){
					getMateria(ListaM);
					Lista = DescA.Inicio;
					while(strcmp(Lista->Nome,Reg.Nome) != 0) {
						Lista = Lista -> Prox;
					}
				}

				ExcluirMateria(ListaM.Materia,Lista->DescM);
			break;
			case 'K':
				system("cls");
				getMateria(ListaM);
				RelatorioM(DescA,ListaM.Materia);
				getch();
			break;
			case 'L':
				system("cls");
				printf("### Relatorio ###\n\n");
				RelatorioReprovas(DescA);
				getch();
			break;
			case 'M':
				system("cls");
				printf("### Relatorio ###\n\n");
				Relatorio(DescA);
				getch();
			break;
			case 'N':
				system("cls");
				printf("### Relatorio ###\n\n");
				RelatorioF(DescA);
				getch();
			break;
			case 'O':
				system("cls");
				printf("### EXCLUIR ###\n\n");
				getMateria(ListaM);
				while(strcmp(BuscarNotas2(DescA,ListaM.Materia).Materia,ListaM.Materia)!=0 || strcmp(ListaM.Materia," ")==0 || ListaM.Materia[0]=='\0'){
					getMateria(ListaM);
				}
				excluirDeTodos(DescA,ListaM.Materia);
				
			break;
		}
	}while(op!=27);

	guadarDados(DescA);
	return 0;
}
