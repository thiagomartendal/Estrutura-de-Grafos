#include "busca.h"

Busca::Busca(std::string nomeArquivo, int s) {
  grafo.ler(nomeArquivo);
  fila.push({s, 0});
}

Busca::Busca(Grafo entrada, int s) {
  grafo = entrada;
  fila.push({s, 0});
}

void Busca::buscar() {
  VerticeFila u = fila.front();
  fila.pop();
  if (!C[u.vertice]) {
    C[u.vertice] = true;
    D[u.vertice] = u.custoArestas;
    verticePorNivel[u.custoArestas].insert(u.vertice);
    if (primeiraIteracao) {
      A[u.vertice] = -1;
      primeiraIteracao = false;
    } else {
      A[u.vertice] = ligacaoVizinhos[u.vertice];
    }
    std::unordered_set<int> vizinhos = grafo.vizinhos(u.vertice);
    for (int v: vizinhos) {
      fila.push({v, D[u.vertice]+1});
      ligacaoVizinhos[v] = u.vertice;
    }
  }
  if (fila.size() > 0) {
    Busca::buscar();
  }
}

void Busca::exibir() {
  for (auto &it: verticePorNivel) {
    std::cout << it.first << ": ";
    int i = 0;
    for (auto &it2: it.second) {
      std::cout << it2;
      if (i < it.second.size()-1) {
        std::cout << ",";
      }
      i++;
    }
    std::cout << std::endl;
  }
}
