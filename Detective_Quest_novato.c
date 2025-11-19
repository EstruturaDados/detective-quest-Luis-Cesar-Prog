#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Sala {
    char nome[40];
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// Cria um nó da árvore (sala)
Sala* criarSala(const char *nome) {
    Sala *s = (Sala*) malloc(sizeof(Sala));
    strcpy(s->nome, nome);
    s->esq = NULL;
    s->dir = NULL;
    return s;
}

// Exploração simples da árvore
void explorarSalas(Sala *s) {
    char op;

    while (s != NULL) {
        printf("\n📍 Sala atual: %s\n", s->nome);

        // Sala final
        if (!s->esq && !s->dir) {
            printf("🏁 Esta sala é um fim de caminho!\n");
            return;
        }

        printf("Escolha:\n");
        if (s->esq) printf("  (e) → %s\n", s->esq->nome);
        if (s->dir) printf("  (d) → %s\n", s->dir->nome);
        printf("  (s) → Sair\n");
        printf("Opção: ");

        scanf(" %c", &op);

        if (op == 'e' && s->esq) s = s->esq;
        else if (op == 'd' && s->dir) s = s->dir;
        else if (op == 's') return;
        else printf("Opção inválida!\n");
    }
}

int main() {

    // Criando árvore fixa da mansão
    Sala *hall = criarSala("Hall de Entrada");
    hall->esq = criarSala("Sala de Estar");
    hall->dir = criarSala("Corredor Principal");

    hall->esq->esq = criarSala("Biblioteca");
    hall->esq->dir = criarSala("Sala de Jantar");

    hall->dir->esq = criarSala("Escadaria");
    hall->dir->dir = criarSala("Jardim Interno");

    // Começa o jogo
    explorarSalas(hall);

    // Pausa antes de fechar
    printf("\nPressione ENTER para sair...");
    getchar(); // consome \n pendente
    getchar(); // espera ENTER real

    return 0;
}