#include "formar_ciclo.h"

FormarCiclo::FormarCiclo(std::string nomeArquivo, int v) {
  grafo.ler(nomeArquivo);
  if (v == -1) {
    for (auto &it: grafo.getVertices()) {
      if (grafo.grau(it.first) >= 1) {
        v = it.first;
        break;
      }
    }
  }
  verticeMestre = v;
  cicloEuleriano.verticeInicial = verticeMestre;
  FormarCiclo::procurarArestas();
  // for (auto it: C1) {
  //   for (auto it2: it.second) {
  //     std::cout << it.first << " " << it2.first << " " << it2.second << std::endl;
  //   }
  // }
  // for (auto it: C1[verticeMestre]) {
  //   std::cout << "V: " << verticeMestre << " C: " << it.first << std::endl;
  // }
}

FormarCiclo::FormarCiclo(Grafo entrada, int v) {
  if (v == -1) {
    for (auto &it: entrada.getVertices()) {
      if (entrada.grau(it.first) >= 1) {
        v = it.first;
        break;
      }
    }
  }
  verticeMestre = v;
  grafo = entrada;
  cicloEuleriano.verticeInicial = verticeMestre;
  FormarCiclo::procurarArestas();
}

void FormarCiclo::procurarArestas() {
  for (auto &it: grafo.getArestas()) {
    for (auto &it2: it.second) {
      ArestaVisitada aresta;
      aresta.verticePartida = it.first;
      aresta.verticeChegada = it2.first;
      C.push_back(aresta);
      C1[it.first].insert(std::make_pair(it2.first, false));
    }
  }
}

// void FormarCiclo::formarCiclo() {
//   ciclo.ciclo.push_back(verticeMestre);
//   // t = verticeMestre
//   // v = verticeMestre
//   // do {
//   //
//   // } while (v != t);
//   for (ArestaVisitada &aresta: C) {
//     if (!aresta.visitada) {
//       if (aresta.verticePartida == verticeMestre) {
//         verticeMestre = aresta.verticeChegada;
//         aresta.visitada = true;
//         ciclo.arestasCiclo.push_back(aresta);
//         for (ArestaVisitada &aresta2: C) {
//           if ((aresta.verticePartida == aresta2.verticeChegada) && (aresta.verticeChegada == aresta2.verticePartida)) {
//             aresta2.visitada = true;
//           }
//         }
//         FormarCiclo::formarCiclo();
//         break;
//       }
//     }
//   }
// }

// void FormarCiclo::formarCiclo() {
//   cicloTotal = FormarCiclo::buscarSubcicloEuleriano();
//   if (cicloTotal.size() == 0) {
//     cicloTotal.clear();
//     return;
//   }
//   if (cicloTotal[0] != cicloTotal[cicloTotal.size()-1]) {
//     cicloTotal.clear();
//     return;
//   }
//   int i = 0;
//   for (int x: cicloTotal) {
//     for (auto it: C1[x]) {
//       if (it.second == false) {
//         verticeMestre = x;
//         std::vector<int> cicloL = FormarCiclo::buscarSubcicloEuleriano();
//         if (cicloL.size() == 0) {
//           cicloTotal.clear();
//           return;
//         }
//         if (cicloL[0] != cicloL[cicloL.size()-1]) {
//           return;
//         }
//         cicloTotal.erase(cicloTotal.begin()+i);
//         cicloTotal.insert(cicloTotal.begin()+i, cicloL.begin(), cicloL.end());
//         break;
//       }
//     }
//     i++;
//   }
//   for (int y: cicloTotal) {
//     for (auto it: C1[y]) {
//       if (it.second == false) {
//         FormarCiclo::formarCiclo();
//         break;
//       }
//     }
//   }
// }
//
// std::vector<int> FormarCiclo::buscarSubcicloEuleriano() {
//   std::vector<int> ciclo;
//   ciclo.push_back(verticeMestre);
//   int t = verticeMestre;
//   int v = verticeMestre;
//   do {
//     bool encontrouVizinhoVazio = false;
//     for (int u: grafo.vizinhos(v)) {
//       if (C1[v][u] == false) {
//         encontrouVizinhoVazio = true;
//         C1[v][u] = true;
//         C1[u][v] = true;
//         v = u;
//         ciclo.push_back(v);
//         break;
//       }
//     }
//     if (!encontrouVizinhoVazio) {
//       ciclo.clear();
//       break;
//     }
//   } while (v != t);
//   return ciclo;
// }

