typedef struct {
	float Nota;
	char Nome[30];
	int Opcao1, Opcao2;
} TipoItem;

typedef struct Celula_str *Apontador;

typedef struct Celula_str {
	TipoItem Aluno;
	Apontador Prox;
} Celula;

typedef struct {
	Apontador Primeiro, Ultimo;
	int Tamanho;	
} TipoLista;

void FLVazia(TipoLista *Lista);

int Vazia(const TipoLista *Lista);

void Insere(TipoItem x, TipoLista *Lista, Apontador E);

void Retira(Apontador p, TipoLista *Lista, TipoItem *Aluno);

Apontador BuscaMenor(TipoItem x, TipoLista *Lista);

Apontador BuscaIgual(TipoItem x, TipoLista *Lista, int Op);

int BuscaPosicao(Apontador E, TipoLista *Lista);

void Imprime(const TipoLista *Lista, int Div);

void Libera(TipoLista *Lista);