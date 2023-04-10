#ifndef VERTICE_H
#define VERTICE_H

#include <string>

typedef struct Vertice {
  int id;
  std::string nome;
} Vertice;

inline bool operator==(const Vertice &v1, const Vertice &v2) {
  if (v1.nome == v2.nome) {
    return true;
  }
  return false;
}

class HashVertice {
public:
    size_t operator()(const Vertice& v) const {
        return v.id;
    }
};

#endif
