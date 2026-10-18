#include "maps.h"
#include "node.h"
#include "astar.h"

using namespace std;

int main(int argc, char* argv[]) {
  Maps maps(argv[1]);
  maps.Show();
  AStar astar (maps);
}