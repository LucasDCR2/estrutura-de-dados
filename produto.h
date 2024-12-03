// produto.h
#ifndef PRODUTO_H
#define PRODUTO_H

#include <string>

// Estrutura que define um Produto com nome e posição no supermercado
struct Produto
{
    std::string nome;
    std::string posicao; // Posição no supermercado (ex: "1A", "2E", ...)
};

#endif // PRODUTO_H