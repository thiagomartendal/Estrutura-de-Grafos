#include "floyd_warshall.h"

FloydWarshall::FloydWarshall(std::string nomeArquivo) {
  grafo.ler(nomeArquivo);
  FloydWarshall::lerVertices(1, nomeArquivo);
}

FloydWarshall::FloydWarshall(Grafo entrada) {
  grafo = entrada;
  FloydWarshall::lerVertices(2);
}

void FloydWarshall::lerVertices(int op, std::string nomeArquivo) {
  if (op == 1) {
    std::ifstream arquivo;
    arquivo.open(nomeArquivo, std::ios::out | std::ios::app | std::ios::binary);
    if (arquivo.is_open()) {
      std::string linha;
      int produz;
      while (getline(arquivo, linha)) {
        if (linha.substr(0,9) == "*vertices") {
          produz = 0;
        } else if (linha.substr(0,6) == "*edges") {
          produz = 1;
        } else {
          if (produz == 0) {
            std::stringstream ss(linha);
            std::string palavra;
            int cont = 0;
            while (ss >> palavra) {
              if (cont == 0) {
                vertices.push_back(std::stoi(palavra));
              }
              cont++;
            }
          } else if (produz == 1) {
            break;
          }
        }
      }
      arquivo.close();
    }
  } else if (op == 2) {
    for (auto &v: grafo.getVertices()) {
      vertices.push_back(v.first);
    }
  }
}

std::vector<std::vector<double>> FloydWarshall::converterGrafoEmMatriz() {
  int V = grafo.qtdVertices();
  std::vector<std::vector<double>> tmp(V, std::vector<double>(V));
  for (auto &u: grafo.getVertices()) {
    for (auto &v: grafo.getVertices()) {
      // tmp[u.first][v.first] = FloydWarshall::funcaoW(u.first, v.first);
      tmp[u.first-1][v.first-1] = FloydWarshall::funcaoW(u.first, v.first);
    }
  }
  return tmp;
}

double FloydWarshall::funcaoW(int u, int v) {
  if (u == v) {
    return 0.0;
  } else if ((u != v) && (grafo.haAresta(u, v))) {
    return grafo.peso(u, v);
  }
  return std::numeric_limits<double>::max();
}

void FloydWarshall::calcularCaminhos() {
  int V = grafo.qtdVertices();
  std::vector<std::vector<double>> D = FloydWarshall::converterGrafoEmMatriz();
  std::vector<std::vector<double>> anterior = D;
  for (auto &k: grafo.getVertices()) {
    std::vector<std::vector<double>> DK(V, std::vector<double>(V));
    for (auto &u: grafo.getVertices()) {
      for (auto &v: grafo.getVertices()) {
        // DK[u.first][v.first] = std::min(anterior[u.first][v.first], anterior[u.first][k.first]+anterior[k.first][v.first]);
        DK[u.first-1][v.first-1] = std::min(anterior[u.first-1][v.first-1], anterior[u.first-1][k.first-1]+anterior[k.first-1][v.first-1]);
      }
    }
    anterior = DK;
  }
  resultado = anterior;
}

void FloydWarshall::exibir() {
  for (int &u: vertices) {
    std::cout << u << ":";
    int j = 0;
    for (int &v: vertices) {
      std::cout << resultado[u-1][v-1];
      if (j < vertices.size()-1) {
        std::cout << ",";
      }
      j++;
    }
    std::cout << std::endl;
  }
}
