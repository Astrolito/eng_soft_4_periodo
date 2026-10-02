#include <stdio.h>
#include <stdbool.h>
#define TAMANHO 5

typedef struct Fila{
	char dados[TAMANHO];
	int inicio, fim;
}Fila;

void inicializar(struct Fila *fila){
	fila->inicio = 0;
	fila->fim = -1;
}

bool estaVazia(struct Fila *fila){
	return fila->fim == -1;
}

bool estaCheia(struct Fila *fila){
	return fila->fim == TAMANHO - 1;
}

void enfileira(struct Fila *fila, char valor){
	if(estaCheia(fila)){
		printf("Fila esta cheia!\n");
	}else{
		fila->fim++;
		fila->dados[fila->fim] = valor;
		printf("Inserirdo com sucesso!\n");
	}
}

void desenfileira(struct Fila *fila){
	if(estaVazia(fila)){
		printf("Fila esta vazia!\n");
	}else{
		char remocao = fila->dados[fila->inicio];
		int aux = fila->inicio;
		while(aux < fila->fim){
			fila->dados[aux] = fila->dados[aux+1];
			aux++;
		}
		fila->fim--;
		printf("Elemento removido: %c\n", remocao);
	}
}

void exibir(struct Fila *fila){
    if(estaVazia(fila)){
        printf("Fila esta vazia!\n");
    }else{
        printf("Fila: ");
        for(int i = fila->inicio; i <= fila->fim; i++){
            printf("%c ", fila->dados[i]);
        }
        printf("\n");
    }
}




int main(){
	struct Fila fila;
	inicializar(&fila);
    exibir(&fila);
	return 0;
}