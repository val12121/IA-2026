#include "astar.h"

vector<Node> AStar::Neighbors_(Node node)
{
  vector<Node> result;
  // Izquierda
  if (0 < node.column()) {
    Node izquierda(node.row(), node.column() - 1);
    if (mapa_.get(izquierda.row(), izquierda.column()) != -1) {
      result.push_back(izquierda);
    }
  }
  // derecha
  if (mapa_.columns() - 1 > node.column()) {
    Node derecha(node.row(), node.column() + 1);
    if (mapa_.get(derecha.row(), derecha.column()) != -1) {
      result.push_back(derecha);
    }
  }
  // arriba
  if (mapa_.rows() - 1 > node.row()) {
    Node arriba(node.row() - 1, node.column());
    if (mapa_.get(arriba.row(), arriba.column()) != -1) {
      result.push_back(arriba);
    }
  }
  // abajo
  if (0 < node.row()) {
    Node abajo(node.row() + 1, node.column());
    if (mapa_.get(abajo.row(), abajo.column()) != -1) {
      result.push_back(abajo);
    }
  }
  return result;
}

void AStar::ShowNeighbors() {
  for (int i = 0; i < neighbors_.size(); i++) {
    cout << "Vecino: " << neighbors_[i] << "\n"
    << " | g: " << neighbors_[i].g()
    << " | h: " << neighbors_[i].h()
    << " | f: " << neighbors_[i].f()
    << " | padre: {" << neighbors_[i].row_padre()
    << ", " << neighbors_[i].column_padre() << "}\n";
  }
}

void AStar::ShowOpen() {
  std::cout << "Se muestran los nodos abiertos: \n";
  for (int i = 0; i < open_.size(); i++) {
    std::cout << "{" << open_[i].row() << ", " << open_[i].column() << "} ";
  }
  cout << endl;
}

void AStar::ShowClosed() {
  std::cout << "Se muestran los nodos cerrados: \n";
  for (int i = 0; i < closed_.size(); i++) {
    std::cout << "{" << closed_[i].row() << ", " << closed_[i].column() << "} ";
  }
  cout << endl;
}

int AStar::Heuristic(Node node) {
  return (2 * (abs(node.row() - mapa_.destino().first) + 
  abs(node.column() - mapa_.destino().second)));
}