#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

class Node
{
public:
  Node() {}
  Node(int row, int column) : row_{row}, column_{column}, row_padre_{-1}, column_padre_{-1}, g_{0}, h_{0}, f_{0} {}
  
  int row() { return row_; }
  int column() { return column_; }
  
  int g() { return g_; }
  int h() { return h_; }
  int f() { return f_; }
  //Setters
  void set_g(int g) { g_ = g; }
  void set_h(int h) { h_ = h; }
  void set_f(int f) { f_ = f; }
  //Establecer padre
  void set_padre(int row, int column) {
    row_padre_ = row;
    column_padre_ = column;
  }
  //Devolver datos del padre
  int row_padre() {
    return row_padre_;
  }
  int column_padre() {
    return column_padre_;
  }
  friend std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "{" << node.row_ << ", " << node.column_ << "}";
    return os;
  }

private:
  int row_padre_;
  int column_padre_;

  int row_;
  int column_;

  int g_;
  int h_;
  int f_;
};

#endif