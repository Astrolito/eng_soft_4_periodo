#include <stdio.h>
#include <stdbool.h>
#define tamanho 5

struct Lista{
    int dados[tamanho];
    int inicio, fim;
};

struct Lista lista;

void inicializacao(){
    lista.inicio = 0;
    lista.fim = -1;
}

bool listaCheia(){
    return (lista.fim == tamanho - 1);
}

bool listaVazia(){
    return (lista.fim == -1);
}

void inserirFim(int valor){
    if(listaCheia()){
        printf("Lista cheia!\n");
    } else {
        lista.fim++;
        lista.dados[lista.fim] = valor;
    }
}

void inserirMeio(int valor, int posicao){
    if(listaCheia()){
        printf("Lista cheia!\n");
    } else {
        if(lista.fim >= posicao){
            int auxPosicao = lista.fim;
            do{
                lista.dados[auxPosicao + 1] = lista.dados[auxPosicao];
            }while(--auxPosicao >= posicao); //decremento antres de verificar a condição quando --auxPosicao > posicao se auxPosicao-- for igual a posicao, o loop termina e não é feito o deslocamento do elemento da posição posicao
            lista.dados[posicao] = valor;
            lista.fim++;
            printf("Valor %d inserido na posição %d da lista.\n", valor, posicao);
        }else{
            inserirFim(valor);
        }
    }   
}

void imprimirLista(){
    if(listaVazia()){
        printf("Lista vazia!\n");
    } else {
        int auxPosicao = lista.inicio;
        printf("Lista: ");
        do{
            printf("%d ", lista.dados[auxPosicao]);
        }while(++auxPosicao <= lista.fim);
    }
}

void inserirInicio(int valor){
    if(listaCheia()){
        printf("Lista cheia!\n");
    } else {
        int auxPosicao = lista.fim;
        while(auxPosicao >= 0){
            lista.dados[auxPosicao + 1] = lista.dados[auxPosicao];
            auxPosicao--;
        }
        lista.dados[0] = valor;
        lista.fim++;
        printf("Valor %d inserido na posição 0 da lista.\n", valor);
    }
}


void removerFim(){
    if(listaVazia()){
        printf("Lista vazia!\n");
    } else {
        lista.fim--;
    }
}

void removerMeio(){
    if(listaVazia()){
        printf("Lista vazia!\n");
    } else {
        int posicao;
        printf("Digite a posição do elemento a ser removido: ");
        scanf("%d", &posicao);
        if(posicao < 0 || posicao > lista.fim){
            printf("Posição inválida!\n");
        } else {
            int auxPosicao = posicao;
            while(auxPosicao < lista.fim){
                lista.dados[auxPosicao] = lista.dados[auxPosicao + 1];
                auxPosicao++;
            }
            lista.fim--;
            printf("Elemento da posição %d removido da lista.\n", posicao);
        }
    }
}
int main(){
    inicializacao();
    imprimirLista();
    printf("\n");
    inserirFim(1);
    imprimirLista();
    printf("\n");
    inserirFim(2);
    inserirFim(3);
    imprimirLista();
    printf("\n");
    inserirMeio(10, 1);
    imprimirLista();
    printf("\n");
    inserirInicio(0);
    imprimirLista();
    printf("\n");
    removerFim();
    imprimirLista();
    printf("\n");
    removerMeio();
    imprimirLista();
    printf("\n");
    return 0;
}
   