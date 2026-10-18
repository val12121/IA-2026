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

class AStar
{
public:
  // Constructor m'etodos y funciones
  AStar(Maps &mapa) : mapa_{mapa}
  {
    Node node_open(mapa_.origen().first, mapa_.origen().second);
    node_open.set_g(0);
    node_open.set_h(Heuristic(node_open));
    node_open.set_f(node_open.g() + node_open.h());

    Simulator(node_open);
  }
  // Metodos que representan operaciones esenciales del A*
  void Simulator(Node node_open);
  void ShowMyWay(Node node)
  {
    camino_.push_back(node);
    cout << "(" << node.row() << ", " << node.column() << ")";
    if (node.row() == mapa_.origen().first &&
        node.column() == mapa_.origen().second)
    {
      cout << endl;
      return;
    }
    Node padre = FindNode_(node.row_padre(), node.column_padre());
    cout << " -> ";
    ShowMyWay(padre);
  }

  void ShowMyWay(Node node, ofstream &archivo)
  {
    archivo << "(" << node.row() << "," << node.column() << ")";
    if (node.row() == mapa_.origen().first && node.column() == mapa_.origen().second)
    {
      archivo << endl;
      return;
    }
    Node padre = FindNode_(node.row_padre(), node.column_padre());
    archivo << " -> ";

    ShowMyWay(padre, archivo);
  }

  Node FindNode_(int row_padre, int column_padre)
  {
    for (int i = 0; i < closed_.size(); i++)
    {
      if (closed_[i].row() == row_padre &&
          closed_[i].column() == column_padre)
      {
        return closed_[i];
      }
    }
    return Node(-1, -1);
  }

  Node node_open() { return open_[0]; }
  Node best_node()
  {
    Node best = open_[0];
    for (int i = 0; i < open_.size(); i++)
    {
      if (open_[i].f() < best.f())
      {
        best = open_[i];
      }
    }
    return best;
  }
  vector<Node> Neighbors_(Node node);
  void erase_node(Node node)
  {
    for (int i = 0; i < open_.size(); i++)
    {
      if (open_[i].row() == node.row() &&
          open_[i].column() == node.column())
      {
        open_.erase(open_.begin() + i);
        break;
      }
    }
  }
  void ShowMapPath(ofstream &archivo) {
    for (int i = 0; i < mapa_.rows(); i++) {
      for (int j = 0; j < mapa_.columns(); j++) {
        bool pertenece = false;
        for (int k = 0; k < camino_.size(); k++) {
          if (camino_[k].row() == i && camino_[k].column() == j) {
            pertenece = true;
            break;
          }
        }
        if (pertenece) {
          archivo << "* ";
        } else {
          archivo << mapa_.get(i, j) << " ";
        }
      }
      archivo << endl;
    }
  }
  void ShowNeighbors();
  // Metodos Show
  void ShowOpen();
  void ShowOpen(ofstream &archivo)
  {
    for (int i = 0; i < open_.size(); i++)
    {
      archivo << "("
              << open_[i].row()
              << ","
              << open_[i].column()
              << ")";

      if (i < open_.size() - 1)
      {
        archivo << ", ";
      }
    }
    archivo << endl;
  }
  void ShowClosed();
  void ShowClosed(ofstream &archivo)
  {
    for (int i = 0; i < closed_.size(); i++)
    {
      archivo << "("
              << closed_[i].row()
              << ","
              << closed_[i].column()
              << ")";

      if (i < closed_.size() - 1)
      {
        archivo << ", ";
      }
    }

    archivo << endl;
  }
  int Heuristic(Node node);
  // Booleanos
  bool IsInClosed_(Node node);
  bool IsInOpen_(Node node);

private:
  Maps &mapa_;
  vector<Node> open_;
  vector<Node> closed_;
  vector<Node> neighbors_;
  vector<Node> camino_;
};

#endif