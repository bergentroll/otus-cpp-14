#pragma once

#include <algorithm>
#include <fstream>
#include <string>
#include <utility>
#include <vector>

#include "utilities.hpp"

namespace otus {
  class Mapper {
  public:
    using MappingResult = std::pair<std::string, std::vector<std::string>>;

    Mapper(
        std::string const &filename,
        PosType begin,
        PosType end,
        size_t size=0);

    void operator()();

    std::vector<MappingResult>& getResult() { return result; }

  private:
    std::ifstream file;
    std::vector<std::string> tokens { };
    std::vector<MappingResult> result { };

    static std::vector<std::string> process(std::string const &item);
  };
}
