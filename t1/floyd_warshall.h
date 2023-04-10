#ifndef FLOYD_WARSHALL_H
#define FLOYD_WARSHALL_H

#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <fstream>
#include "../grafo.h"

class FloydWarshall {
private:
  Grafo grafo;
  std::vector<std::vector<double>> resultado;
  std::vector<int> vertices;
  void lerVertices(int op, std::string nomeArquivo = "");
  double funcaoW(int u, int v);
  std::vector<std::vector<double>> converterGrafoEmMatriz();

public:
  FloydWarshall(std::string nomeArquivo);
  FloydWarshall(Grafo entrada);
  void calcularCaminhos();
  void exibir();
};

#endif
