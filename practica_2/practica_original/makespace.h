#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_set>

using namespace std;

class Makespan {
  public:
    Makespan() {};
    Makespan(std::string archivo_entrada, string semilla) {
      std::ifstream archivo(archivo_entrada);
      if (archivo.is_open()) {
        std::string primera_linea;
        while(getline(archivo, primera_linea)) {
          tiempos.push_back(vector<int>{});
          std::stringstream ss(primera_linea);
          std::string palabra;
          while (ss >> palabra) {
            tiempos.back().push_back(stoi(palabra));
          }
        }
      }
      for (int i = 0; i < semilla.size(); i++) {
        semilla_.push_back(int(semilla[i] - '0') - 1);
      }
    }
    //T1 (Primera parte de la práctica)
    void Mostrar() ;
    int Calcula() ;
    //T2 (Evaluamos si la semilla es valida)
    bool SemillaValida() {
      std::unordered_set<int> vector_aux(semilla_.begin(), semilla_.end()); 
      return vector_aux.size() < semilla_.size();
    }

  private:
    vector<vector<int>> tiempos;
    vector<int> semilla_;
    int presupuesto;
};