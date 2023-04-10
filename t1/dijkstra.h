#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include <iostream>
#include <map>
#include <vector>
#include <limits>
#include <algorithm>
#include "../grafo.h"

typedef struct CaminhoMinimo {
  int destino;
  double distancia;
  std::vector<int> caminho;
  bool operator==(const CaminhoMinimo &c) {
    if (c.destino == destino) {
      return true;
    }
    return false;
  }
} CaminhoMinimo;

class Dijkstra {
private:
  Grafo grafo;
  std::map<int, bool> C;
  std::map<int, double> D;
  std::map<int, int> A;
  std::vector<CaminhoMinimo> caminhos;
  void prepararEstruturas();
  void formarCiclos();
  int argMin();

public:
  Dijkstra(std::string nomeArquivo, int s);
  Dijkstra(Grafo entrada, int s);
  void buscarCaminhosMinimos();
  void exibir();
  std::vector<CaminhoMinimo> getCaminhos();
};

#endif
