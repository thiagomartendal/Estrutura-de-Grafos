#include "dijkstra.h"

Dijkstra::Dijkstra(std::string nomeArquivo, int s) {
  grafo.ler(nomeArquivo);
  Dijkstra::prepararEstruturas();
  D[s] = 0.0;
}

Dijkstra::Dijkstra(Grafo entrada, int s) {
  grafo = entrada;
  Dijkstra::prepararEstruturas();
  D[s] = 0.0;
}

void Dijkstra::prepararEstruturas() {
  for (auto &it: grafo.getVertices()) {
    D[it.first] = 999999.0;
    A[it.first] = -1;
    C[it.first] = false;
  }
}

int Dijkstra::argMin() {
  int u = -1;
  double menor = std::numeric_limits<double>::max();
  for (auto &it: grafo.getVertices()) {
    int v = it.first;
    if (C[v] == false) {
      if (menor > D[v]) {
        menor = D[v];
        u = v;
      }
    }
  }
  return u;
}

void Dijkstra::formarCiclos() {
  for (auto &it: grafo.getVertices()) {
    int u = Dijkstra::argMin();
    C[u] = true;
    for (int v: grafo.vizinhos(u)) {
      if (D[v] > D[u]+grafo.peso(u, v)) {
        D[v] = D[u]+grafo.peso(u, v);
        A[v] = u;
      }
    }
  }
  for (auto &it: grafo.getVertices()) {
    int v = it.first;
    double d = D[it.first];
    std::vector<int> caminho;
    while (A[v] != -1) {
      caminho.push_back(A[v]);
      v = A[v];
    }
    std::reverse(caminho.begin(), caminho.end());
    caminho.push_back(it.first);
    caminhos.push_back({it.first, d, caminho});
  }
  std::reverse(caminhos.begin(), caminhos.end());
}

void Dijkstra::buscarCaminhosMinimos() {
  Dijkstra::formarCiclos();
}

void Dijkstra::exibir() {
  for (CaminhoMinimo c: caminhos) {
    std::cout << c.destino << ": ";
    for (int i = 0; i < c.caminho.size(); i++) {
      std::cout << c.caminho[i];
      if (i < c.caminho.size()-1) {
        std::cout << ",";
      } else {
        std::cout << "; ";
      }
    }
    std::cout << "d=" << c.distancia << std::endl;
  }
}

std::vector<CaminhoMinimo> Dijkstra::getCaminhos() {
  return caminhos;
}
