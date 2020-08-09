#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <iostream>

#include "aliases.hpp"

namespace otus {
  class Mapper {
  public:
    Mapper(std::string const &filename, PosType begin, PosType end):
    file(filename) {
      // TODO Errors handling.
      file.seekg(begin);
      std::string line;
      while (file.tellg() <= end && std::getline(file, line)) {
        tokens.push_back(line);
      }
    }

    void Run() {
      std::string s { };
      file >> s;
      //std::cerr << s << std::endl;
    }

  private:
    std::ifstream file;
    // TODO Reserve.
    std::vector<std::string> tokens { };
  };
}
