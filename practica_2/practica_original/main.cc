#include "makespace.h"
using namespace std;

int main (int argc, char* argv[]) {
  string archivo;
  archivo = "texto1.txt";
  string semilla = "3421";
  Makespan maki (archivo, semilla);
  maki.Mostrar();
  std::cout << "\n";
  int num = maki.Calcula();

  std::cout << "El valor del makespan de la semilla: " << semilla << " -> " << num << std::endl;
}