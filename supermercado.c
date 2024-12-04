#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define SIZE 64  // O tabuleiro 8x8 tem 64 nós
#define INF INT_MAX  // Representa uma distância infinita para inicialização

const char *products[SIZE] = {
    "Cenoura", "Pão", "Leite", "Queijo", "Tomate", "Batata", "Carne", "Frango",
    "Maçã", "Banana", "Uva", "Melancia", "Laranja", "Abacaxi", "Manga", "Limão",
    "Arroz", "Feijão", "Macarrão", "Farinha", "Açúcar", "Sal", "Óleo", "Vinagre",
    "Água", "Refrigerante", "Suco", "Café", "Chá", "Biscoito", "Bolacha", "Chocolate",
    "Iogurte", "Sorvete", "Pipoca", "Amendoim", "Cereal", "Aveia", "Mel", "Granola",
    "Sabão", "Detergente", "Esponja", "Álcool", "Desinfetante", "Shampoo", "Condicionador", "Sabonete",
    "Toalha", "Guardanapo", "Papel Toalha", "Papel Higiênico", "Saco de Lixo", "Alumínio", "Plástico", "Fósforo",
    "Vela", "Lâmpada", "Pilha", "Bateria", "Fita Adesiva", "Cola", "Tesoura", "Caneta"
};

// Função para encontrar o índice do nó com a menor distância que ainda não foi visitado
int minDistance(int dist[], int visited[]) {
    int min = INF;         // Inicializa a menor distância como infinita
    int min_index = -1;    // Índice do nó com a menor distância

    // Percorre todos os nós
    for (int v = 0; v < SIZE; v++) {
        // Se o nó não foi visitado e sua distância é menor que a mínima atual
        if (!visited[v] && dist[v] <= min) {
            min = dist[v];      // Atualiza a menor distância
            min_index = v;      // Atualiza o índice do nó correspondente
        }
    }
    return min_index;  // Retorna o índice do nó com a menor distância
}

/*
 * Função para calcular o menor caminho de um grafo usando o algoritmo de Dijkstra.
 * Parâmetros:
 *  - graph: Matriz de adjacência representando o grafo
 *  - src: Índice do nó de origem
 *  - dest: Índice do nó de destino
 *  - path: Array para armazenar o caminho encontrado
 *  - path_size: Ponteiro para armazenar o tamanho do caminho
 */
void dijkstra(int graph[SIZE][SIZE], int src, int dest, int path[SIZE], int *path_size) {
    int dist[SIZE];        // Array para armazenar as menores distâncias da origem até cada nó
    int visited[SIZE] = {0}; // Array para marcar os nós já visitados
    int prev[SIZE];        // Array para rastrear o nó anterior no menor caminho

    // Passo 1: Inicializar as distâncias e o anterior
    for (int i = 0; i < SIZE; i++) {
        dist[i] = INF;    // Todas as distâncias são infinitas inicialmente
        prev[i] = -1;     // Nenhum nó possui anterior no início
    }
    dist[src] = 0;        // A distância do nó de origem para ele mesmo é 0

    // Passo 2: Iterar pelo grafo para encontrar o menor caminho
    for (int count = 0; count < SIZE - 1; count++) {
        // Encontra o nó com a menor distância ainda não visitado
        int u = minDistance(dist, visited);
        visited[u] = 1;   // Marca o nó como visitado

        // Atualiza as distâncias para os nós vizinhos
        for (int v = 0; v < SIZE; v++) {
            /*
             * Verifica se:
             *  - O nó v não foi visitado
             *  - Existe uma aresta entre u e v (graph[u][v] != 0)
             *  - A distância até u não é infinita
             *  - A distância atual até v é maior que a distância até u + custo da aresta
             */
            if (!visited[v] && graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];  // Atualiza a distância para v
                prev[v] = u;                      // Atualiza o predecessor de v
            }
        }
    }

    // Passo 3: Reconstruir o caminho do nó de destino para o nó de origem
    *path_size = 0;       // Inicializa o tamanho do caminho
    for (int at = dest; at != -1; at = prev[at]) {
        path[(*path_size)++] = at;  // Adiciona cada nó ao caminho
    }
    // O caminho será retornado de trás para frente (do destino para a origem)
}

