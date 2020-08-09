#pragma once

#include <fstream>
#include <string>

#include <iostream>

namespace otus {
  using PosType = std::ifstream::pos_type;

  class Mapper {
  public:
    Mapper(std::string const &filename, PosType begin, PosType end) { }

    void Run() {
      std::cerr << "OLOLO\n";
    }

  private:
  };
}
