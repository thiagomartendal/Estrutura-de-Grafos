#include <iostream>
#include "grafo.h"
#include "t1/busca.h"
#include "t1/formar_ciclo.h"
#include "t1/dijkstra.h"
#include "t1/floyd_warshall.h"
#include "t2/componente_conexa.h"
#include "t2/ordenacao_topologica.h"
#include "t2/kruskal.h"
#include "t3/edmonds_karp.h"
#include "t3/hopcroft_karp.h"

int main() {
  /*std::cout << "Testes na estrutura de Grafo - Grafo 1" << std::endl;
  Grafo grafo;
  grafo.novoVertice(1, "v1");
  grafo.novoVertice(2, "v2");
  grafo.novoVertice(3, "v3");
  grafo.novoVertice(4, "v4");
  grafo.novaAresta(1, 2, 4.5);
  grafo.novaAresta(4, 1, 8.0);
  for (auto &it: grafo.getVertices()) {
    std::cout << it.first << " " << it.second << std::endl;
  }
  if (grafo.existeVertice(1)) {
    std::cout << "v1 existe." << std::endl;
  }
  std::cout << "Total de vértices: " << grafo.qtdVertices() << std::endl;
  std::cout << "Grau de v1: " << grafo.grau(1) << std::endl;
  for (auto &it: grafo.getArestas()) {
    for (auto &it2: it.second) {
      std::cout << "{" << it.first << "," << grafo.rotulo(it.first) << "} {" << it2.first << "," << grafo.rotulo(it2.first) << "} " << it2.second << std::endl;
    }
  }
  std::cout << "Total de arestas: " << grafo.qtdArestas() << std::endl;
  for (auto &it: grafo.vizinhos(1)) {
    std::cout << "Vizinho de v1: " << it << std::endl;
  }
  if (grafo.haAresta(1, 2)) {
    std::cout << "Há aresta entre v1 e v2." << std::endl;
  }
  std::cout << "Peso da aresta entre v1 e v2: " << grafo.peso(1, 2) << std::endl;
  std::cout << "---------------" << std::endl;
  std::cout << "Testes na estrutura de Grafo - Grafo 2" << std::endl;
  Grafo grafo2;
  grafo2.ler("arquivo_grafo");
  for (auto &it: grafo2.getVertices()) {
    std::cout << it.first << " " << it.second << std::endl;
  }
  for (auto &it: grafo2.getArestas()) {
    for (auto &it2: it.second) {
      std::cout << "{" << it.first << "," << grafo.rotulo(it.first) << "} {" << it2.first << "," << grafo.rotulo(it2.first) << "} " << it2.second << std::endl;
    }
  }
  std::cout << "Peso da aresta entre a2 e a4: " << grafo2.peso(2, 4) << std::endl;
  std::cout << "Peso da aresta entre a2 e a3: " << grafo2.peso(2, 3) << std::endl;
  std::cout << "---------------" << std::endl;
  std::cout << "Busca em largura no arquivo_grafo" << std::endl;
  Busca b = Busca("arquivo_grafo", 0);
  b.buscar();
  b.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca em largura no arquivo_grafo2" << std::endl;
  Busca b1 = Busca("arquivo_grafo2", 0);
  b1.buscar();
  b1.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca de ciclo Euleriano para o arquivo_grafo3" << std::endl;
  FormarCiclo ciclo1 = FormarCiclo("arquivo_grafo3", 0);
  ciclo1.buscar();
  ciclo1.exibirCiclo();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca de ciclo Euleriano para o arquivo_grafo4" << std::endl;
  FormarCiclo ciclo2 = FormarCiclo("arquivo_grafo4", 0);
  ciclo2.buscar();
  ciclo2.exibirCiclo();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca de ciclo Euleriano para o arquivo_grafo2" << std::endl;
  FormarCiclo ciclo3 = FormarCiclo("arquivo_grafo2", 0);
  ciclo3.buscar();
  ciclo3.exibirCiclo();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca de ciclo Euleriano para o arquivo_grafo6" << std::endl;
  FormarCiclo ciclo4 = FormarCiclo("arquivo_grafo6", 0);
  ciclo4.buscar();
  ciclo4.exibirCiclo();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca de ciclo Euleriano para o arquivo_grafo7" << std::endl;
  FormarCiclo ciclo5 = FormarCiclo("arquivo_grafo7", 0);
  ciclo5.buscar();
  ciclo5.exibirCiclo();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca de ciclo Euleriano para o arquivo_grafo10" << std::endl;
  FormarCiclo ciclo6 = FormarCiclo("arquivo_grafo10", 1);
  ciclo6.buscar();
  ciclo6.exibirCiclo();
  std::cout << "---------------" << std::endl;
  std::cout << "Busca de ciclo Euleriano para o arquivo_grafo11" << std::endl;
  FormarCiclo ciclo7 = FormarCiclo("arquivo_grafo11");
  ciclo7.buscar();
  ciclo7.exibirCiclo();
  std::cout << "---------------" << std::endl;
  std::cout << "Algoritmo de Dijkstra para o arquivo_grafo5" << std::endl;
  Dijkstra d = Dijkstra("arquivo_grafo5", 0);
  d.buscarCaminhosMinimos();
  d.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Algoritmo de Dijkstra para o arquivo_grafo2" << std::endl;
  Dijkstra d1 = Dijkstra("arquivo_grafo2", 0);
  d1.buscarCaminhosMinimos();
  d1.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Algoritmo de Dijkstra para o arquivo_grafo8" << std::endl;
  Dijkstra d2 = Dijkstra("arquivo_grafo8", 1);
  d2.buscarCaminhosMinimos();
  d2.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Algoritmo de Dijkstra para o arquivo_grafo9" << std::endl;
  Dijkstra d3 = Dijkstra("arquivo_grafo9", 1);
  d3.buscarCaminhosMinimos();
  d3.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Algoritmo de Floyd-Warshall para o arquivo_grafo5" << std::endl;
  FloydWarshall f = FloydWarshall("arquivo_grafo5");
  f.calcularCaminhos();
  f.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Algoritmo de Floyd-Warshall para o arquivo_grafo9" << std::endl;
  FloydWarshall f1 = FloydWarshall("arquivo_grafo9");
  f1.calcularCaminhos();
  f1.exibir();*/
  /*std::cout << "Testes na estrutura de Grafo - Grafo 3" << std::endl;
  Grafo grafo3 = Grafo(TipoGrafo::ORIENTADO);
  grafo3.novoVertice(1, "a");
  grafo3.novoVertice(2, "b");
  grafo3.novoVertice(3, "c");
  grafo3.novoVertice(4, "d");
  grafo3.novoVertice(5, "e");
  grafo3.novaAresta(1, 2, 1.0);
  grafo3.novaAresta(1, 3, 1.0);
  grafo3.novaAresta(2, 4, 1.0);
  grafo3.novaAresta(3, 4, 1.0);
  grafo3.novaAresta(3, 5, 1.0);
  grafo3.novaAresta(4, 5, 1.0);
  for (auto &it: grafo3.getVertices()) {
    std::cout << it.first << " " << it.second << std::endl;
  }
  for (auto &it: grafo3.getArestas()) {
    for (auto &it2: it.second) {
      std::cout << "{" << it.first << "," << grafo3.rotulo(it.first) << "} {" << it2.first << "," << grafo3.rotulo(it2.first) << "} " << it2.second << std::endl;
    }
  }
  std::cout << "---------------" << std::endl;
  std::cout << "Componente conexa arquivo_grafo19" << std::endl;
  ComponenteConexa c1 = ComponenteConexa("arquivo_grafo19");
  c1.analisarComponente();
  c1.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Componente conexa arquivo_grafo12" << std::endl;
  ComponenteConexa c2 = ComponenteConexa("arquivo_grafo12");
  c2.analisarComponente();
  c2.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Componente conexa arquivo_grafo13" << std::endl;
  ComponenteConexa c3 = ComponenteConexa("arquivo_grafo13");
  c3.analisarComponente();
  c3.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Componente conexa arquivo_grafo15" << std::endl;
  ComponenteConexa c4 = ComponenteConexa("arquivo_grafo15");
  c4.analisarComponente();
  c4.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Componente conexa arquivo_grafo16" << std::endl;
  ComponenteConexa c5 = ComponenteConexa("arquivo_grafo16");
  c5.analisarComponente();
  c5.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Ordenação topológica arquivo_grafo14" << std::endl;
  OrdenacaoTopologica o1 = OrdenacaoTopologica("arquivo_grafo14");
  o1.ordenar();
  o1.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Arvore Geradora Minima arquivo_grafo17" << std::endl;
  Kruskal k1 = Kruskal("arquivo_grafo17");
  k1.AGM();
  k1.exibir();
  std::cout << "---------------" << std::endl;
  std::cout << "Arvore Geradora Minima arquivo_grafo18" << std::endl;
  Kruskal k2 = Kruskal("arquivo_grafo18");
  k2.AGM();
  k2.exibir();*/
  std::cout << "Edmonds-Karp arquivo_grafo20" << std::endl;
  EdmondsKarp e1 = EdmondsKarp("arquivo_grafo20", 0, 5);
  e1.fordFulkerson();
  // std::cout << "---------------" << std::endl;
  // std::cout << "Edmonds-Karp arquivo_grafo21" << std::endl;
  // EdmondsKarp e2 = EdmondsKarp("arquivo_grafo21", 1, 4096);
  // e2.fordFulkerson();
  std::cout << "---------------" << std::endl;
  std::cout << "Hopcroft-Karp arquivo_grafo22" << std::endl;
  HopcroftKarp h1 = HopcroftKarp("arquivo_grafo22");
  std::cout << "---------------" << std::endl;
  return 0;
}
