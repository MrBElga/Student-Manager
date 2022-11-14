#include <stdio.h>
#include <stdlib.h>
#include "listas.h"
#include <ctype.h>
#include <windows.h>
#include <conio2.h>
#include <time.h>
#include <string.h>

char Menu ()
{
	system("cls");
	printf("[A] - Cadastrar Aluno\n");
	printf("[B] - Excluir Aluno\n");
	printf("[C] - Consultar Aluno\n");
	printf("[D] - Alterar dados do Aluno\n");
	printf("[E] -  Relatorio dos Alunos\n");
	printf("[ESC] - Finalizar\n");
	
	return toupper(getch());
}



int main(void){
	TpDescritorA DescA;
	TpAlunos ListaA,Reg;
	
	

	char op,aux[30];

	IniciarDescA(DescA);

	//VerificarArquivo(DescA);
	
	do{
		
		op = Menu();
		
		switch(op)
		{	
			case 'A': 
				system("cls");
				printf("\n## CADASTRO DE ALUNOS ##\n");
				printf("Digite o Nome do Aluno: ");fflush(stdin);
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
		}
		
	}while(op!=27);
	//GuadarDados(DescA);
	return 0;
}
