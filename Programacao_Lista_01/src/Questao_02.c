/*
 ============================================================================
 Nome        : Programacao_Lista_01_12-08-2008/Questao_02.c
 Equipe      : Rafael de Castro, Lucas Assuncao
 ============================================================================
 */

#include <stdio.h>

int main(void) {
	float nota_avaliacao, nota_media_exercicios, media_aproveitamento = 0;

	//Le as notas das 3 avaliacoes e ja armazena em media_aproveitamento
	int i;
	for (i = 1; i <= 3; i++) {
		printf("Digite a nota da avaliacao No. %d: ", i);
		scanf("%f", &nota_avaliacao);
		media_aproveitamento += 2 * nota_avaliacao;
	}

	//Le a nota da media dos exercicios e ja armazena em media_aproveitamento
	printf("Digite a nota da media dos exercicios: ");
	scanf("%f", &nota_media_exercicios);
	media_aproveitamento += nota_media_exercicios;

	//Calcula a media de aproveitamento:
	media_aproveitamento = media_aproveitamento / 7;

	//Exibe o resultado:
	if (media_aproveitamento >= 7) {
		printf("Situacao do aluno: Aprovado");
	} else {
		printf("Situacao do aluno: Reprovado");
	}

	printf("\n\nPressione ENTER para sair");
	getchar();
	getchar();
	return 0;
}
