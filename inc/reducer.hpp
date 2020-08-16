#pragma once

#include <fstream>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

#include <iostream>

namespace otus {
  class Reducer {
  public:
    using ItemType = std::pair<std::string, std::vector<std::string>>;
    Reducer (std::vector<ItemType> const &data):
      data(data) { }

    void operator()() const {
      std::stringstream filename { };
      filename << std::this_thread::get_id() << ".txt";
      std::ofstream file { filename.str() };

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

        file << result << '\n';

        globalIndex = localIndex;
      }

      auto const &lastPrefixes { data.back().second };
      auto resultIndex = std::min(globalIndex, lastPrefixes.size() - 1);
      auto result { lastPrefixes[resultIndex] };

      file << result << '\n';
    }

  private:
    std::vector<ItemType> const &data;
  };
}
