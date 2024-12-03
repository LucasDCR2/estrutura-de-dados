    // 1. **Compilar o Projeto usando clang++:**
    //    Abra o terminal, navegue até o diretório do projeto e execute o seguinte comando:

    //    ```bash
    //    clang++ -std=c++11 main.cpp grafo.cpp dijkstra.cpp -o programa
    //    ```

    //    - `clang++`: Invoca o compilador C++.
    //    - `-std=c++11`: Usa o padrão C++11.
    //    - `main.cpp grafo.cpp dijkstra.cpp`: Lista dos arquivos de implementação a serem compilados.
    //    - `-o programa`: Define o nome do executável como "programa".

    // 3. **Executar o Programa:**
    //    Após a compilação bem-sucedida, execute o programa com o comando:

    //    ```bash
    //    ./programa
    //    ```


#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include "produto.h"  // Estrutura que define um Produto
#include "grafo.h"    // Funções para construir e exibir o grafo do supermercado
#include "dijkstra.h" // Funções para executar o algoritmo de Dijkstra

int main()
{
    // ### 1. Definição dos Produtos Disponíveis ###
    // Cria uma lista de produtos com seus nomes e posições no layout do supermercado.
    std::vector<Produto> produtos = {
        {"Arroz", "1A"}, {"Feijão", "1B"}, {"Macarrão", "1C"}, {"Farinha", "1D"},
        {"Açúcar", "1E"}, {"Sal", "1F"}, {"Óleo", "1G"}, {"Café", "1H"},
        {"Molho", "2A"}, {"Mostarda", "2B"}, {"Ketchup", "2C"}, {"Maionese", "2D"},
        {"Atum", "2E"}, {"Sardinha", "2F"}, {"Ervilha", "2G"}, {"Milho", "2H"},
        {"Granola", "4A"}, {"Aveia", "4B"}, {"Cereal", "4C"}, {"Pão", "4D"},
        {"Achocolatado", "4E"}, {"Margarina", "4F"}, {"Queijo", "4G"}, {"Leite", "4H"},
        {"Água", "5A"}, {"Refrigerante", "5B"}, {"Suco", "5C"}, {"Chá", "5D"},
        {"Cerveja", "5E"}, {"Vinho", "5F"}, {"Vodka", "5G"}, {"Whisky", "5H"},
    };

    // ### 2. Mapeamento das Posições para Índices Numéricos ###
    // Cria um mapa para associar cada posição (e.g., "1A") a um índice numérico único.
    std::map<std::string, int> mapaNos;
    int n; // Número total de nós no grafo

    // ### 3. Construção do Grafo do Supermercado ###
    // Inicializa uma lista de adjacência para representar o grafo.
    std::vector<std::vector<std::pair<int, int>>> grafo;
    construirGrafo(grafo, mapaNos, n); // Função modularizada para construir o grafo

    // ### 4. Adição dos Nós de Entrada e Saída ###
    // Define os pontos de entrada e saída do supermercado no grafo.

    // Adiciona o nó de entrada ao grafo
    std::string entrada = "Entrada";
    int nodoEntrada = n++; // Incrementa 'n' para reservar um novo índice
    grafo.resize(n); // Redimensiona o grafo para acomodar o novo nó
    grafo[nodoEntrada].push_back({mapaNos["1A"], 1}); // Conecta 'Entrada' a '1A' com custo 1
    grafo[mapaNos["1A"]].push_back({nodoEntrada, 1}); // Conexão bidirecional
    mapaNos[entrada] = nodoEntrada; // Atualiza o mapa com a nova posição

    // Adiciona o nó de saída ao grafo
    std::string saida = "Saída";
    int nodoSaida = n++;
    grafo.resize(n);
    grafo[nodoSaida].push_back({mapaNos["5H"], 1}); // Conecta 'Saída' a '5H' com custo 1
    grafo[mapaNos["5H"]].push_back({nodoSaida, 1}); // Conexão bidirecional
    mapaNos[saida] = nodoSaida; // Atualiza o mapa com a nova posição

    // ### 5. Exibição das Prateleiras Organizadas ###
    // Define as colunas do lado esquerdo e direito de cada corredor.
    char colunasEsquerda[] = {'A', 'B', 'C', 'D'};
    char colunasDireita[] = {'E', 'F', 'G', 'H'};
    std::vector<int> corredores = {1, 2, 4, 5}; // Corredores existentes no supermercado

    // Chama a função modularizada para exibir o layout das prateleiras
    exibirPrateleiras(corredores, colunasEsquerda, colunasDireita);

    // ### 6. Interação com o Usuário para Seleção de Produtos ###
    // Cria uma lista para armazenar as posições dos produtos selecionados pelo usuário.
    std::vector<std::string> listaCompras;
    int opcao; // Variável para armazenar a escolha do usuário

    // Exibe a lista de produtos disponíveis
    std::cout << "\nProdutos disponíveis no supermercado:\n";
    for (size_t i = 0; i < produtos.size(); i++)
    {
        std::cout << i + 1 << ". " << produtos[i].nome << " (" << produtos[i].posicao << ")\n";
    }
    std::cout << "0. Finalizar seleção\n";

    // Loop para permitir que o usuário selecione múltiplos produtos
    do
    {
        std::cout << "\nDigite o número do produto que deseja adicionar à lista de compras (ou 0 para finalizar): ";
        std::cin >> opcao;

        if (opcao > 0 && opcao <= (int)produtos.size())
        {
            // Obtém o produto selecionado
            std::string produtoSelecionado = produtos[opcao - 1].nome;
            std::string posicaoSelecionada = produtos[opcao - 1].posicao;

            // Verifica se o produto já está na lista de compras
            if (std::find(listaCompras.begin(), listaCompras.end(), posicaoSelecionada) != listaCompras.end())
            {
                std::cout << produtoSelecionado << " já está na lista de compras. Escolha outro produto.\n";
            }
            else
            {
                // Adiciona o produto à lista de compras
                listaCompras.push_back(posicaoSelecionada);
                std::cout << produtoSelecionado << " adicionado à lista de compras.\n";
            }
        }
        else if (opcao != 0)
        {
            std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 0); // Continua até que o usuário finalize a seleção

    // Verifica se a lista de compras está vazia
    if (listaCompras.empty())
    {
        std::cout << "\nNenhum produto foi selecionado. Finalizando o programa.\n";
        return 0; // Encerra o programa
    }

    // ### 7. Exibição da Lista de Compras ###
    // Lista os produtos selecionados pelo usuário.
    std::cout << "\nLista de compras:\n";
    for (const auto &produto : listaCompras)
    {
        std::cout << "- " << produto << "\n";
    }

    // ### 8. Preparação dos Pontos a Visitar ###
    // Cria uma lista que inclui a entrada, os produtos selecionados e a saída.
    std::vector<std::string> pontosVisitar = {entrada};
    pontosVisitar.insert(pontosVisitar.end(), listaCompras.begin(), listaCompras.end());
    pontosVisitar.push_back(saida);

    // ### 9. Criação da Matriz de Distâncias ###
    // Inicializa matrizes para armazenar as distâncias e os caminhos entre os pontos a visitar.
    int m = pontosVisitar.size(); // Número de pontos a visitar
    std::vector<std::vector<int>> distancias(m, std::vector<int>(m, INF)); // Matriz de distâncias
    std::vector<std::vector<std::vector<int>>> caminhos(m, std::vector<std::vector<int>>(m)); // Matriz de caminhos

    // Calcula as distâncias entre todos os pares de pontos a visitar usando o algoritmo de Dijkstra
    for (int i = 0; i < m; i++)
    {
        std::vector<int> dist, caminhoTemp;
        int u = mapaNos[pontosVisitar[i]]; // Índice do ponto de partida
        dijkstra(grafo, u, dist, caminhoTemp); // Executa Dijkstra a partir de 'u'

        for (int j = 0; j < m; j++)
        {
            int v = mapaNos[pontosVisitar[j]]; // Índice do ponto de destino
            distancias[i][j] = dist[v]; // Armazena a distância de 'u' para 'v'
            caminhos[i][j] = reconstruirCaminho(u, v, caminhoTemp); // Armazena o caminho de 'u' para 'v'
        }
    }

    // ### 10. Encontrar a Melhor Sequência para Visitar os Produtos ###
    // Gera todas as permutações possíveis das ordens de visitação dos produtos para encontrar a menor rota.

    // Cria uma lista de índices correspondentes aos produtos na lista de compras
    std::vector<int> indicesProdutos(m - 2); // Exclui entrada e saída
    for (int i = 1; i <= m - 2; i++)
        indicesProdutos[i - 1] = i;

    int menorCusto = INF;               // Inicializa o menor custo como infinito
    std::vector<int> melhorSequencia;   // Armazena a melhor sequência de visitação

    // Ordena os índices para garantir que 'next_permutation' gere todas as permutações
    std::sort(indicesProdutos.begin(), indicesProdutos.end());

    // Gera todas as permutações possíveis das ordens de visitação
    do
    {
        int custoAtual = 0; // Custo acumulado para a sequência atual
        std::vector<int> sequenciaAtual = {0}; // Inicia com a entrada (índice 0)
        sequenciaAtual.insert(sequenciaAtual.end(), indicesProdutos.begin(), indicesProdutos.end()); // Adiciona os produtos
        sequenciaAtual.push_back(m - 1); // Adiciona a saída

        // Calcula o custo total desta sequência
        bool caminhoValido = true;
        for (size_t i = 0; i < sequenciaAtual.size() - 1; i++)
        {
            int u = sequenciaAtual[i];     // Índice do ponto atual
            int v = sequenciaAtual[i + 1]; // Índice do próximo ponto

            // Verifica se há um caminho válido entre 'u' e 'v'
            if (distancias[u][v] == INF)
            {
                caminhoValido = false; // Não há caminho, sequência inválida
                break;
            }
            custoAtual += distancias[u][v]; // Adiciona o custo do trecho ao custo total
        }

        // Se a sequência é válida e tem um custo menor, atualiza a melhor sequência
        if (caminhoValido && custoAtual < menorCusto)
        {
            menorCusto = custoAtual;
            melhorSequencia = sequenciaAtual;
        }

    } while (std::next_permutation(indicesProdutos.begin(), indicesProdutos.end())); // Continua até todas as permutações serem geradas

    // ### 11. Verificação de Possibilidade de Caminho ###
    // Se nenhuma sequência válida foi encontrada, informa o usuário e encerra o programa.
    if (menorCusto == INF)
    {
        std::cout << "\nNão é possível encontrar um caminho que satisfaça as restrições.\n";
        return 0;
    }

    // ### 12. Exibição do Menor Caminho Encontrado ###
    // Reconstrói e exibe o caminho completo baseado na melhor sequência encontrada.
    std::cout << "\nMenor caminho:\n";
    std::vector<int> caminhoFinal; // Lista final do caminho a ser exibido

    // Itera sobre a melhor sequência e concatena os caminhos parciais
    for (size_t i = 0; i < melhorSequencia.size() - 1; i++)
    {
        int u = melhorSequencia[i];
        int v = melhorSequencia[i + 1];

        // Obtém o caminho parcial de 'u' para 'v'
        std::vector<int> caminhoParcial = caminhos[u][v];
        // Remove o primeiro nó do caminho parcial para evitar duplicatas, exceto no primeiro trecho
        if (!caminhoParcial.empty() && i != 0)
            caminhoParcial.erase(caminhoParcial.begin());
        // Adiciona o caminho parcial ao caminho final
        caminhoFinal.insert(caminhoFinal.end(), caminhoParcial.begin(), caminhoParcial.end());
    }

    // Converte os índices do caminho final de volta para as posições do supermercado e exibe
    for (size_t idx = 0; idx < caminhoFinal.size(); idx++)
    {
        int no = caminhoFinal[idx];
        for (const auto &par : mapaNos)
        {
            if (par.second == no)
            {
                std::cout << par.first;
                if (idx < caminhoFinal.size() - 1)
                    std::cout << " -> ";
                break;
            }
        }
    }
    std::cout << "\n\nCusto total: " << menorCusto << "\n"; // Exibe o custo total do caminho

    return 0; // Encerra o programa
}
