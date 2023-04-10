#include "kruskal.h"

Kruskal::Kruskal(std::string nomeArquivo) {
  grafo.ler(nomeArquivo);
}

Kruskal::Kruskal(Grafo entrada) {
  grafo = entrada;
}

void Kruskal::ordenar(std::vector<std::pair<int, int>> &E) {
  for (int i = 0; i < E.size(); i++) {
    for (int j = i+1; j < E.size(); j++) {
      if (grafo.peso(E[i].first, E[i].second) > grafo.peso(E[j].first, E[j].second)) {
        std::pair<int, int> tmp = E[i];
        E[i] = E[j];
        E[j] = tmp;
      }
    }
  }
}

Grafo Kruskal::AGM() {
  std::map<int, std::map<int, double>> A;
  std::map<int, std::set<int>> S;
  for (auto &it: grafo.getVertices()) {
    S[it.first].insert(it.first);
  }
  std::vector<std::pair<int, int>> E;
  for (auto &it: grafo.getArestas()) {
    for (auto &it2: it.second) {
      E.push_back(std::make_pair(it.first, it2.first));
    }
  }
  Kruskal::ordenar(E);
  for (auto &it: E) {
    int u = it.first;
    int v = it.second;
    if (S[u] != S[v]) {
      A[u][v] = grafo.peso(u, v);
      std::set<int> x;
      for (int it: S[u]) {
        x.insert(it);
      }
      for (int it: S[v]) {
        x.insert(it);
      }
      for (int y: x) {
        S[y] = x;
      }
    }
  }
  for (auto &it: A) {
    agm.novoVertice(it.first, grafo.rotulo(it.first));
    for (auto &it2: it.second) {
      agm.novoVertice(it2.first, grafo.rotulo(it2.first));
      agm.novaAresta(it.first, it2.first, it2.second);
    }
  }
  return agm;
}

void Kruskal::exibir() {
  double custo = 0.0;
  std::vector<std::pair<int, int>> E;
  for (auto &it: agm.getArestas()) {
    for (auto &it2: it.second) {
      if (std::find(E.begin(), E.end(), std::make_pair(it2.first, it.first)) == E.end()) {
        custo += agm.peso(it.first, it2.first);
        E.push_back(std::make_pair(it.first, it2.first));
      }
    }
  }
  std::cout << custo << std::endl;
  int j = 0;
  for (auto &it: agm.getArestas()) {
    int i = 0;
    for (auto &it2: it.second) {
      std::cout << it.first << "-" << it2.first;
      if (i < (it.second.size()-1)) {
        std::cout << ", ";
      }
      i++;
    }
    if (j < (agm.getArestas().size()-1)) {
      std::cout << ", ";
    }
    j++;
  }
  std::cout << std::endl;
}
