// grafo.cpp
#include "grafo.h"
#include <iostream>

// Função para construir o grafo do supermercado
void construirGrafo(std::vector<std::vector<std::pair<int, int>>> &grafo,
                    std::map<std::string, int> &mapaNos,
                    int &n)
{
    // Define as colunas do lado esquerdo e direito de cada corredor
    char colunasEsquerda[] = {'A', 'B', 'C', 'D'};
    char colunasDireita[] = {'E', 'F', 'G', 'H'};

    // Lista de corredores no supermercado
    std::vector<int> corredores = {1, 2, 4, 5};
    int indiceNo = 0; // Contador para atribuir índices únicos aos nós

    // Atribui índices numéricos para cada posição nas colunas
    for (int corredor : corredores)
    {
        // Atribui índices para o lado esquerdo
        for (char coluna : colunasEsquerda)
        {
            std::string posicao = std::to_string(corredor) + coluna;
            mapaNos[posicao] = indiceNo++;
        }
        // Atribui índices para o lado direito
        for (char coluna : colunasDireita)
        {
            std::string posicao = std::to_string(corredor) + coluna;
            mapaNos[posicao] = indiceNo++;
        }
    }

    n = indiceNo; // Define o número total de nós no grafo
    grafo.resize(n); // Redimensiona o grafo para acomodar todos os nós

    // Adiciona arestas dentro dos corredores (movimentos vertical e horizontal)
    for (int corredor : corredores)
    {
        // Conexões verticais no lado esquerdo
        for (int i = 0; i < 3; i++)
        {
            std::string posicaoAtual = std::to_string(corredor) + colunasEsquerda[i];
            std::string proximaPosicao = std::to_string(corredor) + colunasEsquerda[i + 1];
            int u = mapaNos[posicaoAtual];
            int v = mapaNos[proximaPosicao];
            // Cria arestas bidirecionais com peso 1
            grafo[u].push_back({v, 1});
            grafo[v].push_back({u, 1});
        }

        // Conexões verticais no lado direito
        for (int i = 0; i < 3; i++)
        {
            std::string posicaoAtual = std::to_string(corredor) + colunasDireita[i];
            std::string proximaPosicao = std::to_string(corredor) + colunasDireita[i + 1];
            int u = mapaNos[posicaoAtual];
            int v = mapaNos[proximaPosicao];
            // Cria arestas bidirecionais com peso 1
            grafo[u].push_back({v, 1});
            grafo[v].push_back({u, 1});
        }

        // Conexões horizontais entre os lados esquerdo e direito
        for (int i = 0; i < 4; i++)
        {
            std::string posicaoEsquerda = std::to_string(corredor) + colunasEsquerda[i];
            std::string posicaoDireita = std::to_string(corredor) + colunasDireita[i];
            int u = mapaNos[posicaoEsquerda];
            int v = mapaNos[posicaoDireita];
            // Cria arestas bidirecionais com peso 1
            grafo[u].push_back({v, 1});
            grafo[v].push_back({u, 1});
        }
    }

    // Adiciona conexões especiais entre corredores em posições específicas

    // Conexões envolvendo 1H
    grafo[mapaNos["1H"]].push_back({mapaNos["1D"], 1}); // Conecta 1H a 1D
    grafo[mapaNos["1H"]].push_back({mapaNos["2D"], 2}); // Conecta 1H a 2D com peso 2
    grafo[mapaNos["2D"]].push_back({mapaNos["1H"], 2}); // Conexão bidirecional

    grafo[mapaNos["1H"]].push_back({mapaNos["4E"], 2}); // Conecta 1H a 4E com peso 2
    grafo[mapaNos["4E"]].push_back({mapaNos["1H"], 2}); // Conexão bidirecional

    // Conexão entre 1E e 2A
    grafo[mapaNos["1E"]].push_back({mapaNos["2A"], 2});
    grafo[mapaNos["2A"]].push_back({mapaNos["1E"], 2});

    // Conexão entre 2H e 5E
    grafo[mapaNos["2H"]].push_back({mapaNos["5E"], 2});
    grafo[mapaNos["5E"]].push_back({mapaNos["2H"], 2});

    // Conexão entre 4H e 5D
    grafo[mapaNos["4H"]].push_back({mapaNos["5D"], 2});
    grafo[mapaNos["5D"]].push_back({mapaNos["4H"], 2});
}

// Função para exibir a disposição das prateleiras no supermercado
void exibirPrateleiras(const std::vector<int> &corredores,
                       const char colunasEsquerda[],
                       const char colunasDireita[])
{
    std::cout << "\nTabela das prateleiras:\n\n";
    std::cout << "Entrada\n|\n";

    // Itera sobre os corredores, dois de cada vez (esquerdo e direito)
    for (size_t idx = 0; idx < corredores.size(); idx += 2)
    {
        int corredorEsq = corredores[idx];
        int corredorDir = corredores[idx + 1];

        std::cout << "Corredor " << corredorEsq << ":   Corredor " << corredorDir << ":\n";
        for (int i = 0; i < 4; i++)
        {
            char colunaEsq = colunasEsquerda[i];
            char colunaDir = colunasDireita[i];

            // Exibe as posições das prateleiras lado a lado
            std::cout << corredorEsq << colunaEsq << "   " << corredorEsq << colunaDir << "       "
                      << corredorDir << colunaEsq << "   " << corredorDir << colunaDir << "\n";

            // Linha de separação entre as prateleiras, exceto na última
            if (i < 3)
                std::cout << "|     |        |     |\n";
        }
        std::cout << "|\n"; // Linha final do corredor
    }

    std::cout << "Saída\n"; // Indica a saída do supermercado
}