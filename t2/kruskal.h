#ifndef KRUSKAL_H
#define KRUSKAL_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include "../grafo.h"

class Kruskal {
private:
  Grafo grafo;
  Grafo agm;
  void ordenar(std::vector<std::pair<int, int>> &E);

public:
  Kruskal(std::string nomeArquivo);
  Kruskal(Grafo entrada);
  Grafo AGM();
  void exibir();
};

#endif
