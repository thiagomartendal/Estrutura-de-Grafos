#ifndef CICLO_H
#define CICLO_H

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <utility>
#include "../grafo.h"

typedef struct ArestaVisitada {
  int verticePartida;
  int verticeChegada;
  bool visitada{false};
  bool operator==(const ArestaVisitada &aresta) {
    if ((aresta.verticePartida == verticePartida) && (aresta.verticeChegada == verticeChegada)) {
      return true;
    }
    return false;
  }
  ArestaVisitada operator[](int u) {
    if (verticePartida == u && verticeChegada == u) {
      return {verticePartida, verticeChegada, visitada};
    }
    return {};
  }
} ArestaVisitada;

// typedef struct Ciclo {
//   bool existeCiclo{false};
//   int verticeInicial;
//   std::vector<int> ciclo;
//   std::vector<ArestaVisitada> arestasCiclo;
// } Ciclo;

typedef struct Ciclo {
  bool existeCiclo{false};
  int verticeInicial;
  std::vector<int> ciclo;
  std::map<int, std::map<int, bool>> arestasCiclo;
} Ciclo;

class FormarCiclo {
private:
  Grafo grafo;
  Ciclo cicloEuleriano;
  int verticeMestre;
  std::vector<int> cicloTotal;
  std::vector<ArestaVisitada> C;
  std::map<int, std::map<int, bool>> C1;
  void procurarArestas();
  void formarCiclo();
  std::vector<int> buscarSubcicloEuleriano();

public:
  FormarCiclo(std::string nomeArquivo, int v = -1);
  FormarCiclo(Grafo entrada, int v = -1);
  void buscar();
  void exibirCiclo();
  Ciclo getCiclo();
};

#endif
