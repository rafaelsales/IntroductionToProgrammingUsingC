/*
 * Calculo do Indice de Rendimento Academico da Universidade Federal do Ceara
 * por Arthur de Castro Callado
 *
 */

#include <stdio.h>
#include <stdlib.h>
//#include <conio.h>

/* Funcoes necessarias */
float calculo(int *creditos, int *semestres, float *notas, int discip, int tranc)
{
	int i;
	float parcial1=0.0, parcial2=0.0;
	for(i=0;i<discip;i++)
	{
		parcial1+=notas[i]*creditos[i]*(6<semestres[i]?6:semestres[i]);
		parcial2+=creditos[i]*(6<semestres[i]?6:semestres[i]);
	}
	return((1.0-((0.5*tranc)/(discip+tranc)))*(parcial1/parcial2));
}

void entra(int *creditos, int *semestres, float *notas, int discip, int tranc, FILE *entrada)
{
	int i;
	printf("\n%i Disciplina(s) cursada(s)\n%i Disciplina(s) Trancada(s)\nTotal: %i Disciplina(s).", discip, tranc, discip+tranc);
	printf("\nOBS: Reprovacao por falta implica media zero.\n");
	printf("\nEntre os dados das disciplinas cursadas:\n");
	for(i=0;i<discip;i++)
	{
		printf("Digite a media da disciplina %i: ", i+1);
		fscanf(entrada, "%f", &notas[i]);
		printf("Digite o numero de creditos da mesma: ");
		fscanf(entrada, "%i", &creditos[i]);
		printf("Digite o semestre em que a mesma foi cursada: ");
		fscanf(entrada, "%i", &semestres[i]);
	}
}

void gera(int *creditos, int *semestres, float *notas, char *nome1, char *nome2, int discip, int tranc, FILE *saida)
{
	int i;
	fprintf(saida, "%s %s\n", nome1, nome2);
	fprintf(saida, "%i\n%i\n", discip, tranc);
	for(i=0;i<discip;i++)
	{
		fprintf(saida, "%.1f\n%i\n%i\n", notas[i], creditos[i], semestres[i]);
	}
}

void sai(int *creditos, int *semestres, float *notas, int discip, int tranc, FILE *saida)
{
	int i;
	fprintf(saida, "\n\r%i Disciplina(s) Cursada(s)\n\r%i Disciplina(s) Trancada(s)\n\rTotal: %i Disciplina(s)\n\r\n", discip, tranc, discip+tranc);
	fprintf(saida, "                Media  Creditos  Semestre\n\r");
	for(i=0;i<discip;i++)
	{
		fprintf(saida, "Disciplina %3i: %4.1f     %3i       %3i\n\r", i+1, notas[i], creditos[i], semestres[i]);
	}
	fprintf(saida, "\nIRA: %f\n\r", calculo(creditos, semestres, notas, discip, tranc));
}

/* Programa Principal */
int main(int argc, char **argv) {
	char a_nom[12], nome1[20], nome2[20];
	int discip, tranc, *semestres, *creditos, princ, dados=0;
	float *notas, ira;
	FILE *entrada, *saida;
	do
	{
		printf("\nPrograma para calcular o IRA\n");
		printf("Por Arthur de Castro Callado\n\n");
		printf("1 - Entrada de dados interativa\n");
		printf("2 - Entrada de dados por arquivo\n");
		printf("3 - Gerar arquivo de entrada com dados digitados\n");
		printf("4 - Gerar relatorio em arquivo\n");
		printf("5 - Imprimir relatorio\n");
		printf("6 - Calcular o IRA\n");
		printf("0 - Sair\n");
		scanf("%i", &princ);
		switch(princ)
		{
		case 1:
		{
			if(dados==1)
			{
				free(notas);
				free(semestres);
				free(creditos);
				dados=0;
			}
			printf("Digite seu nome (Primeiro e ultimo): ");
			scanf("%s %s", nome1, nome2);
			printf("\nDigite o numero total de disciplinas cursadas (incluindo repeticoes): ");
			scanf("%i", &discip);
			printf("Digite o numero total de trancamentos: ");
			scanf("%i", &tranc);
			/* Alocacao dinamica */
			if(!(notas=(float *)calloc(discip, sizeof(float)))||
				!(semestres=(int *)calloc(discip, sizeof(int)))||
				!(creditos=(int *)calloc(discip, sizeof(int))))
			{
				printf("\nMemoria insuficiente!");
			}
			else
			{
				entra(creditos, semestres, notas, discip, tranc, stdin);
				dados = 1;
			}
			break;
		}
		case 2:
		{
			if(dados==1)
			{
				free(notas);
				free(semestres);
				free(creditos);
				dados=0;
			}
			printf("\nDigite o nome do arquivo de entrada: ");
			scanf("%s", &a_nom);
			/* Abre o arquivo para leitura */
			if ((entrada = fopen(a_nom, "rt")) == NULL)
			{
				printf("\nArquivo nao encontrado!");
			}
			fscanf(entrada, "%s %s", nome1, nome2);
			fscanf(entrada, "%i", &discip);
			fscanf(entrada, "%i", &tranc);
			/* Alocacao dinamica */
			if(!(notas=(float *)calloc(discip, sizeof(float)))||
				!(semestres=(int *)calloc(discip, sizeof(int)))||
				!(creditos=(int *)calloc(discip, sizeof(int))))
			{
				printf("\nMemoria insuficiente!");
			}
			else
			{
				entra(creditos, semestres, notas, discip, tranc, entrada);
				dados = 1;
			}
			/* Fechando o arquivo */
			fclose(entrada);
			break;
		}
		case 3:
		{
			if(dados==1)
			{
				printf("\nDigite o nome do arquivo de saida: ");
				scanf("%s", &a_nom);
				/* Abre o arquivo para gravacao */
				if ((saida = fopen(a_nom, "wt")) == NULL)
				{
					printf("\nErro ao criar arquivo!");
				}
				else
				{
					gera(creditos, semestres, notas, nome1, nome2, discip, tranc, saida);
				}
				/* Fechando o arquivo */
				fclose(saida);
			}
			break;
		}
		case 4:
		{
			if(dados==1)
			{
				printf("\nDigite o nome do arquivo de saida: ");
				scanf("%s", &a_nom);
				/* Abre o arquivo para gravacao */
				if ((saida = fopen(a_nom, "wt")) == NULL)
				{
					printf("\nErro ao criar arquivo!");
				}
				else
				{
					sai(creditos, semestres, notas, discip, tranc, saida);
				}
				/* Fechando o arquivo */
				fclose(saida);
			}
			break;
		}
		case 5:
		{
			if(dados==1)
			{
//				sai(creditos, semestres, notas, discip, tranc, stdprn);
			}
			break;
		}
		case 6:
		{
			if(dados==1)
			{
				ira=calculo(creditos, semestres, notas, discip, tranc);
				/* Imprimindo Resultado */
				printf("\nSeu IRA e': %f\n", ira);
			}
			break;
		}
		}
	}
	while(princ!=0);
	/* Desalocando a Memoria */
	if(dados==1)
	{
		free(notas);
		free(semestres);
		free(creditos);
	} return 0;
}


