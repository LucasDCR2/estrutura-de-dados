// dijkstra.cpp
#include "dijkstra.h"
#include <queue>
#include <algorithm>

// Função que implementa o Algoritmo de Dijkstra
void dijkstra(const std::vector<std::vector<std::pair<int, int>>> &grafo,
             int inicio, std::vector<int> &dist, std::vector<int> &caminho)
{
    int n = grafo.size();               // Número total de nós no grafo
    dist.assign(n, INF);                // Inicializa todas as distâncias como infinito
    caminho.assign(n, -1);              // Inicializa todos os predecessores como -1
    std::vector<bool> visitado(n, false); // Vetor para marcar nós visitados

    dist[inicio] = 0;                    // A distância do nó inicial para si mesmo é 0
    // Define uma fila de prioridade que ordena pares (distância, nó) em ordem crescente de distância
    std::priority_queue<std::pair<int, int>,
                        std::vector<std::pair<int, int>>,
                        std::greater<std::pair<int, int>>> pq;
    pq.push({0, inicio});                // Insere o nó inicial na fila de prioridade

    // Loop principal do Algoritmo de Dijkstra
    while (!pq.empty())
    {
        int u = pq.top().second;         // Extrai o nó com a menor distância atual
        pq.pop();                        // Remove o nó da fila de prioridade

        if (visitado[u])
            continue;                    // Pula se o nó já foi visitado
        visitado[u] = true;              // Marca o nó como visitado

        // Itera sobre todos os vizinhos do nó atual
        for (const auto &vizinho : grafo[u])
        {
            int v = vizinho.first;       // Índice do nó vizinho
            int peso = vizinho.second;   // Peso da aresta que conecta u a v
            // Verifica se a distância através de u para v é menor que a distância atual de v
            if (dist[u] + peso < dist[v])
            {
                dist[v] = dist[u] + peso; // Atualiza a distância de v
                caminho[v] = u;           // Define u como predecessor de v
                pq.push({dist[v], v});    // Insere v na fila de prioridade com a nova distância
            }
        }
    }
}

// Função para reconstruir o caminho mais curto do nó de início até o nó de destino
std::vector<int> reconstruirCaminho(int inicio, int destino, const std::vector<int> &caminho)
{
    std::vector<int> percurso; // Vetor para armazenar o caminho reconstruído

    // Começa a reconstrução a partir do nó de destino
    for (int atual = destino; atual != -1; atual = caminho[atual])
    {
        percurso.push_back(atual); // Adiciona o nó atual ao percurso
    }

    // Inverte o vetor para que o percurso comece no nó de início e termine no destino
    std::reverse(percurso.begin(), percurso.end());

    return percurso; // Retorna o percurso reconstruído
}