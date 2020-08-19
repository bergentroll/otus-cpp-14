#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

#include "utilities.hpp"

namespace otus {
  class FileMarker {
  public:
    using OutputType = std::vector<std::pair<PosType, size_t>>;

    FileMarker(std::string const &filename) {
      std::ifstream file { filename };

      if (!file.is_open())
        throw FailedToReadFile("failed to open file \"" + filename + '"');

      std::for_each(
          std::istreambuf_iterator<char>(file),
          std::istreambuf_iterator<char>(),
          [this, &file, &filename](char ch) {
            if (ch == '\n') eols.push_back(file.tellg());
            if (file.fail())throw  FailedToReadFile(
                "fail while reading file \"" + filename + '"');
          });

      file.close();
    }

    /// Get positions of last \n in blocks.
    OutputType mark(size_t blocksNum) {
      OutputType result { };
      result.reserve(blocksNum);

      auto blockSize { eols.size() / blocksNum };
      auto remainder { eols.size() % blocksNum };

      size_t shift { 0 };
      size_t prevMarkIndex { 0 };

      for (size_t i { 0 }; i < blocksNum; ++i) {
        // To spread remains on blocks.
        if (remainder > 0) {
          --remainder;
          ++shift;
        }

        auto markIndex { (i + 1) * blockSize + shift - 1 };
        auto mark { eols[markIndex] };

        result.push_back(std::make_pair(
              mark,
              markIndex - prevMarkIndex + (i == 0)));

        prevMarkIndex = markIndex;
      }

      return result;
    }

    private:
    std::vector<PosType> eols { };
  };
}
