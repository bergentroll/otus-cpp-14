#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include <iostream>

namespace otus {
  class Shuffler {
  public:
    using ItemType = std::pair<std::string, std::vector<std::string>>;
    using InputType = std::vector<std::vector<ItemType>>;

    Shuffler(InputType &input):
    input(input) {
      size_t itemsAmount { };
      for (auto const &container: input) {
        itemsAmount += container.size();
        iterators.push_back(container.cbegin());
      }
      result.reserve(itemsAmount);
    };

    /// FIXME Still errors in sorting.
    void operator()() {
      while (true) {
        std::string secondMin;
        std::vector<std::pair<std::string, size_t>> currentValues { };

        for (size_t i { }; i < input.size(); ++i) {
          auto it { iterators[i] };
          if (it != input[i].cend()) {
            currentValues.push_back(std::make_pair((*it).first, i));
          }
        }

        if (currentValues.size() == 0) {
          std::cerr << "Nothing remains\n";
          return;
        }

        std::sort(
            currentValues.begin(),
            currentValues.end(),
            [](auto const &item1, auto const &item2) {
            return item1.first < item2.first;
            });

        auto targetContainerIndex { currentValues[0].second };
        auto const &target { input[targetContainerIndex] };

        if (currentValues.size() == 1) {
          secondMin = target.back().first;
          std::cerr << "Last container\n";
        }
        else {
          secondMin = currentValues[1].first;
        }

        auto &it { iterators[targetContainerIndex] };

        std::cerr << "containersRemain: " << currentValues.size() << ", secondMin: " << secondMin << '\n';
        /// FIXME Use upper_bound for efficient.
        auto end { std::find_if(
            it,
            target.cend(),
            [&secondMin](auto const &item) { std::cerr << item.first << ", "; return item.first > secondMin; }) };

        std::cerr << "\n";
        std::cerr << "End: " << ((end != target.cend())? (*end).first: "end") << "\n";

        std::for_each(it, end, [](auto item) { std::cerr << item.first << ", "; });
        std::cerr << std::endl;

        std::copy(it, end, std::back_inserter(result));

        it = end;
        std::cerr << "::CYCLE::\n\n";
      }
    }

    std::vector<ItemType> getResult() { return result; }

  private:
    InputType &input;
    std::vector<ItemType> result { };
    std::vector<std::vector<ItemType>::const_iterator> iterators { };
  };
}
