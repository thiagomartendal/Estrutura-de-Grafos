#ifndef BUSCA_H
#define BUSCA_H

#include <iostream>
#include <string>
#include <queue>
#include <map>
#include <set>
#include <limits>
#include "../grafo.h"

typedef struct VerticeFila {
  int vertice;
  int custoArestas;
} VerticeFila;

class Busca {
private:
  std::queue<VerticeFila> fila;
  std::map<int, bool> C;
  std::map<int, int> D;
  std::map<int, int> A;
  std::map<int, int> ligacaoVizinhos;
  std::map<int, std::set<int>> verticePorNivel;
  bool primeiraIteracao{true};
  Grafo grafo;

public:
  Busca(std::string nomeArquivo, int s);
  Busca(Grafo entrada, int s);
  void buscar();
  void exibir();
};

#endif
