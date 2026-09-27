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
    }
    void Show() {
      for (int i = 0; i < mapa_[0].size(); i++) {
        for (int j = 0; j < mapa_.size(); j++) {
          cout << mapa_[i][j] << " ";
        }
        cout << endl;
      }
    }
    int size_x() { return mapa_.size(); }
    int size_y() { return mapa_[0].size(); }
  private:
    vector<vector<int>> mapa_;
};