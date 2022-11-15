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


char menu (){
	system("cls");
	printf("[A] - 	CADASTRAR ALUNOS\n");
	printf("[B] - 	EXCLUIR ALUNOS\n");
	printf("[C] - 	CONSULTAR ALUNOS\n");
	printf("[D] - 	ALTERAR ALUNOS\n");
	printf("[E] -  	EXIBIR ALUNOS\n");
	printf("[F] -  	CADASTRAS NOTA\n");
	printf("[G] -  	EXIBIR NOTAS\n");
	printf("[D] - 	ALTERAR NOTAS DE UM ALUNO\n");
	printf("[H] -  	CONSULTAR NOTAS DE UM ALUNO\n");
	printf("[I] -  	EXIBIR NOTAS\n");
	printf("[ESC] - FINALIZAR\n");
	
	return toupper(getch());
}



int main(void){
	TpDescritorA DescA;
	TpAlunos ListaA,Reg;
	TpNotas ListaN;
	
	

	char op,aux[30];

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
				Reg = BuscarAlunos(aux,DescA);
				while(strcmp(aux,Reg.Nome)==0){
					printf("Digite o Nome do Aluno: ");
					gets(aux);
					Reg = BuscarAlunos(aux,DescA);
				}
				AdcionarAlunos(ListaA, DescA, aux);
			break;
			case 'E':
				system("cls");
				exibirAlunos(DescA);
			break;
			case 'C':
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				consultarAluno(DescA,aux);
			break;
			case'F':
				system("cls");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
				AdcionarMaterias(DescA,aux);
			break;
			case 'G':
				
				exibirMaterias(DescA);
			break;

			case 'H':
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				Reg = BuscarAlunos(aux,DescA);
				while(strcmp(aux,Reg.Nome)!=0){
					printf("Digite o Nome do Aluno: ");
					gets(aux);
					Reg = BuscarAlunos(aux,DescA);
				}
				consultarNota(DescA,aux);
			break;
		}
		
	}while(op!=27);
	//GuadarDados(DescA);
	return 0;
}
