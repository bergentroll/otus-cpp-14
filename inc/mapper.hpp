#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <iostream>

#include "aliases.hpp"

namespace otus {
  class Mapper {
  public:
    using MappingResult = std::vector<std::string>;

    Mapper(std::string const &filename, PosType begin, PosType end):
    file(filename) {
      // TODO Errors handling.
      file.seekg(begin);
      std::string line;
      while (file.tellg() <= end && std::getline(file, line)) {
        tokens.push_back(line);
      }
      result.reserve(tokens.size());
    }

    void run() {
      for (auto const &token: tokens)
        result.push_back(process(token));
    }

    std::vector<MappingResult>& getResult() { return result; }

  private:
    std::ifstream file;
    // TODO Reserve.
    std::vector<std::string> tokens { };
    std::vector<MappingResult> result { };

    static inline MappingResult process(std::string const &item) {
      MappingResult result { };
      result.reserve(item.length());

      std::string buf { };
      for (auto ch: item) {
        buf += ch;
        result.push_back(buf);
      }

      return result;
    }
  };
}
