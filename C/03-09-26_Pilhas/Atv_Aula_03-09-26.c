#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct No {
    char *url;
    struct No *prox;
} No;

typedef struct {
    No *topo;
} PilhaURLs;

typedef struct {
    char *atual;
    PilhaURLs voltar;

    PilhaURLs avancar;
} Navegador;

char *duplicarString(const char *texto) {
    char *copia = malloc(strlen(texto) + 1);

    if (copia != NULL) {
        strcpy(copia, texto);
    }

    return copia;
}

void inicializarPilha(PilhaURLs *pilha) {
    pilha->topo = NULL;
}

bool pilhaVazia(const PilhaURLs *pilha) {
    return pilha->topo == NULL;
}

bool empilhar(PilhaURLs *pilha, char *url) {
    No *novo = malloc(sizeof(No));

    if (novo == NULL) {
        return false;
    }

    novo->url = url;
    novo->prox = pilha->topo;
    pilha->topo = novo;

    return true;
}

char *desempilhar(PilhaURLs *pilha) {
    if (pilhaVazia(pilha)) {
        return NULL;
    }

    No *removido = pilha->topo;
    char *url = removido->url;

    pilha->topo = removido->prox;
    free(removido);

    return url;
}

void limparPilha(PilhaURLs *pilha) {
    char *url;

    while ((url = desempilhar(pilha)) != NULL) {
        free(url);
    }
}

void inicializarNavegador(Navegador *navegador) {
    navegador->atual = NULL;
    inicializarPilha(&navegador->voltar);
    inicializarPilha(&navegador->avancar);
}

void visitar(Navegador *navegador, const char *url) {
    char *novaUrl = duplicarString(url);

    if (novaUrl == NULL) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    if (navegador->atual != NULL &&
        !empilhar(&navegador->voltar, navegador->atual)) {
        free(novaUrl);
        printf("Erro ao alocar memoria.\n");
        return;
    }

    navegador->atual = novaUrl;
    limparPilha(&navegador->avancar);

    printf("Visitando: %s\n", navegador->atual);
}

void voltar(Navegador *navegador) {
    if (pilhaVazia(&navegador->voltar)) {
        printf("Nao ha pagina anterior.\n");
        return;
    }

    if (!empilhar(&navegador->avancar, navegador->atual)) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    navegador->atual = desempilhar(&navegador->voltar);
    printf("Pagina atual: %s\n", navegador->atual);
}

void avancar(Navegador *navegador) {
    if (pilhaVazia(&navegador->avancar)) {
        printf("Nao ha pagina para avancar.\n");
        return;
    }

    if (!empilhar(&navegador->voltar, navegador->atual)) {
        printf("Erro ao alocar memoria.\n");
        return;
    }

    navegador->atual = desempilhar(&navegador->avancar);
    printf("Pagina atual: %s\n", navegador->atual);
}

void exibirAtual(const Navegador *navegador) {
    if (navegador->atual == NULL) {
        printf("Nenhuma pagina aberta.\n");
    } else {
        printf("Pagina atual: %s\n", navegador->atual);
    }
}

void liberarNavegador(Navegador *navegador) {
    free(navegador->atual);
    limparPilha(&navegador->voltar);
    limparPilha(&navegador->avancar);
}

int main(void) {
    Navegador navegador;
    int opcao;
    char url[256];

    inicializarNavegador(&navegador);

    do {
        printf("\n1 - Visitar\n");
        printf("2 - Voltar\n");
        printf("3 - Avancar\n");
        printf("4 - Exibir pagina atual\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        fflush(stdout);

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada invalida. Digite um numero.\n");
            while (getchar() != '\n') {
            }
            continue;
        }

        switch (opcao) {
            case 1:
                printf("URL: ");
                fflush(stdout);

                if (scanf("%255s", url) != 1) {
                    printf("URL invalida.\n");
                    break;
                }

                visitar(&navegador, url);
                break;
            case 2:
                voltar(&navegador);
                break;
            case 3:
                avancar(&navegador);
                break;
            case 4:
                exibirAtual(&navegador);
                break;
            case 0:
                break;
            default:
                printf("Opcao invalida.\n");
        }
    } while (opcao != 0);

    liberarNavegador(&navegador);
    return 0;
}