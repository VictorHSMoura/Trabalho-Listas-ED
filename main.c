#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "lista.h"

typedef struct {
	char Nome[30];
	int Vagas;
	float Corte;
	TipoLista Alunos;
} Curso;

void LeDados(TipoLista *LGeral, Curso **Cursos, int nCursos, int nAlunos) {
	Curso *Cr;
	TipoItem I;
	Apontador P;
	char c;
  
    Cr = (Curso *) malloc(nCursos * sizeof(Curso));
    for(int i = 0; i < nCursos; i++) {
        //__fpurge(stdin);	//limpeza de buffer (para Linux)
        while((c = getchar()) != EOF && c != '\n')
        	continue;
        fgets(Cr[i].Nome, 30, stdin);
        Cr[i].Nome[strlen(Cr[i].Nome) - 1] = '\0';  //tira \n do fim
        scanf("%d", &Cr[i].Vagas);
        Cr[i].Corte = 0;
        FLVazia(&Cr[i].Alunos);
    }
 
    FLVazia(LGeral);
    for(int i = 0; i < nAlunos; i++) {
        while((c = getchar()) != EOF && c != '\n')
        	continue;
        fgets(I.Nome, 30, stdin);
        I.Nome[strlen(I.Nome) - 1] = '\0';  //tira \n do fim
        scanf("%f %d %d", &I.Nota, &I.Opcao1, &I.Opcao2);
        //Inserção usando versão alterada do Insertion Sort
        P = BuscaMenor(I, LGeral);
        Insere(I, LGeral, P);
    }
    *Cursos = Cr;
}

void Distribui(TipoLista *LGeral, Curso *Cursos) {
	Apontador q;
	int curso1, curso2;	

	if(!Vazia(LGeral)) {
		for(q = LGeral->Primeiro->Prox; q != NULL; q = q->Prox) {
			curso1 = q->Aluno.Opcao1;
			
			if(Vazia(&Cursos[curso1].Alunos) && Cursos[curso1].Vagas > 0) {
				//Se não tem ninguém no curso, insere direto
				Insere(q->Aluno, &Cursos[curso1].Alunos, Cursos[curso1].Alunos.Ultimo);
			} else if(!Vazia(&Cursos[curso1].Alunos)) {
				Apontador aux;

				if(Cursos[curso1].Alunos.Ultimo->Aluno.Nota > q->Aluno.Nota ||
					Cursos[curso1].Alunos.Ultimo->Aluno.Opcao1 == curso1) {
					aux = Cursos[curso1].Alunos.Ultimo;	//Insere no fim caso a ultima nota for maior
				} else {
					aux = BuscaIgual(q->Aluno, &Cursos[curso1].Alunos, curso1);	//Desempate de notas
				}
				Insere(q->Aluno, &Cursos[curso1].Alunos, aux);
				
				if(Cursos[curso1].Alunos.Tamanho > Cursos[curso1].Vagas) {
					if((aux->Prox == Cursos[curso1].Alunos.Ultimo) ||
					(BuscaPosicao(aux->Prox, &Cursos[curso1].Alunos) >= Cursos[curso1].Vagas)) {
						curso2 = q->Aluno.Opcao2;
						//Insere no segundo curso caso não tenha mais vagas no primeiro
						Insere(q->Aluno, &Cursos[curso2].Alunos, Cursos[curso2].Alunos.Ultimo);
						if(Cursos[curso2].Alunos.Tamanho == Cursos[curso2].Vagas)
							//Seta nota de corte curso2
							Cursos[curso2].Corte = Cursos[curso2].Alunos.Ultimo->Aluno.Nota;
					}
				}
			}
			if(Cursos[curso1].Alunos.Tamanho == Cursos[curso1].Vagas)
				//Seta nota de corte curso1
				Cursos[curso1].Corte = Cursos[curso1].Alunos.Ultimo->Aluno.Nota;
		}
	}
}

void ImprimeClassificacao(Curso *Cursos, int nCursos){
	int i;
	for(i = 0; i < nCursos; i++){
		printf("%s %.2f\n", Cursos[i].Nome, Cursos[i].Corte);
		printf("Classificados\n");
		Imprime(&Cursos[i].Alunos, Cursos[i].Vagas);
		printf("\n");
	}
}

int main() {
	int nCursos, nAlunos;
	TipoLista LGeral;
	Curso *Cursos;

	scanf("%d %d", &nCursos, &nAlunos);
    LeDados(&LGeral, &Cursos, nCursos, nAlunos);
	Distribui(&LGeral, Cursos);
	ImprimeClassificacao(Cursos, nCursos);
	
	Libera(&LGeral);
	for(int i = 0; i < nCursos; i++) {
		Libera(&Cursos[i].Alunos);
	}
	free(Cursos);
	return 0;
}