// Converte coordenadas (linha, coluna) para um alias (ex: "1a")
void coordinatesToAlias(int row, int col, char *alias) {
    alias[0] = '1' + row;  // Converte a linha para '1'-'8'
    alias[1] = 'a' + col;  // Converte a coluna para 'a'-'h'
    alias[2] = '\0';       // Termina a string
}

// Imprime a lista de produtos de forma compacta (horizontal)
void printProductsCompact() {
    printf("\nProdutos:\n");
    for (int row = 0; row < 8; row++) {  // Itera por linhas
        for (int col = 0; col < 8; col++) {  // Itera por colunas
            int index = row * 8 + col;
            char alias[3];
            coordinatesToAlias(row, col, alias);
            printf("%s - %-12s", alias, products[index]);  // Alinha cada item
        }
        printf("\n");  // Nova linha após cada linha do tabuleiro
    }
}

// Converte um alias (ex: "1a") para coordenadas (linha, coluna)
int aliasToCoordinates(const char *alias, int *row, int *col) {
    if (strlen(alias) != 2) return 0; // Verifica se o alias é válido
    *row = alias[0] - '1';            // Converte a linha do alias
    *col = alias[1] - 'a';            // Converte a coluna do alias
    return (*row >= 0 && *row < 8 && *col >= 0 && *col < 8);  // Verifica se está dentro dos limites
}

// Constrói a matriz de adjacência do grafo para o tabuleiro 8x8
void buildGraph(int graph[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            graph[i][j] = 0;  // Inicializa a matriz com zeros
        }
    }

    // Define as conexões entre os nós adjacentes (cima, baixo, esquerda, direita)
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int node = row * 8 + col;
            if (row > 0) graph[node][(row - 1) * 8 + col] = 1; // Cima
            if (row < 7) graph[node][(row + 1) * 8 + col] = 1; // Baixo
            if (col > 0) graph[node][row * 8 + col - 1] = 1; // Esquerda
            if (col < 7) graph[node][row * 8 + col + 1] = 1; // Direita
        }
    }
}

// Imprime o tabuleiro com origem, destino e o caminho percorrido
void printBoard(int src, int dest, int path[], int path_size) {
    printf("\nTabuleiro 8x8 (com origem, destino e caminho):\n");
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            int index = row * 8 + col;

            if (index == src) {
                printf(" S ");
            } else if (index == dest) {
                printf(" D ");
            } else {
                int is_path = 0;
                for (int i = 0; i < path_size; i++) {
                    if (path[i] == index) {
                        is_path = 1;
                        break;
                    }
                }
                if (is_path) {
                    printf(" * ");
                } else {
                    printf(" . ");
                }
            }
        }
        printf("\n");
    }
}

int main() {
    int graph[SIZE][SIZE];
    buildGraph(graph);

    // Exibe o tabuleiro inicial e a lista de produtos em formato compacto
    printProductsCompact();

    char src_alias[3], dest_alias[3];
    int src_row, src_col, dest_row, dest_col;
    int src = -1, dest;

    while (1) {
        if (src == -1) {
            printf("Digite o alias do nó de origem (ex: 1a): ");
            scanf("%s", src_alias);
            if (!aliasToCoordinates(src_alias, &src_row, &src_col)) {
                printf("Alias inválido! Tente novamente.\n");
                continue;
            }
            src = src_row * 8 + src_col;
        }

        printProductsCompact();

        printf("Digite o alias do próximo nó de destino (ex: 8h ou 'fim' para encerrar): ");
        scanf("%s", dest_alias);
        if (strcmp(dest_alias, "fim") == 0) {
            printf("Programa encerrado.\n");
            break;
        }
        if (!aliasToCoordinates(dest_alias, &dest_row, &dest_col)) {
            printf("Alias inválido! Tente novamente.\n");
            continue;
        }
        dest = dest_row * 8 + dest_col;

        int path[SIZE], path_size = 0;
        dijkstra(graph, src, dest, path, &path_size);

        printf("\nMenor caminho do nó %s (%s) para o nó %s (%s):\n", src_alias, products[src], dest_alias, products[dest]);
        for (int i = path_size - 1; i >= 0; i--) {
            int row = path[i] / 8;
            int col = path[i] % 8;
            char alias[3];
            coordinatesToAlias(row, col, alias);
            printf("%s ", alias);
        }
        printf("\n");

        src = dest;
        strcpy(src_alias, dest_alias);

        printBoard(src, dest, path, path_size);
    }

    return 0;
}