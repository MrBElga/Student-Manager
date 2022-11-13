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
	
	char op;
	
	do{
		
		op = Menu();
		
		switch(op)
		{
			case 'A': printf("teste");
				break;
		}
		
	}while(op!=27);
	return 0;
}
