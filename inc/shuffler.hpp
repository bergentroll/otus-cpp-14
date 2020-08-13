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

    void operator()() {
      while (!isFinished()) {

        auto [targetContainerIndex, prevMin] { getTarget() };

        auto const &target { input[targetContainerIndex] };
        auto &it { iterators[targetContainerIndex] };

        /// FIXME Use upper_bound for efficient.
        auto end { std::find_if(
            target.cbegin(),
            target.cend(),
            [&prevMin](auto const &item) { return item.first > prevMin; }) };

        std::copy(it, end, std::back_inserter(result));

        if (end == target.cend()) std::cerr << "End of " << targetContainerIndex << " reached\n";

        it = end;
      }
    }

    std::vector<ItemType> getResult() { return result; }

  private:
    InputType &input;
    std::vector<ItemType> result { };
    std::vector<std::vector<ItemType>::const_iterator> iterators { };

    bool isFinished() {
      for (size_t i { }; i < input.size(); ++i) {
        if (iterators[i] != input[i].cend()) {
          std::cerr << "Not finished: " << i << ", value: " << (*iterators[i]).first << std::endl;
          return false;
        }
      }
      return true;
    }

    std::pair<size_t, std::string> getTarget() {
      std::string min { "Zzz" }, prevMin { "Zzz" }; // FIXME
      size_t targetContainerIndex { };

      for (size_t i { }; i < input.size(); ++i) {
        auto it { iterators[i] };
        if (it == input[i].cend()) continue;

        auto const &value { (*it).first };
        if (value < min) {
          prevMin = min;
          min = value;
          targetContainerIndex = i;
        }
      }

      std::cerr << "ContIndex: " << targetContainerIndex
        << ", prevMin: " << prevMin << ", min: " << min << "\n";
      return std::make_pair(targetContainerIndex, prevMin);
    }
  };
}
