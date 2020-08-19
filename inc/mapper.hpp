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
        size_t size=0):
    file(filename) {
      if (!file.is_open())
        throw FailedToReadFile("failed to open file \"" + filename + '"');

      file.seekg(begin);
      std::string line;
      tokens.reserve(size);
      while (file.tellg() <= end && std::getline(file, line)) {
        tokens.push_back(line);
        if (file.fail())throw  FailedToReadFile(
            "fail while reading file \"" + filename + '"');
      }
    }

    void operator()() {
      std::sort(tokens.begin(), tokens.end());

      result.reserve(tokens.size());

      for (auto const &token: tokens)
        result.push_back(std::make_pair(token, process(token)));
    }

    std::vector<MappingResult>& getResult() { return result; }

  private:
    std::ifstream file;
    std::vector<std::string> tokens { };
    std::vector<MappingResult> result { };

    static inline std::vector<std::string> process(std::string const &item) {
      std::vector<std::string> result { };
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
