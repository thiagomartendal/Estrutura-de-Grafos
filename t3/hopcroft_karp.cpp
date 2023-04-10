#include "hopcroft_karp.h"

HopcroftKarp::HopcroftKarp(std::string nomeArquivo) {
  grafo.ler(nomeArquivo);
  HopcroftKarp::prepararEstruturas();
  HopcroftKarp::emparelhar();
}

HopcroftKarp::HopcroftKarp(Grafo entrada) {
  grafo = entrada;
  HopcroftKarp::prepararEstruturas();
  HopcroftKarp::emparelhar();
}

void HopcroftKarp::prepararEstruturas() {
  int i = 0;
  for (auto &it: grafo.getVertices()) {
    D[it.first] = std::numeric_limits<int>::max();
    if (i < (grafo.getVertices().size()/2)) {
      Y.insert(it.first);
    } else {
      X.insert(it.first);
    }
    i++;
  }
}

// null é o vértice artificial, vai ficar na posição 0

void HopcroftKarp::emparelhar() {
  int m = 0;
  while (HopcroftKarp::BFS()) {
    for (int x: X) {
      if (mate[x] == 0) {
        if (HopcroftKarp::DFS(x)) {
          m++;
        }
      }
    }
  }
  std::cout << "Emparelhamento Máximo = " << m << std::endl;
  std::cout << "Arstas:" << std::endl;
  for (auto &it: mate) {
    std::cout << it.first << " " << it.second << std::endl;
  }
}

bool HopcroftKarp::BFS() {
  std::queue<int> Q;
  for (int x: X) {
    if (mate[x] == 0) {
      D[x] = 0;
      Q.push(x);
    } else {
      D[x] = std::numeric_limits<int>::max();
    }
  }
  D[0] = std::numeric_limits<int>::max();
  while (!Q.empty()) {
    int x = Q.front();
    Q.pop();
    if (D[x] < D[0]) {
      for (int y: grafo.vizinhos(x)) {
        if (D[mate[y]] == std::numeric_limits<int>::max()) {
          D[mate[y]] = D[x]+1;
          Q.push(mate[y]);
        }
      }
    }
  }
  return (D[0] != std::numeric_limits<int>::max());
}

bool HopcroftKarp::DFS(int x) {
  if (x != 0) {
    for (int y: grafo.vizinhos(x)) {
      if (D[mate[y]] == D[x]+1) {
        if (DFS(mate[y])) {
          mate[y] = x;
          mate[x] = y;
          return true;
        }
      }
    }
    D[x] = std::numeric_limits<int>::max();
    return false;
  }
  return true;
}
