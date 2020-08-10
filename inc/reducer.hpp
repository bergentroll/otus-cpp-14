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

    void run() const {
      size_t globalIndex { };

      for (std::vector<ItemType>::size_type i { }; i < data.size() - 1; ++i) {
        size_t localIndex { };
        auto const &prefixes { data[i].second };
        auto const &nextPrefixes { data[i + 1].second };

        std::string prefix, prefixOfNext;
        while (localIndex < prefixes.size() && localIndex < nextPrefixes.size()) {
          prefix = prefixes.at(localIndex);
          prefixOfNext = nextPrefixes.at(localIndex);
          if (prefix != prefixOfNext) break;
          ++localIndex;
        }

        auto resultIndex { std::max(globalIndex, localIndex) };
        resultIndex = std::min(resultIndex, prefixes.size() - 1);

        auto result { prefixes[resultIndex] };

        std::cerr << data[i].first << ": '" << result << '\'' << std::endl;

        globalIndex = localIndex;
      }

      auto const &lastPrefixes { data.back().second };
      auto resultIndex = std::min(globalIndex, lastPrefixes.size() - 1);
      auto result { lastPrefixes[resultIndex] };

      std::cerr << data.back().first << ": " << result << std::endl;

    }

  private:
    // TODO Reference.
    std::vector<ItemType> data;
  };
}
