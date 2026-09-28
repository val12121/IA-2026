#ifndef MAPS_H
#define MAPS_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
class Maps{
  public:
    Maps() {}
    Maps(std::string file_in) {
      std::ifstream file(file_in);
      if (file.is_open()) {
        std::string primera_linea;
        while (std::getline(file, primera_linea)) {
          mapa_.push_back(vector<int>{});
          std::stringstream ss(primera_linea);
          std::string palabra;
          while (ss >> palabra) {
            mapa_.back().push_back(stoi(palabra));
          }  
        }
      }
      for (int i = 0; i < mapa_.size(); i++) {
        for (int j = 0; j < mapa_[i].size(); j++) {
          if (mapa_[i][j] == 0) {
            origen_.first = i;
            origen_.second = j;
          }
          if (mapa_[i][j] == 10) {
            destino_.first = i;
            destino_.second = j;
          }
        }
      }
    }
    void Show() {
      for (int i = 0; i < mapa_.size(); i++) {
        for (int j = 0; j < mapa_[i].size(); j++) {
          cout << mapa_[i][j] << " ";
        }
        cout << endl;
      }
    }
    int rows() { return mapa_.size(); }
    int columns() { return mapa_[0].size(); }
    int get(int row, int column) {
      return mapa_[row][column];
    }
    
    pair<int, int> origen() {
      return origen_;
    }
    pair<int, int> destino() {
      return destino_;
    }
  private:
    vector<vector<int>> mapa_;
    std::pair<int, int> origen_;
    std::pair<int, int> destino_;
};

#endif