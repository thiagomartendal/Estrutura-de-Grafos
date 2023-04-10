#include "grafo.h"

Grafo::Grafo(TipoGrafo tipo) : tipoGrafo(tipo) {

}

bool Grafo::existeVertice(int vertice) {
    return (vertices.find(vertice) != vertices.end());
}

void Grafo::novoVertice(int id, std::string nomeVertice) {
  vertices.insert({id, nomeVertice});
}

void Grafo::novaAresta(int vertice1, int vertice2, double peso) {
  if (!Grafo::existeVertice(vertice1)) {
    throw(std::runtime_error("O vértice "+std::to_string(vertice1)+" não existe."));
  }
  if (!Grafo::existeVertice(vertice2)) {
    throw(std::runtime_error("O vértice "+std::to_string(vertice2)+" não existe."));
  }
  if (tipoGrafo == TipoGrafo::NAO_ORIENTADO) {
    arestas[vertice1].insert({vertice2, peso});
    arestas[vertice2].insert({vertice1, peso});
  } else {
    arestas[vertice1].insert({vertice2, peso});
  }
}

std::unordered_map<int, std::string> Grafo::getVertices() {
  return vertices;
}

std::unordered_map<int, std::unordered_map<int, double>> Grafo::getArestas() {
  return arestas;
}

int Grafo::qtdVertices() {
  return vertices.size();
}

int Grafo::qtdArestas() {
  return arestas.size();
}

int Grafo::grau(int vertice) {
  return arestas[vertice].size();
}

std::string Grafo::rotulo(int vertice) {
  if (Grafo::existeVertice(vertice)) {
    return vertices[vertice];
  }
  return "";
}

std::unordered_set<int> Grafo::vizinhos(int vertice) {
  std::unordered_set<int> conjuntoVizinhos;
  for (auto &it: arestas[vertice]) {
    conjuntoVizinhos.insert(it.first);
  }
  return conjuntoVizinhos;
}

bool Grafo::haAresta(int vertice1, int vertice2) {
  if (!Grafo::existeVertice(vertice1)) {
    throw(std::runtime_error("O vértice "+std::to_string(vertice1)+" não existe."));
  }
  if (!Grafo::existeVertice(vertice2)) {
    throw(std::runtime_error("O vértice "+std::to_string(vertice2)+" não existe."));
  }
  std::unordered_map<int, double> m1 = arestas[vertice1];
  for (auto &m2: m1) {
    if (m2.first == vertice2) {
      return true;
    }
  }
  return false;
}

double Grafo::peso(int vertice1, int vertice2) {
  if (!Grafo::haAresta(vertice1, vertice2)) {
    return std::numeric_limits<double>::max();
  }
  std::unordered_map<int, double> m1 = arestas[vertice1];
  for (auto &m2: m1) {
    if (m2.first == vertice2) {
      return m2.second;
    }
  }
  return -1.0;
}

void Grafo::ler(std::string nomeArquivo) {
  std::ifstream arquivo;
  arquivo.open(nomeArquivo, std::ios::out | std::ios::app | std::ios::binary);
  if (arquivo.is_open()) {
    std::string linha;
    int produz;
    std::string tipoAresta = "";
    if (tipoGrafo == TipoGrafo::ORIENTADO) {
      tipoAresta = "*arcs";
    } else {
      tipoAresta = "*edges";
    }
    while (getline(arquivo, linha)) {
      if (linha.substr(0,9) == "*vertices") {
        produz = 0;
      } else if (linha.substr(0,6) == tipoAresta) {
        produz = 1;
      } else {
        if (produz == 0) {
          std::stringstream ss(linha);
          std::string palavra;
          int cont = 0;
          int id;
          std::string rotulo = "";
          while (ss >> palavra) {
            if (cont == 0) {
              id = std::stoi(palavra);
            } else if (cont >= 1) {
              rotulo += palavra+" ";
            }
            cont++;
          }
          rotulo[rotulo.length()-1] = '\0';
          Grafo::novoVertice(id, rotulo);
        } else if (produz == 1) {
          std::stringstream ss(linha);
          std::string palavra;
          int cont = 0;
          int vertice1 = -1, vertice2 = -1;
          while (ss >> palavra) {
            if (cont == 0) {
              vertice1 = std::stoi(palavra);
            } else if (cont == 1) {
              vertice2 = std::stoi(palavra);
            } else if (cont == 2) {
              Grafo::novaAresta(vertice1, vertice2, std::stod(palavra));
              vertice1 = -1;
              vertice2 = -1;
            }
            cont++;
          }
        }
      }
    }
    arquivo.close();
  } else {
    throw(std::runtime_error("O arquivo "+nomeArquivo+" não existe."));
  }
}

void Grafo::removerAresta(int vertice1, int vertice2) {
  arestas[vertice1].erase(vertice2);
  if (tipoGrafo == TipoGrafo::NAO_ORIENTADO) {
    arestas[vertice2].erase(vertice1);
  }
}
