#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <iostream>

namespace otus {
  class Reducer {
  public:
    using ItemType = std::pair<std::string, std::vector<std::string>>;
    Reducer (std::vector<ItemType> const &data):
      data(data) { }

    // TODO Duplicates
    void run() const {
      size_t globalIndex { };

      for (std::vector<ItemType>::size_type i { }; i < data.size() - 1; ++i) {
        // TODO Bounding
        size_t localIndex { };
        auto const &prefixes { data[i].second };
        auto const &nextPrefixes { data[i + 1].second };

        while (prefixes[localIndex] == nextPrefixes[localIndex]) {
          ++localIndex;
        }

        auto resultIndex { std::max(globalIndex, localIndex) };

        std::cerr << data[i].first << ": " << data[i].second[resultIndex] << std::endl;

        globalIndex = localIndex;
      }
      // TODO Last item.
    }

  private:
    // TODO Reference.
    std::vector<ItemType> data;
  };
}
