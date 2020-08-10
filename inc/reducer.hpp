#pragma once

#include <fstream>
#include <string>
#include <vector>

#include <iostream>

namespace otus {
  class Reducer {
  public:
    using ItemType = std::pair<std::string, std::vector<std::string>>;
    Reducer (std::vector<ItemType> &data):
      data(data) { }

    // TODO Duplicates
    void run() {
      size_t index { };

      for (std::vector<ItemType>::size_type i { }; i < data.size() - 1; ++i) {
        // TODO Bounding
        size_t newIndex { };
        while (data[i].second[newIndex] == data[i + 1].second[newIndex]) {
          ++newIndex;
        }
        auto resultIndex { std::max(index, newIndex) };
        index = newIndex;
        std::cerr << data[i].first << ": " << data[i].second[resultIndex] << std::endl;
      }
    }

  private:
    // TODO Reference.
    std::vector<ItemType> data;
  };
}
