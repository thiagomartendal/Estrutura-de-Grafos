#include "ordenacao_topologica.h"

OrdenacaoTopologica::OrdenacaoTopologica(std::string nomeArquivo) {
  grafo = Grafo(TipoGrafo::ORIENTADO);
  grafo.ler(nomeArquivo);
  OrdenacaoTopologica::preparaEstruturas();
}

OrdenacaoTopologica::OrdenacaoTopologica(Grafo entrada) {
  grafo = entrada;
  OrdenacaoTopologica::preparaEstruturas();
}

void OrdenacaoTopologica::preparaEstruturas() {
  for (auto &it: grafo.getVertices()) {
    C[it.first] = false;
    T[it.first] = std::numeric_limits<int>::max();
    F[it.first] = std::numeric_limits<int>::max();
  }
}

void OrdenacaoTopologica::DFS() {
  int tempo = 0;
  for (auto &it: grafo.getVertices()) {
    if (!C[it.first]) {
      OrdenacaoTopologica::DFSVisita(it.first, tempo);
    }
  }
}

void OrdenacaoTopologica::DFSVisita(int v, int &tempo) {
  C[v] = true;
  tempo++;
  T[v] = tempo;
  for (auto &it: grafo.vizinhos(v)) {
    if (!C[it]) {
      OrdenacaoTopologica::DFSVisita(it, tempo);
    } else {
      if ((T[it] != std::numeric_limits<int>::max()) && (F[it] == std::numeric_limits<int>::max())) {
        throw(std::runtime_error("O grafo contém ciclos."));
      }
    }
  }
  tempo++;
  F[v] = tempo;
  O.push_back(v);
}

void OrdenacaoTopologica::ordenar() {
  OrdenacaoTopologica::DFS();
  std::reverse(O.begin(), O.end());
}

void OrdenacaoTopologica::exibir() {
  int i = 0;
  for (int v: O) {
    std::cout << grafo.rotulo(v);
    if (i < (O.size()-1)) {
      std::cout << "->";
    } else {
      std::cout << std::endl;
    }
    i++;
  }
}
