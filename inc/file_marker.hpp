#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <stdexcept>
#include <vector>

#include "aliases.hpp"

namespace otus {
  class FileMarker {
  public:
    class FailedToReadFile: public std::runtime_error {
    public:
      FailedToReadFile(std::string const &message):
        std::runtime_error(message.c_str()) { }
    };

    FileMarker(std::string const &filename) {
      std::ifstream file { filename };

      if (!file.is_open())
        throw FailedToReadFile("failed to read file \"" + filename + '"');

      /// TODO Test on badness.
      std::for_each(
          std::istreambuf_iterator<char>(file),
          std::istreambuf_iterator<char>(),
          [this, &file](char ch) {
            if (ch == '\n') eols.push_back(file.tellg());
          });

      file.close();
    }

    /** @brief Get positions of last \n in blocks.
     *
     * TODO Vector of pairs
     */
    std::vector<PosType> mark(size_t blocksNum) {
      std::vector<PosType> result { };
      result.reserve(blocksNum);

      auto blockSize { eols.size() / blocksNum };
      auto remainder { eols.size() % blocksNum };

      size_t shift { 0 };

      for (size_t i { }; i < blocksNum; ++i) {
        // To spread remains to blocks.
        if (remainder > 0) {
          --remainder;
          ++shift;
        }

        auto mark { eols[(i + 1) * blockSize + shift - 1] };

        result.push_back(mark);
      }

      return result;
    }

    private:
    std::vector<PosType> eols { };
  };
}
