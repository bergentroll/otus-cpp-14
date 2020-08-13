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

        auto [targetContainerIndex, secondMin] { getTarget() };

        auto const &target { input[targetContainerIndex] };
        auto &it { iterators[targetContainerIndex] };

        if (containersRemain == 0) break;
        else if (containersRemain == 1) {
          secondMin = target.back().first;
        }

        /// FIXME Use upper_bound for efficient.
        auto end { std::find_if(
            target.cbegin(),
            target.cend(),
            [&secondMin](auto const &item) { return item.first > secondMin; }) };

        std::copy(it, end, std::back_inserter(result));

        it = end;
      }
    }

    std::vector<ItemType> getResult() { return result; }

  private:
    InputType &input;
    std::vector<ItemType> result { };
    std::vector<std::vector<ItemType>::const_iterator> iterators { };
    size_t containersRemain { };

    std::pair<size_t, std::string> getTarget() {
      std::string min { }, secondMin { };
      size_t targetContainerIndex { };

      containersRemain = 0;

      for (size_t i { }; i < input.size(); ++i) {
        auto it { iterators[i] };
        if (it == input[i].cend()) continue;

        ++containersRemain;

        auto const &value { (*it).first };
        if (value < min || min.empty()) {
          min = value;
          targetContainerIndex = i;
        }

        if ((value < secondMin && i != targetContainerIndex) || secondMin.empty()) {
          secondMin = value;
        }
      }

      return std::make_pair(targetContainerIndex, secondMin);
    }
  };
}
