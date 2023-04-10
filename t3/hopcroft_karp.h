#ifndef HOPCROFT_KARP_H
#define HOPCROFT_KARP_H

#include <iostream>
#include <map>
#include <set>
#include <limits>
#include <queue>
#include "../grafo.h"

class HopcroftKarp {
private:
  std::set<int> X;
  std::set<int> Y;
  std::map<int, int> D;
  std::map<int, int> mate;
  Grafo grafo;
  void prepararEstruturas();
  void emparelhar();
  bool BFS();
  bool DFS(int x);

public:
  HopcroftKarp(std::string nomeArquivo);
  HopcroftKarp(Grafo entrada);
  void exibir();
};

#endif
