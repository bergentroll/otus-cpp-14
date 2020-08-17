#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include <iostream>

namespace otus {
  /// Shuffler merges multiple sorted containers preserving sorting.
  class Shuffler {
  public:
    using ItemType = std::pair<std::string, std::vector<std::string>>;
    using InputType = std::vector<std::vector<ItemType> *>;
    using OutputType = std::vector<std::vector<ItemType>>;

    Shuffler(InputType &input, size_t resultContainersNumber):
    input(input),
    result(OutputType(resultContainersNumber)) {
      currentValues.reserve(input.size());
      iterators.reserve(input.size());

      size_t itemsAmount { };
      for (auto containerPtr: input) {
        itemsAmount += containerPtr->size();
        iterators.push_back(containerPtr->begin());
      }

      outputContainerSize = itemsAmount / resultContainersNumber;
      if (itemsAmount % resultContainersNumber)
        outputContainerSize += 1;

      for (auto &container: result) {
        /// TODO Add some room.
        container.reserve(outputContainerSize);
      }
    };

    /** @brief Shuffle data from input containers to inner.
     *
     * After call date will be moved to internal containers. Input containers
     * will be cleaned.
     */
    void operator()() {
      while (true) {
        for (size_t i { }; i < input.size(); ++i) {
          auto it { iterators[i] };
          if (it != input[i]->end()) {
            currentValues.push_back(std::make_pair((*it).first, i));
          }
        }

        if (currentValues.size() == 0) {
          for (auto containerPtr: input) containerPtr->clear();
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
          secondMin = target->back().first;
        }
        else {
          secondMin = currentValues[1].first;
        }

        currentValues.clear();

        moveData(targetContainerIndex, secondMin);
      }
    }

    OutputType & getResult() { return result; }

  private:
    InputType &input;
    OutputType result;
    size_t outputContainerSize;
    size_t currentOutputContainer { };
    std::vector<std::vector<ItemType>::iterator> iterators { };
    std::vector<std::pair<std::string, size_t>> currentValues { };

    void moveData(size_t targetContainerIndex, std::string secondMin) {
        // TODO Clarify naming.
        auto const &target { input[targetContainerIndex] };
        auto &it { iterators[targetContainerIndex] };

        ItemType secondMinItem { secondMin, { } };
        auto end { std::upper_bound(
            it,
            target->end(),
            secondMinItem,
            [](auto const &item1, auto const &item2) {
              return item1.first < item2.first;
            })
        };

        while (it != end) {
          auto &targetContainer { result[currentOutputContainer] };
          targetContainer.push_back(std::move(*it));
          std::string const &value { targetContainer.back().first };

          if (targetContainer.size() >= outputContainerSize) {
            auto nextIt { std::next(it) };
            std::string nextValue;
            if (nextIt != end) nextValue = nextIt->first;
            else nextValue = secondMin;

            if (nextValue != value) ++currentOutputContainer;
          }

          ++it;
        }
    }
  };
}
