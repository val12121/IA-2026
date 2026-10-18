#include "astar.h"

void AStar::Simulator(Node node_open)
{
  ofstream archivo("salida.txt");

  int iteracion = 0;
  int g;
  for (int i = 0; i < 10; i++)
  {
    open_.clear();
    closed_.clear();
    camino_.clear();
    neighbors_.clear();
    // Mostrar estado actual
    open_.push_back(node_open);
    while (!open_.empty())
    {
      cout << "Iteración " << iteracion << endl;
      cout << "-----------" << endl;
      archivo << "Iteración " << iteracion << endl;
      archivo << "-----------" << endl;
      cout << "Abiertos = ";
      archivo << "Abiertos = ";
      ShowOpen();
      ShowOpen(archivo);
      cout << "Cerrados = ";
      archivo << "Cerrados = ";
      ShowClosed();
      ShowClosed(archivo);
      cout << "------------------------" << endl;
      archivo << "------------------------" << endl;
      Node actual = best_node();
      erase_node(actual);
      closed_.push_back(actual);

      if (actual.row() == mapa_.destino().first &&
          actual.column() == mapa_.destino().second)
      {
        ShowMyWay(actual);
        ShowMyWay(actual, archivo);
        ShowMapPath(archivo);
        g = actual.g();
        break;
      }
      neighbors_ = Neighbors_(actual);
      iteracion++;
    }
    cout << "Coste del camino = " << g << endl;
    archivo << "Coste del camino = " << g << endl;
    iteracion = 0;
  }
}

void AStar::ShowMyWay(Node node)
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

void AStar::ShowMyWay(Node node, ofstream &archivo)
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

vector<Node> AStar::Neighbors_(Node node)
{
  vector<Node> result;
  // arriba
  if (node.row() > 0)
  {
    Node arriba(node.row() - 1, node.column());
    if (mapa_.get(arriba.row(), arriba.column()) != -1)
    {
      result.push_back(arriba);
    }
  }
  // abajo
  if (node.row() < mapa_.rows() - 1)
  {
    Node abajo(node.row() + 1, node.column());
    if (mapa_.get(abajo.row(), abajo.column()) != -1)
    {
      result.push_back(abajo);
    }
  }
  // Izquierda
  if (0 < node.column())
  {
    Node izquierda(node.row(), node.column() - 1);
    if (mapa_.get(izquierda.row(), izquierda.column()) != -1)
    {
      result.push_back(izquierda);
    }
  }
  // derecha
  if (mapa_.columns() - 1 > node.column())
  {
    Node derecha(node.row(), node.column() + 1);
    if (mapa_.get(derecha.row(), derecha.column()) != -1)
    {
      result.push_back(derecha);
    }
  }

  neighbors_ = result;

  for (int i = 0; i < neighbors_.size(); i++)
  {
    if (IsInClosed_(neighbors_[i]))
    {
      continue;
    }
    int coste = mapa_.get(neighbors_[i].row(), neighbors_[i].column());
    if (neighbors_[i].row() == mapa_.destino().first &&
        neighbors_[i].column() == mapa_.destino().second)
    {
      coste = 2;
    }

    int g = node.g() + coste;
    int h = Heuristic(neighbors_[i]);
    neighbors_[i].set(g, h);
    neighbors_[i].set_padre(node.row(), node.column());
    if (!IsInOpen_(neighbors_[i]))
    {
      open_.push_back(neighbors_[i]);
    }
  }
  return neighbors_;
}

void AStar::ShowNeighbors()
{
  for (int i = 0; i < neighbors_.size(); i++)
  {
    cout << "Vecino: " << neighbors_[i] << "\n"
         << " | g: " << neighbors_[i].g()
         << " | h: " << neighbors_[i].h()
         << " | f: " << neighbors_[i].f()
         << " | padre: {" << neighbors_[i].row_padre()
         << ", " << neighbors_[i].column_padre() << "}\n";
  }
}

void AStar::ShowOpen()
{
  std::cout << "Se muestran los nodos abiertos: \n";
  for (int i = 0; i < open_.size(); i++)
  {
    std::cout << "{" << open_[i].row() << ", " << open_[i].column() << "} ";
  }
  cout << endl;
}

void AStar::ShowClosed()
{
  std::cout << "Se muestran los nodos cerrados: \n";
  for (int i = 0; i < closed_.size(); i++)
  {
    std::cout << "{" << closed_[i].row() << ", " << closed_[i].column() << "} ";
  }
  cout << endl;
}

int AStar::Heuristic(Node node)
{
  return (2 * (abs(node.row() - mapa_.destino().first) +
               abs(node.column() - mapa_.destino().second)));
}

bool AStar::IsInClosed_(Node node)
{
  for (int i = 0; i < closed_.size(); i++)
  {
    if (closed_[i].row() == node.row() && closed_[i].column() == node.column())
    {
      return true;
    }
  }
  return false;
}
bool AStar::IsInOpen_(Node node)
{
  for (int i = 0; i < open_.size(); i++)
  {
    if (open_[i].row() == node.row() && open_[i].column() == node.column())
    {
      return true;
    }
  }
  return false;
}