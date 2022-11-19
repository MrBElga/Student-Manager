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


void recuperarDadosAlunos(TpDescritorA &Desc, FILE *ptrArqMat){
	TpAlunos Reg;

	fscanf(ptrArqMat,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",&Reg.Nome,&Reg.Curso,&Reg.Cidade,&Reg.Bairro,&Reg.Rua,&Reg.Estado,&Reg.Endereco);
	while(!feof(ptrArqMat)){
		AdcionarAlunos(Desc,Reg);
		fscanf(ptrArqMat,"%[^;];%[^;];%[^;];%[^;];%[^;];%[^;];%d\n",&Reg.Nome,&Reg.Curso,&Reg.Cidade,&Reg.Bairro,&Reg.Rua,&Reg.Estado,&Reg.Endereco);
	}
	AdcionarAlunos(Desc,Reg);
}
void verificarArquivo(TpDescritorA &Desc){
	FILE *ptrArq;
	TpAlunos *listaAlunos;
	TpMateria *listaMaterias;
	TpDescritorM DescM;

	ptrArq = fopen("Alunos.txt","r");
	if(ptrArq != NULL) {
		recuperarDadosAlunos(Desc, ptrArq);
	}
	fclose(ptrArq);
	
	listaAlunos = Desc.Inicio;


} 

void guadarDados(TpDescritorA &Desc){


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
	printf("[A] - 	CADASTRAR ALUNOS\n");
	printf("[B] - 	EXCLUIR ALUNOS\n");
	printf("[C] - 	CONSULTAR ALUNOS\n");
	printf("[D] - 	ALTERAR ALUNOS\n");
	printf("[E] -  	EXIBIR ALUNOS\n");
	printf("[F] -  	CADASTRAS NOTA\n");
	printf("[G] -  	EXIBIR NOTAS\n");
	printf("[H] - 	ALTERAR NOTAS DE UM ALUNO\n");
	printf("[I] -  	CONSULTAR NOTAS DE UM ALUNO\n");
	printf("[J] - 	EXCLUIR NOTAS\n");
	printf("[ESC] - FINALIZAR\n");
	printf("OPCAO: ");

	return toupper(getch());
}



int main(void){
	TpAlunos ListaA,*Lista,Reg;
	TpMateria ListaM,RegM;
	TpDescritorA DescA;



	
	

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
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(Reg.Nome);
				while(strcmp(BuscarAlunos(Reg.Nome,DescA).Nome,Reg.Nome)==0 || strcmp(Reg.Nome," ")==0 || Reg.Nome[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(Reg.Nome);
				}
				printf("\nDigite o Curso: ");fflush(stdin);
				gets(Reg.Curso);
				printf("\nDigite a Cidade: ");fflush(stdin);
				gets(Reg.Cidade);
				printf("\nDigite o Bairro: ");fflush(stdin);
				gets(Reg.Bairro);
				printf("\nDigite a Rua: ");fflush(stdin);
				gets(Reg.Rua);
				printf("\nDigite o Estado: ");fflush(stdin);
				gets(Reg.Estado);
				printf("\nDigite o Endereco: ");
				scanf("%d",&Reg.Endereco);
				AdcionarAlunos(DescA, Reg);
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
					op2 = menualt();
					system("cls");
					switch(op2)
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
				printf("## CADASTRAR MATERIAS ##\n");
				printf("Digite o Nome do Aluno: ");
				fflush(stdin);
				gets(aux);
				while(strcmp(BuscarAlunos(aux,DescA).Nome,aux)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome do Aluno: ");
					fflush(stdin);
					gets(aux);
				}
				printf("\nDigite a nota do primeiro bim: ");
				scanf("%f",&ListaM.Nota0);
				printf("\nDigite a nota do segundo bim: ");
				scanf("%f",&ListaM.Nota2);
				printf("\nDigite a frequencia do aluno: ");
				scanf("%d",&ListaM.Frequencia);
	
				Lista = DescA.Inicio;
				while(strcmp(Lista->Nome,aux) != 0) {
					Lista = Lista -> Prox;
				}
				
				AdcionarMaterias(ListaM,Lista->DescM);
			break;
			case 'G':
				system("cls");
				ExibirMaterias(DescA);
			break;
			case 'H':
				system("cls");
				printf("## ALTERAR MATERIAS ##\n");
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
				gets(aux3);
				while(strcmp(BuscarNotas(Lista->DescM,aux3).Materia,aux3)!=0 || strcmp(aux3," ")==0 || aux3[0]=='\0'){
					printf("Digite o Nome da materia: ");
					fflush(stdin);
					gets(aux3);
				}
				RegM = BuscarNotas(Lista->DescM,aux3);
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
				gets(aux3);
				while(strcmp(BuscarNotas(Lista->DescM,aux3).Materia,aux3)!=0 || strcmp(aux," ")==0 || aux[0]=='\0'){
					printf("Digite o Nome da materia: ");
					fflush(stdin);
					gets(aux3);
				}

				ExcluirMateria(BuscarNotas(Lista->DescM,aux3).Materia,Lista->DescM);
			break;
		}
		
	}while(op!=27);

	guadarDados(DescA);
	return 0;
}