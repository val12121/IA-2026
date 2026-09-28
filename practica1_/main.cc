#include "maps.h"
#include "node.h"
#include "astar.h"

using namespace std;

int main(int argc, char* argv[]) {
  Maps maps(argv[1]);
  maps.Show();
  AStart astar (maps);

  cout << "Origen: " << maps.origen().first << ", "
  << maps.origen().second << endl;

  cout << "Destino: " << maps.destino().first << ", "
  << maps.destino().second << endl;

  astar.ShowOpen();
  cout << astar.Heuristic(astar.node_open()) << endl;
}