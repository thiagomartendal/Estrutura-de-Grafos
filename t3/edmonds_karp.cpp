#include "edmonds_karp.h"

EdmondsKarp::EdmondsKarp(std::string nomeArquivo, int s, int t) {
  grafo = Grafo(TipoGrafo::ORIENTADO);
  grafo.ler(nomeArquivo);
  this->s = s;
  this->t = t;
  EdmondsKarp::arestasRetorno();
  for (auto &it: grafo.getArestas()) {
    for (auto &it2: it.second) {
      W[it.first][it2.first] = grafo.peso(it.first, it2.first);
    }
  }
}

EdmondsKarp::EdmondsKarp(Grafo entrada, int s, int t) {
  grafo = entrada;
  this->s = s;
  this->t = t;
}

void EdmondsKarp::prepararEstruturas() {
  for (auto &it: grafo.getVertices()) {
    C[it.first] = false;
    A[it.first] = -1;
  }

}

void EdmondsKarp::arestasRetorno() {
  for (auto &it: grafo.getArestas()) {
    for (auto &it2: it.second) {
      grafo.novaAresta(it2.first, it.first, 0.0);
    }
  }
}

std::vector<int> EdmondsKarp::fluxoMaximo() {
  EdmondsKarp::prepararEstruturas();
  C[s] = true;
  std::queue<int> Q;
  Q.push(s);
  while (Q.size() != 0) {
    int u = Q.front();
    Q.pop();
    for (int v: grafo.vizinhos(u)) {
      double Cf = W[u][v];
      if (!C[v] && (Cf > 0.0)) {
        C[v] = true;
        A[v] = u;
        if (v == t) {
          std::vector<int> p;
          p.push_back(t);
          int w = t;
          while (w != s) {
            w = A[w];
            p.push_back(w);
          }
          std::reverse(p.begin(), p.end());
          return p;
        }
        Q.push(v);
      }
    }
  }
  return std::vector<int>();
}

void EdmondsKarp::fordFulkerson() {
  double f = 0.0;
  std::vector<int> p = EdmondsKarp::fluxoMaximo();
  while (p.size() > 0) {
    double c = std::numeric_limits<double>::max();
    for (int i = 0; i < p.size()-1; i++) {
      if (c > W[p[i]][p[i+1]]) {
        c = W[p[i]][p[i+1]];
      }
    }
    for (int i = 0; i < p.size()-1; i++) {
      W[p[i]][p[i+1]] -= c;
      W[p[i+1]][p[i]] += c;
    }
    f += c;
    p = EdmondsKarp::fluxoMaximo();
  }
  std::cout << "Fluxo Máximo: " << f << std::endl;
}
