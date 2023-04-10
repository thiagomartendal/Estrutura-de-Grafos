#ifndef ORDENACAO_TOPOLOGICA_H
#define ORDENACAO_TOPOLOGICA_H

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "../grafo.h"

class OrdenacaoTopologica {
private:
  std::map<int, bool> C;
  std::map<int, int> T;
  std::map<int, int> F;
  std::vector<int> O;
  Grafo grafo;
  void preparaEstruturas();
  void DFS();
  void DFSVisita(int v, int &tempo);

public:
  OrdenacaoTopologica(std::string nomeArquivo);
  OrdenacaoTopologica(Grafo entrada);
  void ordenar();
  void exibir();
};

#endif
