#ifndef EDMONDS_KARP_H
#define EDMONDS_KARP_H

#include <map>
#include <set>
#include <queue>
#include <limits>
#include <vector>
#include <algorithm>
#include "../grafo.h"

class EdmondsKarp {
private:
  std::map<int, std::map<int, double>> W;
  std::map<int, bool> C;
  std::map<int, int> A;
  std::queue<int> Q;
  int s, t;
  Grafo grafo;
  void prepararEstruturas();
  void arestasRetorno();
  std::vector<int> fluxoMaximo();

public:
  EdmondsKarp(std::string nomeArquivo, int s, int t);
  EdmondsKarp(Grafo entrada, int s, int t);
  void fordFulkerson();
};

#endif
