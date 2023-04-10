#ifndef GRAFO_H
#define GRAFO_H

#include <iostream>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <stdexcept>
#include <fstream>
#include <sstream>
#include <limits>
#include <vector>

enum TipoGrafo {
  ORIENTADO,
  NAO_ORIENTADO
};

class Grafo {
private:
  std::unordered_map<int, std::string> vertices;
  std::unordered_map<int, std::unordered_map<int, double>> arestas;
  TipoGrafo tipoGrafo;

public:
  Grafo(TipoGrafo tipo = TipoGrafo::NAO_ORIENTADO);
  bool existeVertice(int vertice);
  void novoVertice(int id, std::string nome);
  void novaAresta(int vertice1, int vertice2, double peso = -1.0);
  std::unordered_map<int, std::string> getVertices();
  std::unordered_map<int, std::unordered_map<int, double>> getArestas();
  int qtdVertices();
  int qtdArestas();
  int grau(int vertice);
  std::string rotulo(int vertice);
  std::unordered_set<int> vizinhos(int vertice);
  bool haAresta(int vertice1, int vertice2);
  double peso(int vertice1, int vertice2);
  void ler(std::string nomeArquivo);
  void removerAresta(int vertice1, int vertice2);
};

#endif
