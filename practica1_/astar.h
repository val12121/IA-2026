#ifndef AStart_H
#define AStart_H

#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <sstream>
#include <fstream>
#include <vector>
#include "maps.h"
#include "node.h"

class AStart {
  public:
  //Constructor m'etodos y funciones
    AStart(Maps& mapa) : mapa_{mapa} {
      Node node_open(mapa_.origen().first, mapa_.origen().second);
      node_open.set_g(0);
      node_open.set_h(Heuristic(node_open));
      node_open.set_f(node_open.g() + node_open.h());
      open_.push_back(node_open);
      Neighbors_(node_open);
      ShowNeighbors();
    }
    //Metodos que representan operaciones esenciales del A*
    Node node_open() { return open_[0]; }
    vector<Node> Neighbors_(Node node) {
      vector<Node> result;
      //Izquierda
      if (0 < node.column()) {
        Node izquierda (node.row(), node.column() - 1);
        result.push_back(izquierda);
      } 
      //derecha
      if (mapa_.columns() - 1 > node.column()) {
        Node derecha (node.row(), node.column() + 1);
        result.push_back(derecha);
      } 
      //arriba
      if (0 < node.row()) {
        Node arriba (node.row() - 1, node.column());
        result.push_back(arriba);
      } 
      //abajo
      if (mapa_.rows() - 1 > node.row()) {
        Node abajo (node.row() + 1, node.column());
        result.push_back(abajo);
      }
      return result;
    }
    void ShowNeighbors() {
      for (int i = 0; i < neighbors_.size(); i++) {
        cout << "Vecino: " << neighbors_[i] << "\n";
      }
    }
    //Metodos Show
    void ShowOpen() {
      std::cout << "Se muestran los nodos abiertos: \n";
      for (int i = 0; i < open_.size(); i++) {
        std::cout << "{" << open_[i].row() << ", " << open_[i].column() << "} ";
      }
      cout << endl;
    }
    void ShowClosed() {
      std::cout << "Se muestran los nodos cerrados: \n";
      for (int i = 0; i < closed_.size(); i++) {
        std::cout << "{" << closed_[i].row() << ", " << closed_[i].column() << "} ";
      }
      cout << endl;
    }
    int Heuristic(Node node) {
      return (2 * (abs(node.row() - mapa_.destino().first) + 
      abs(node.column() - mapa_.destino().second)));
    }
    //

  private:
    Maps& mapa_;
    vector<Node> open_;
    vector<Node> closed_;
    vector<Node> neighbors_;;
};

#endif