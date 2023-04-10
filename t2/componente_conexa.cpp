#include "componente_conexa.h"

ComponenteConexa::ComponenteConexa(std::string nomeArquivo) {
  grafo = Grafo(TipoGrafo::ORIENTADO);
  grafo.ler(nomeArquivo);
  ComponenteConexa::preparaEstruturas();
}

ComponenteConexa::ComponenteConexa(Grafo entrada) {
  grafo = entrada;
  ComponenteConexa::preparaEstruturas();
}

void ComponenteConexa::preparaEstruturas() {
  for (auto &it: grafo.getVertices()) {
    C[it.first] = false;
    T[it.first] = std::numeric_limits<int>::max();
    F[it.first] = std::numeric_limits<int>::max();
    A[it.first] = -1;
  }
}

void ComponenteConexa::preparaEstruturasGrafoTransposto() {
  for (auto &it: transposto.getVertices()) {
    Ct[it.first] = false;
    Tt[it.first] = std::numeric_limits<int>::max();
    Ft[it.first] = std::numeric_limits<int>::max();
    Alt[it.first] = -1;
  }
}

void ComponenteConexa::DFS() {
  int tempo = 0;
  for (auto &it: grafo.getVertices()) {
    if (!C[it.first]) {
      ComponenteConexa::DFSVisita(it.first, tempo);
    }
  }
}

void ComponenteConexa::DFSVisita(int v, int &tempo) {
  C[v] = true;
  tempo++;
  T[v] = tempo;
  for (auto &it: grafo.vizinhos(v)) {
    if (!C[it]) {
      A[it] = v;
      ComponenteConexa::DFSVisita(it, tempo);
    }
  }
  tempo++;
  F[v] = tempo;
}

void ComponenteConexa::DFSAdaptado(std::vector<std::pair<int, int>> Fdecrescente) {
  int tempo = 0;
  for (auto &it: Fdecrescente) {
    if (!Ct[it.first]) {
      ComponenteConexa::DFSVisitaAdaptado(it.first, tempo);
    }
  }
}

void ComponenteConexa::DFSVisitaAdaptado(int v, int &tempo) {
  Ct[v] = true;
  tempo++;
  Tt[v] = tempo;
  for (auto &it: transposto.vizinhos(v)) {
    if (!Ct[it]) {
      Alt[it] = v;
      ComponenteConexa::DFSVisitaAdaptado(it, tempo);
    }
  }
  tempo++;
  Ft[v] = tempo;
}

void ComponenteConexa::criaGrafoTransposto(std::map<int, int> At) {
  for (auto &it: grafo.getVertices()) {
    transposto.novoVertice(it.first, it.second);
  }
  for (auto &it: grafo.getArestas()) {
    for (auto &it2: it.second) {
      transposto.novaAresta(it2.first, it.first, it2.second);
    }
  }
}

bool cmp(std::pair<int, int> &a, std::pair<int, int> &b) {
  return a.second > b.second;
}

void ComponenteConexa::decrescer(std::vector<std::pair<int, int>> &Fdecrescente) {
  for (auto& it : F) {
    Fdecrescente.push_back(it);
  }
  std::sort(Fdecrescente.begin(), Fdecrescente.end(), cmp);
}

void ComponenteConexa::formarComponente(Componente &cmp, int v) {
  cmp.arestas[v] = grafo.getArestas()[v];
  cmp.vertices.insert(v);
  for (auto &it: transposto.getVertices()) {
    if (Alt[it.first] == v) {
      ComponenteConexa::formarComponente(cmp, it.first);
      break;
    }
  }
}

void ComponenteConexa::analisarComponente() {
  ComponenteConexa::DFS();
  std::map<int, int> At;
  for (auto &it: A) {
    At[it.second] = it.first;
  }
  transposto = Grafo(TipoGrafo::ORIENTADO);
  std::vector<std::pair<int, int>> Fdecrescente;
  ComponenteConexa::criaGrafoTransposto(At);
  ComponenteConexa::preparaEstruturasGrafoTransposto();
  ComponenteConexa::decrescer(Fdecrescente);
  ComponenteConexa::DFSAdaptado(Fdecrescente);
  for (auto &it: transposto.getVertices()) {
    if (Alt[it.first] == -1) {
      Componente cmp;
      ComponenteConexa::formarComponente(cmp, it.first);
      componentes.push_back(cmp);
    }
  }
  for (Componente &c: componentes) {
    for (auto &it: c.arestas) {
      for (auto &it2: it.second) {
        if (c.vertices.find(it2.first) == c.vertices.end()) {
          c.arestas[it.first].erase(it2.first);
        }
      }
    }
  }
}

void ComponenteConexa::exibir() {
  for (Componente c: componentes) {
    int i = 0;
    for (int v: c.vertices) {
      std::cout << v;
      if (i < (c.vertices.size()-1)) {
        std::cout << ",";
      }
      i++;
    }
    std::cout << std::endl;
  }
}

std::vector<Componente> ComponenteConexa::getComponentes() {
  return componentes;
}
