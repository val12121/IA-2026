#ifndef AStar_H
#define AStar_H

#include <iostream>
#include <cmath>
#include <cstdlib> 
#include <sstream>
#include <fstream>
#include <vector>
#include "maps.h"
#include "node.h"

class AStar {
  public:
  //Constructor m'etodos y funciones
    AStar(Maps& mapa) : mapa_{mapa} {
      Node node_open(mapa_.origen().first, mapa_.origen().second);
      node_open.set_g(0);
      node_open.set_h(Heuristic(node_open));
      node_open.set_f(node_open.g() + node_open.h());
      
      open_.push_back(node_open);
      neighbors_ = Neighbors_(node_open);
      
      for (int i = 0; i < neighbors_.size(); i++) {
        int g = node_open.g() + mapa_.get(neighbors_[i].row(), neighbors_[i].column());
        int h = Heuristic(neighbors_[i]);
        neighbors_[i].set(g, h);
        neighbors_[i].set_padre(node_open.row(), node_open.column());
      }
      ShowNeighbors();
    }
    //Metodos que representan operaciones esenciales del A*
    Node node_open() { return open_[0]; }
    vector<Node> Neighbors_(Node node) ;

    void ShowNeighbors() ;
    //Metodos Show
    void ShowOpen() ;
    void ShowClosed() ;
    int Heuristic(Node node) ;

  private:
    Maps& mapa_;
    vector<Node> open_;
    vector<Node> closed_;
    vector<Node> neighbors_;;
};

#endif