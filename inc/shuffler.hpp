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
      while (true) {
        std::vector<std::pair<std::string, size_t>> currentValues { };

        for (size_t i { }; i < input.size(); ++i) {
          auto it { iterators[i] };
          if (it != input[i].cend()) {
            currentValues.push_back(std::make_pair((*it).first, i));
          }
        }

        if (currentValues.size() == 0) {
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
        std::string secondMin;

        if (currentValues.size() == 1) {
          secondMin = target.back().first;
        }
        else {
          secondMin = currentValues[1].first;
        }

        moveData(targetContainerIndex, secondMin);
      }
    }

    std::vector<ItemType> getResult() { return result; }

  private:
    InputType &input;
    std::vector<ItemType> result { };
    std::vector<std::vector<ItemType>::const_iterator> iterators { };

    void moveData(size_t targetContainerIndex, std::string secondMin) {
        auto const &target { input[targetContainerIndex] };
        auto &it { iterators[targetContainerIndex] };

        ItemType secondMinItem { secondMin, { } };
        auto end { std::upper_bound(
            it,
            target.cend(),
            secondMinItem,
            [](auto const &item1, auto const &item2) {
              return item1.first < item2.first;
            })
        };

        std::copy(it, end, std::back_inserter(result));

        it = end;
    }
  };
}
