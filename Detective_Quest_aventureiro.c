#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ────────────────────────────────────────────────────────────
//  (1) Associar pista ao cômodo: campo extra na struct Sala
// ────────────────────────────────────────────────────────────

// Estrutura da sala (nó da árvore da mansão)
typedef struct Sala {
    char nome[40];
    char pista[80];      // (1) Campo extra para armazenar a pista do cômodo
    struct Sala *esq;
    struct Sala *dir;
} Sala;

// ────────────────────────────────────────────────────────────
//  BST das pistas (2)
// ────────────────────────────────────────────────────────────

// Nó da árvore BST das pistas coletadas
typedef struct PistaNode {
    char pista[80];
    struct PistaNode *esq;
    struct PistaNode *dir;
} PistaNode;


// ────────────────────────────────────────────────────────────
//  Função 1: criarSala()  (5 - modularização + comentário)
// ────────────────────────────────────────────────────────────


// (5) Cria dinamicamente uma sala com nome e pista (se houver)
Sala* criarSala(const char *nome, const char *pista) {
    Sala *s = (Sala*) malloc(sizeof(Sala));
    strcpy(s->nome, nome);
    strcpy(s->pista, pista);
    s->esq = NULL;
    s->dir = NULL;
    return s;
}

// ────────────────────────────────────────────────────────────
//  Função 2: inserirPista() — BST  (2 e 5)
// ────────────────────────────────────────────────────────────

// (2)(5) Insere uma pista na BST em ordem alfabética
PistaNode* inserirPista(PistaNode *raiz, const char *p) {
    if (raiz == NULL) {
        PistaNode *novo = (PistaNode*) malloc(sizeof(PistaNode));
        strcpy(novo->pista, p);
        novo->esq = novo->dir = NULL;
        return novo;
    }

    if (strcmp(p, raiz->pista) < 0)
        raiz->esq = inserirPista(raiz->esq, p);
    else if (strcmp(p, raiz->pista) > 0)
        raiz->dir = inserirPista(raiz->dir, p);

    return raiz; // pistas iguais são ignoradas
}

// ────────────────────────────────────────────────────────────
//  Função 3: exibirPistas() — in-order  (4 e 5)
// ────────────────────────────────────────────────────────────

// (4)(5) Exibe pistas organizadas alfabeticamente usando percurso in-order
void exibirPistas(PistaNode *r) {
    if (r == NULL) return;
    exibirPistas(r->esq);
    printf("🔎 %s\n", r->pista);
    exibirPistas(r->dir);
}

// ────────────────────────────────────────────────────────────
//  Função 4: explorarSalasComPistas()  (3, 5, 7)
// ────────────────────────────────────────────────────────────

// (3)(5)(7) Explora a mansão, exibindo nome do cômodo, pista e caminhos.
//           Sempre que entrar em uma sala com pista, ela é automaticamente
//           inserida na BST. O mapa não muda, mas as pistas coletadas variam
//           conforme o caminho escolhido.
void explorarSalasComPistas(Sala *s, PistaNode **arvorePistas) {
    char op;

    while (s != NULL) {
        printf("\n📍 Sala atual: %s\n", s->nome);

        // (3) Mostrar pista do cômodo, se existir
        if (strlen(s->pista) > 0) {
            printf("✨ Pista encontrada: %s\n", s->pista);

            // (2) Inserir automaticamente a pista na BST
            *arvorePistas = inserirPista(*arvorePistas, s->pista);
        }

        // Sala sem saídas
        if (!s->esq && !s->dir) {
            printf("🏁 Esta sala é um fim de caminho!\n");
            return;
        }

        // (3) Exibir opções de caminho
        printf("\nEscolha:\n");
        if (s->esq) printf("  (e) → %s\n", s->esq->nome);
        if (s->dir) printf("  (d) → %s\n", s->dir->nome);
        printf("  (s) → Sair da exploração\n");
        printf("Opção: ");

        scanf(" %c", &op);

        if (op == 'e' && s->esq) s = s->esq;
        else if (op == 'd' && s->dir) s = s->dir;
        else if (op == 's') return;
        else printf("Opção inválida!\n");
    }
}

// ────────────────────────────────────────────────────────────
//  MAIN — mapa fixo (7)
// ────────────────────────────────────────────────────────────

int main() {

    // (7) O mapa não muda, é fixo
    Sala *hall = criarSala("Hall de Entrada", "Pegadas de lama");

    hall->esq = criarSala("Sala de Estar", "");
    hall->dir = criarSala("Corredor Principal", "Cheiro estranho no ar");

    hall->esq->esq = criarSala("Biblioteca", "Livro antigo fora do lugar");
    hall->esq->dir = criarSala("Sala de Jantar", "");

    hall->dir->esq = criarSala("Escadaria", "Degrau quebrado");
    hall->dir->dir = criarSala("Jardim Interno", "Flor arrancada recentemente");

    // Árvore de pistas começa vazia
    PistaNode *pistas = NULL;

    // Inicia a exploração
    explorarSalasComPistas(hall, &pistas);

    // (4) Exibir pistas coletadas ao sair
    printf("\n\n=========================\n");
    printf("     PISTAS COLETADAS\n");
    printf("=========================\n");

    if (pistas == NULL)
        printf("Nenhuma pista encontrada.\n");
    else
        exibirPistas(pistas);

    printf("\nPressione ENTER para sair...");
    getchar(); getchar();

    return 0;
}
