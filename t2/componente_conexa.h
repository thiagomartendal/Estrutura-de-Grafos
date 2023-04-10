#ifndef COMPONENTE_CONEXA_H
#define COMPONENTE_CONEXA_H

#include <iostream>
#include <map>
#include <set>
#include <limits>
#include <vector>
#include <algorithm>
#include "../grafo.h"

typedef struct Componente {
  std::set<int> vertices;
  std::unordered_map<int, std::unordered_map<int, double>> arestas;
} Componente;

class ComponenteConexa {
private:
  std::vector<Componente> componentes;
  std::map<int, bool> C;
  std::map<int, int> T;
  std::map<int, int> F;
  std::map<int, int> A;
  std::map<int, bool> Ct;
  std::map<int, int> Tt;
  std::map<int, int> Ft;
  std::map<int, int> Alt;
  Grafo grafo;
  Grafo transposto;
  void preparaEstruturas();
  void preparaEstruturasGrafoTransposto();
  void DFS();
  void DFSVisita(int v, int &tempo);
  void DFSAdaptado(std::vector<std::pair<int, int>> Fdecrescente);
  void DFSVisitaAdaptado(int v, int &tempo);
  void criaGrafoTransposto(std::map<int, int> At);
  void decrescer(std::vector<std::pair<int, int>> &Fdecrescente);
  void formarComponente(Componente &cmp, int v);

public:
  ComponenteConexa(std::string nomeArquivo);
  ComponenteConexa(Grafo entrada);
  void analisarComponente();
  void exibir();
  std::vector<Componente> getComponentes();
};

#endif
