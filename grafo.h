// grafo.h
#ifndef GRAFO_H
#define GRAFO_H

#include <vector>
#include <string>
#include <map>
#include "constants.h"

// Função para construir o grafo do supermercado
void construirGrafo(std::vector<std::vector<std::pair<int, int>>> &grafo,
                    std::map<std::string, int> &mapaNos,
                    int &n);

// Função para exibir a disposição das prateleiras
void exibirPrateleiras(const std::vector<int> &corredores,
                       const char colunasEsquerda[],
                       const char colunasDireita[]);

#endif // GRAFO_H