#include "makespace.h"

void Makespan::Mostrar() {
  for (int i = 0; i < tiempos.size(); i++) {
    for (int j = 0; j < tiempos[i].size(); j++) {
      std::cout << tiempos[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

int Makespan::Calcula() {
  int trabajos = semilla_.size();
  int maquinas = tiempos.size();
  vector<vector<int>> nueva = tiempos;

  for (int i = 0; i < maquinas; i++) {
    int maquina_anterior = 0;
    int trabajo_anterior = 0;
    for (int j = 0; j < trabajos; j++) {
      if (i > 0) {
        maquina_anterior = nueva[i - 1][semilla_[j]];
      }
      if (j > 0) {
        trabajo_anterior = nueva[i][semilla_[j - 1]];
      }
      nueva[i][semilla_[j]] = max(trabajo_anterior, maquina_anterior) + nueva[i][semilla_[j]];
    }
  }

  for (int i = 0; i < nueva.size(); i++) {
    for (int j = 0; j < nueva[i].size(); j++) {
      std::cout << nueva[i][j] << " ";
    }
    std::cout << std::endl;
  }
  return nueva[maquinas - 1][semilla_[semilla_.size()]];
}