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

char menualt(){
	system("cls");
	printf("[A] - 	ALTERAR NOME\n");
	printf("[B] - 	ALTERAR CURSO\n");
	printf("[C] - 	ALTERAR CIDADE\n");
	printf("[D] -  	ALTERAR BAIRRO \n");
	printf("[E] -  	ALTERAR RUA\n");
	printf("[F] -  	ALTERAR ESTADO\n");
	printf("[G] -  	ALTERAR ENDERECO\n");
	printf("[H] - 	ALTERAR DATA\n");
	printf("OPCAO: ");
	
	return toupper(getch());

}

char menu (){
	system("cls");
	printf("[A] - 	CADASTRAR ALUNOS\n");
	printf("[B] - 	EXCLUIR ALUNOS\n");
	printf("[C] - 	CONSULTAR ALUNOS\n");
	printf("[D] - 	ALTERAR ALUNOS\n");
	printf("[E] -  	EXIBIR ALUNOS\n");
	printf("[F] -  	CADASTRAS NOTA\n");
	printf("[G] -  	EXIBIR NOTAS\n");
	printf("[H] - 	ALTERAR NOTAS DE UM ALUNO\n");
	printf("[I] -  	CONSULTAR NOTAS DE UM ALUNO\n");
	printf("[J] -  	EXIBIR NOTAS\n");
	printf("[K] - 	EXCLUIR NOTAS\n");
	printf("[ESC] - FINALIZAR\n");
	printf("OPCAO: ");

	return toupper(getch());
}



int main(void){
	TpAlunos ListaA,*Lista,Reg;
	TpMateria ListaM,RegM;
	TpDescritorA DescA;



	
	

	char op,aux[30],aux2[30];

	IniciarDescA(DescA);
	

	//VerificarArquivo(DescA);
	
	do{
		
		op = menu();
		
		switch(op)
		{	
			case 'A': 
				system("cls");
				printf("\n## CADASTRO DE ALUNOS ##\n");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)==0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
				AdcionarAlunos(ListaA, DescA, aux);
			break;
			case 'B':
				system("cls");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0  || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
				ExcluirAlunos(aux,DescA);
			break;
			case 'C':
				system("cls");
				printf("## CONSULTA ##\n");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
				ConsultarAluno(DescA,aux);
			break;
			case 'D':
				system("cls");
				printf("## ALTERAR ##\n");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
					system("cls");
					Reg=BuscarAlunos(aux,DescA);
					op = menualt();
					system("cls");
					switch(op)
					{
						case 'A':
							printf("Digite o Novo Nome do Aluno: ");
							fflush(stdin);
							gets(aux2);
							strcpy(ListaA.Nome,aux2);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;
						case 'B':
							strcpy(ListaA.Nome,Reg.Nome);
							printf("\nDigite o Novo Nome do Curso: ");
							gets(aux2);
							strcpy(ListaA.Curso,aux2);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;
						case 'C':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							printf("\nDigite o Novo Nome da cidade: ");
							gets(aux2);
							strcpy(ListaA.Cidade,aux2);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;	
						case 'D':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							printf("\nDigite o Novo Nome do Bairro: ");
							gets(aux2);
							strcpy(ListaA.Bairro,aux2);
							strcpy(ListaA.Rua,Reg.Rua);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;		
						case 'E':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							printf("\nDigite o Novo Nome da Rua: ");
							gets(aux2);
							strcpy(ListaA.Rua,aux2);
							strcpy(ListaA.Estado,Reg.Estado);
							ListaA.Endereco = Reg.Endereco;
						break;					
						case 'F':
							strcpy(ListaA.Nome,Reg.Nome);
							strcpy(ListaA.Curso,Reg.Curso);
							strcpy(ListaA.Cidade,Reg.Cidade);
							strcpy(ListaA.Bairro,Reg.Bairro);
							strcpy(ListaA.Rua,Reg.Rua);
							printf("\nDigite o Novo Nome do Estado: ");
							gets(aux2);
							strcpy(ListaA.Estado,aux2);
							ListaA.Endereco = Reg.Endereco;
						break;		
						case 'H':
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
				AlterarAluno(aux,DescA,ListaA);
			break;
			case 'E':
				system("cls");
				exibirAlunos(DescA);
			break;
			case'F':
				system("cls");
				printf("## ADCIONAR MATERIAS ##\n");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}

				Lista = DescA.Inicio;
				while(strcmp(Lista->Nome,aux) != 0) {
					Lista = Lista -> Prox;
				}
				
				AdcionarMaterias(ListaM,Lista->DescM);
			break;
			case 'G':
				ExibirMaterias(DescA);
			break;

			case 'H':
				system("cls");
				printf("## CONSULTAR MATERIAS ##\n");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);	
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
				ConsultarMateria(DescA,aux);
			break;
			case 'J':
				system("cls");
				printf("## EXCLUIR MATERIA ##\n");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
				printf("Digite o Nome da materia: ");
				fflush(stdin);
				gets(aux2);
				while(strcmp(BuscarNotas(ListaM,aux2).Materia,aux2)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome da materia: ");
					fflush(stdin);
					gets(aux2);
				}

				ExcluirMateria(BuscarNotas(ListaM,aux2).Materia,Lista->DescM);
				//BuscarNotas();
			break;
		}
		
	}while(op!=27);
	//GuadarDados(DescA);
	return 0;
}
