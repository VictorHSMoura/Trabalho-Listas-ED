#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

void FLVazia(TipoLista *Lista) {
	Lista->Primeiro = (Apontador) malloc(sizeof(Celula));
	Lista->Ultimo = Lista->Primeiro;
	Lista->Primeiro->Prox = NULL;
	Lista->Tamanho = 0;
}

int Vazia(const TipoLista *Lista) {
	return (Lista->Primeiro == Lista->Ultimo);
}

void Insere(TipoItem x, TipoLista *Lista, Apontador E) {
	Apontador novo;
	novo = (Apontador) malloc(sizeof(Celula));
	novo->Aluno = x;
	novo->Prox = E->Prox;
	E->Prox = novo;
	if(E == Lista->Ultimo)
		Lista->Ultimo = novo;
	Lista->Tamanho++;
}

void Retira(Apontador p, TipoLista *Lista, TipoItem *Aluno) {
	Apontador q;

	if(Vazia(Lista) || p == NULL || p->Prox == NULL) {
		printf("Erro Lista vazia ou posição não existe\n");
		return;
	}

	q = p->Prox;
	*Aluno = q->Aluno;
	p->Prox = q->Prox;
	if(p->Prox == NULL)
		Lista->Ultimo = p;
	free(q);
	Lista->Tamanho--;
}

Apontador BuscaMenor(TipoItem x, TipoLista *Lista) {
	Apontador q;

	if(Vazia(Lista))
		return Lista->Primeiro;

	q = Lista->Primeiro;
	while(q != Lista->Ultimo && q->Prox->Aluno.Nota >= x.Nota)
		q = q->Prox;
	return q;
}

//Busca primeiro aluno com mesma nota, mas com prioridade de curso diferente
Apontador BuscaIgual(TipoItem x, TipoLista *Lista, int Op) {
	Apontador q;

	if(Vazia(Lista))
		return Lista->Primeiro;

	q = Lista->Primeiro;
	while(q != Lista->Ultimo){
		if(q->Prox->Aluno.Nota == x.Nota && q->Prox->Aluno.Opcao1 != Op)
			break;
		q = q->Prox;
	}
	return q;
}

int BuscaPosicao(Apontador E, TipoLista *Lista) {
	Apontador q;
	int i = 0;

	if(Vazia(Lista))
		return -1;

	q = Lista->Primeiro->Prox;
	while(q != NULL && q != E) {
		q = q->Prox;
		i++;
	}
	if(q == NULL)
		return -1;
	return i;
}

void Imprime(const TipoLista *Lista, int Div) {
	Apontador Aux;
	int i = 0;
	for(Aux = Lista->Primeiro->Prox; Aux != NULL; Aux = Aux->Prox, i++) {
		if(Div == i)
			printf("Lista de espera\n");

		printf("%s %.2f\n", Aux->Aluno.Nome, Aux->Aluno.Nota);
	}
	if(i <= Div)
		printf("Lista de espera\n");	//Imprime caso não tenham alunos suficientes na disciplina
}

void Libera(TipoLista *Lista) {
	Apontador aux;

	//Libera todos os itens até que reste apenas a célula cabeça
	while(!Vazia(Lista)) {
		aux = Lista->Primeiro;
		Lista->Primeiro = Lista->Primeiro->Prox;
		free(aux);
	}
	free(Lista->Primeiro);	//Libera célula cabeça
}
