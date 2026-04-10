#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LIMITE 300.0

typedef struct Pasta {
    char nome[50];
    float tamanho;
    struct Pasta *subpastas[10];
    int qtd_sub;
} Pasta;

// Função para criar pasta
Pasta* criarPasta(char nome[], float tamanho) {
    Pasta* p = (Pasta*) malloc(sizeof(Pasta));
    strcpy(p->nome, nome);
    p->tamanho = tamanho;
    p->qtd_sub = 0;
    return p;
}

// Adicionar subpasta
void adicionarSubpasta(Pasta *pai, Pasta *filha) {
    pai->subpastas[pai->qtd_sub++] = filha;
}

// Função recursiva
float mapearEstrutura(Pasta *p, int nivel, int limiteNivel) {
    if (p == NULL || nivel > limiteNivel) return 0;

    float soma = p->tamanho;

    // Indentação visual
    for (int i = 0; i < nivel; i++) printf("  ");

    printf("- %s (%.2f GB)\n", p->nome, p->tamanho);

    for (int i = 0; i < p->qtd_sub; i++) {
        soma += mapearEstrutura(p->subpastas[i], nivel + 1, limiteNivel);
    }

    // Alerta
    if (soma > LIMITE) {
        for (int i = 0; i < nivel; i++) printf("  ");
        printf("ALERTA: %s excede %.2f GB (Total: %.2f GB)\n", p->nome, LIMITE, soma);
    }

    return soma;
}

int main() {
    // Criando estrutura exemplo
    Pasta *raiz = criarPasta("Raiz", 50);
    Pasta *eng = criarPasta("Engenharia", 100);
    Pasta *proj = criarPasta("Projetos", 200);
    Pasta *docs = criarPasta("Documentos", 80);

    adicionarSubpasta(raiz, eng);
    adicionarSubpasta(raiz, docs);
    adicionarSubpasta(eng, proj);

    int limiteNivel = 10;

    printf("Mapeamento de Estrutura:\n");
    mapearEstrutura(raiz, 0, limiteNivel);

    return 0;
}