std::vector<int> FormarCiclo::buscarSubcicloEuleriano() {
  std::vector<int> ciclo;
  ciclo.push_back(verticeMestre);
  int t = verticeMestre;
  int v = verticeMestre;
  do {
    bool encontrouVizinhoVazio = false;
    for (int u: grafo.vizinhos(v)) {
      if (C1[v][u] == false) {
        encontrouVizinhoVazio = true;
        C1[v][u] = true;
        C1[u][v] = true;
        cicloEuleriano.arestasCiclo[v].insert({u, true});
        v = u;
        ciclo.push_back(v);
        break;
      }
    }
    if (!encontrouVizinhoVazio) {
      ciclo.clear();
      cicloEuleriano.arestasCiclo.clear();
      break;
    }
  } while (v != t);
  if ((ciclo.size() == 0) || (ciclo[0] != ciclo[ciclo.size()-1])) {
    ciclo.clear();
    cicloEuleriano.arestasCiclo.clear();
    return ciclo;
  }
  int i = 0;
  for (int x: ciclo) {
    for (auto it: C1[x]) {
      if (it.second == false) {
        verticeMestre = x;
        std::vector<int> cicloL = FormarCiclo::buscarSubcicloEuleriano();
        if ((cicloL.size() == 0) || (cicloL[0] != cicloL[cicloL.size()-1])) {
          ciclo.clear();
          cicloEuleriano.arestasCiclo.clear();
          return ciclo;
        }
        ciclo.erase(ciclo.begin()+i);
        ciclo.insert(ciclo.begin()+i, cicloL.begin(), cicloL.end());
        break;
      }
    }
    i++;
  }
  return ciclo;
}

void FormarCiclo::formarCiclo() {
  bool grauImpar = false;
  for (auto &it: grafo.getVertices()) {
    if (grafo.grau(it.first) % 2 != 0) {
      cicloEuleriano.existeCiclo = false;
      grauImpar = true;
      break;
    }
  }
  if (!grauImpar) {
    cicloTotal = FormarCiclo::buscarSubcicloEuleriano();
    bool existeCiclo = false;
    if (cicloTotal.size() > 0) {
      if (cicloTotal[0] == cicloTotal[cicloTotal.size()-1]) {
        existeCiclo = true;
      }
      for (auto it: C1) {
        for (auto it2: it.second) {
          if (it2.second == false) {
            existeCiclo = false;
            cicloTotal.clear();
            break;
          }
        }
      }
    }
    cicloEuleriano.existeCiclo = existeCiclo;
    cicloEuleriano.ciclo = cicloTotal;
  }
}

void FormarCiclo::buscar() {
  FormarCiclo::formarCiclo();
  // if (ciclo.verticeInicial == ciclo.ciclo[ciclo.ciclo.size()-1]) {
  //   ciclo.existeCiclo = true;
  // }
  // for (int i = 0; i < ciclo.arestasCiclo.size(); i++) {
  //   for (int j = i+1; j < ciclo.arestasCiclo.size(); j++) {
  //     if (ciclo.arestasCiclo[i] == ciclo.arestasCiclo[j]) {
  //       ciclo.existeCiclo = false;
  //       break;
  //     }
  //   }
  // }
  // for (ArestaVisitada aresta: C) {
  //   if (aresta.visitada == false) {
  //     ciclo.existeCiclo = false;
  //     break;
  //   }
  // }
  // for (auto &it: grafo.getVertices()) {
  //   if (grafo.grau(it.first) % 2 != 0) {
  //     ciclo.existeCiclo = false;
  //     break;
  //   }
  // }
}

void FormarCiclo::exibirCiclo() {
  std::cout << cicloEuleriano.existeCiclo << std::endl;
  if (cicloEuleriano.existeCiclo) {
    for (int i = 0; i < cicloEuleriano.ciclo.size(); i++) {
      std::cout << cicloEuleriano.ciclo[i];
      if (i < cicloEuleriano.ciclo.size()-1) {
        std::cout << ",";
      }
    }
    std::cout << std::endl;
  }
}

Ciclo FormarCiclo::getCiclo() {
  return cicloEuleriano;
}
