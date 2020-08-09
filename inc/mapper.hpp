#pragma once

#include <fstream>
#include <string>

#include <iostream>

#include "aliases.hpp"

namespace otus {
  class Mapper {
  public:
    Mapper(std::string const &filename, PosType begin, PosType end):
    file(filename) {
      // TODO Errors handling.
      file.seekg(begin);
      //std::cerr << begin << ": " << end << std:: endl;
    }

    void Run() {
      std::string s { };
      file >> s;
      std::cerr << s << std::endl;
    }

  private:
    std::ifstream file;
  };
}
