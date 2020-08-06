#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

#include <iostream>

// Attribution to https://stackoverflow.com/a/3072840/7486328.
namespace otus {
  class FileMarker {
  public:
    using PosType = std::ifstream::pos_type;

    class FailedToReadFile: public std::runtime_error {
    public:
      FailedToReadFile(std::string const &message):
        std::runtime_error(message.c_str()) { }
    };

    FileMarker(std::string const &filename) {
      std::ifstream file { filename };

      if (!file.is_open())
        throw FailedToReadFile("failed to read file \"" + filename + '"');

      /// TODO Test on badness
      linesNum = std::count_if(
          std::istreambuf_iterator<char>(file),
          std::istreambuf_iterator<char>(),
          [this, &file](char ch) {
            if (ch == '\n') {
              eols.push_back(file.tellg());
              return true;
            }
            return false;
          });
    }

    /// TODO Vector of pairs
    std::vector<PosType> mark(size_t blocksNum) {
      //std::cerr << linesNum << std::endl;
      //for (auto i: eols) {
      //  std::cerr << i << ", ";
      //}
      //std::cerr << std::endl;

      std::vector<PosType> result { };
      return result;
    }

    private:
    std::vector<PosType> eols { };
    uint_least32_t linesNum;
  };
}
