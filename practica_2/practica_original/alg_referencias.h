#ifndef REFERENCIAS_H
#define REFERENCIAS_H

#include "makespace.h"

class Referencias {
  public:
    Referencias () {}
    Referencias (int budget, const int option = 0) : budget_(budget), option_(option) {}
    
  private:
    int budget_ = 50000;
    int option_;
};

#endif