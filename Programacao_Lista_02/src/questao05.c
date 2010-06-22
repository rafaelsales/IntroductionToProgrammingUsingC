/*
 ============================================================================
 Arquivo     : Programação - Lista 02 - Questao 05
 Equipe      : Lucas Assunção e Rafael Sales
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

// Criacao de tipo para implementacao da lista
struct lista {
	char info;
	struct lista* prox;
};
typedef struct lista Lista;

// Declaracao das rotinas usadas para implementar lista

Lista* criaLista();
void insereLetra(Lista* inicio, char letra);
void removeLetra(Lista* inicio);

// Declaracao das rotinas que calculam tamanho de uma string (numero de caracteres validos)
int tamanho(Lista* inicio);
int tamanho_str(char* str);

// Declaracao das rotinas das operacoes pedidas na questao
Lista* strconvertlist(char* str);
void listconvertstr(Lista* l1, char* str);
Lista* substr(Lista* inicio, int i1, int i2);
int strcomp(Lista* l1, Lista* l2);
Lista* strconcat(Lista* l1, Lista* l2);
Lista* strinvert(Lista* l1);

// Cria lista encadeada
Lista* criaLista() {
	Lista* inicio = (Lista *) malloc(sizeof(Lista));
	inicio->prox = NULL;
	return inicio;
}

// Insere caractere em lista (no inicio)
void insereLetra(Lista* inicio, char letra) {
	Lista* novo = (Lista *) malloc(sizeof(Lista));
	if (novo != NULL) {
		novo->info = letra;
		novo->prox = inicio->prox;
		inicio->prox = novo;
	} else
		printf("Memoria insuficiente");
}

// Remove caractere de lista (do inicio)
void removeLetra(Lista* inicio) {
	Lista* aRemover;
	if (inicio->prox == NULL)
		printf("Nao ha letras a serem removidas\n");
	else {
		aRemover = inicio->prox;
		inicio->prox = aRemover->prox;
		free(aRemover);
	}
}

// Calcula numero de caracteres validos numa lista encadeada
int tamanho(Lista* inicio) {
	int tam = 0;
	Lista* percorre = inicio;
	while (percorre->prox != NULL) {
		percorre = percorre->prox;
		tam++;
	}
	return tam;
}

// Calcula numero de caracteres validos numa string
int tamanho_str(char* str) {
	int tam = 0, i = 0;
	while (str[i] != '\0') {
		i++;
		tam++;
	}
	return tam;
}

// Converte uma string para uma lista de caracteres
Lista* strconvertlist(char* str) {
	int i = 0;
	Lista* inicio = criaLista();
	for (i = tamanho_str(str) - 1; i >= 0; i--) { //do fim para o inicio, pois cada insercao na lista ocorre pelo inicio
		insereLetra(inicio, str[i]);
	}
	return inicio;
}

// Converte uma lista de caracteres para uma string
void listconvertstr(Lista* l1, char* str) {
	int i;
	int tam = tamanho(l1);
	Lista* percorre = l1->prox;
	if (l1->prox != NULL) {
		for (i = 0; i < tam; i++) {
			str[i] = percorre->info;
			percorre = percorre->prox;
		}
		str[tam] = '\0'; //fim da string(certificar-se de mandar str vazia, para nao haver conflito entre dois '\0')
	}
}

// retorna uma "substring" obtida a partir de uma lista de caracteres
// caso seja impossivel criar a "substring" desejada, retorna NULL
Lista* substr(Lista* inicio, int i1, int i2) {
	int i;
	Lista* inicio_substr = criaLista(), * percorre = inicio->prox;
	int tam1 = tamanho(inicio);
	if (i1 + i2 <= tam1) {
		for (i = 1; i <= i2; i++) {
			insereLetra(inicio_substr, percorre->info);
			percorre = percorre->prox;
		}
		return inicio_substr;
	} else {
		printf("Impossivel criar substring desse tamanho");
		return NULL;
	}
}

// Compara duas listas de caracteres, retornando 0, caso iguais, ou 1, caso diferentes
int strcomp(Lista* l1, Lista* l2) {
	Lista* percorre_l1 = l1->prox;
	Lista* percorre_l2 = l2->prox;
	while ((percorre_l1->info == percorre_l2->info) &&
			(l1->prox != NULL) && (l2->prox != NULL)) {
		l1 = l1->prox;
		l2 = l2->prox;
	}
	if (percorre_l1->info == percorre_l2->info)
		return 0;
	else
		return 1;
}

// Retorna um ponteiro para o inicio da lista resultante da concatenacao das listas recebidas
Lista* strconcat(Lista* l1, Lista* l2) {
	int i, j;
	Lista *l3 = criaLista(), *l4 = criaLista(), *percorre = l1->prox;
	for (i = 1; i <= tamanho(l1); i++) {
		insereLetra(l3, percorre->info);
		percorre = percorre->prox;
	}
	percorre = l2->prox;
	for (j = 1; j <= tamanho(l2); j++) {
		insereLetra(l3, percorre->info);
		percorre = percorre->prox;
	}
	percorre = l3->prox;
	//para corrigir a ordem de insercao na lista
	for (i = 1; i <= tamanho(l3); i++) {
		insereLetra(l4, percorre->info);
		percorre = percorre->prox;
	}
	return l4;
}

// Retorna a o ponteiro para o inicio da lista inversa a recebida
Lista* strinvert(Lista* l1) {
	int i;
	Lista* l2 = criaLista(), *percorre = l1->prox;
	for (i = 1; i <= tamanho(l1); i++) {
		insereLetra(l2, percorre->info);
		percorre = percorre->prox;
	}
	return l2;
}

// main com operacoes uteis para testar funcionamento das rotinas implementadas
int main(void) {
	Lista* l1 = criaLista(), * l2 = criaLista(), * x;
	char* str = (char*) calloc(20, sizeof(char));
	int resultado;
	insereLetra(l1, 's'); // insere sempre no inicio da lista
	insereLetra(l1, 'a');
	insereLetra(l2, 'c');
	insereLetra(l2, 'u');
	insereLetra(l2, 'l');
	//concatena
	x = strconcat(l2, l1);
	// converte para string
	listconvertstr(x, str);
	//imprime string
	printf("Normal: %s\n", str);
	//inverte lista
	x=strconvertlist(str);
	x = strinvert(x);
	//converte para string
	listconvertstr(x, str);
	//imprime string
	printf("Invertida: %s\n", str);
	//compara x com sua inversa
	resultado=strcomp(x,strinvert(x));
	//imprime resultado
	if(resultado==0) printf(" -> Iguais\n");
	else printf(" -> Diferentes\n");
	getchar();
	getchar();
	return 0;
}
