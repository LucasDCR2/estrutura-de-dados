// dijkstra.h
#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <vector>
#include "constants.h"

/**
 * @brief Calcula as menores distâncias a partir de um nó inicial usando o Algoritmo de Dijkstra.
 *
 * @param grafo Representação do grafo como uma lista de adjacência.
 * @param inicio Índice do nó de início.
 * @param dist Vetor que armazenará as menores distâncias encontradas.
 * @param caminho Vetor que armazenará os predecessores de cada nó.
 */
void dijkstra(const std::vector<std::vector<std::pair<int, int>>> &grafo,
             int inicio, std::vector<int> &dist, std::vector<int> &caminho);

/**
 * @brief Reconstrói o caminho mais curto do nó de início até o nó de destino.
 *
 * @param inicio Índice do nó de início.
 * @param destino Índice do nó de destino.
 * @param caminho Vetor com os predecessores de cada nó.
 * @return std::vector<int> Sequência de nós que formam o caminho mais curto.
 */
std::vector<int> reconstruirCaminho(int inicio, int destino, const std::vector<int> &caminho);

#endif // DIJKSTRA_H