#include "shuffler.hpp"

using namespace std;
using namespace otus;

Shuffler::Shuffler(InputType &input, size_t resultContainersNumber):
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

  // Room needed when we have duplicates to put them in one container.
  for (auto &container: result) {
    container.reserve(outputContainerSize + roomSize);
  }
};

void Shuffler::operator()() {
  while (true) {
    for (size_t i { }; i < input.size(); ++i) {
      auto it { iterators[i] };
      if (it != input[i]->end()) {
        currentValues.push_back(make_pair((*it).first, i));
      }
    }

    if (currentValues.size() == 0) {
      for (auto containerPtr: input) containerPtr->clear();
      return;
    }

    sort(
        currentValues.begin(),
        currentValues.end(),
        [](auto const &item1, auto const &item2) {
        return item1.first < item2.first;
        });

    auto targetContainerIndex { currentValues[0].second };
    auto const &target { input[targetContainerIndex] };
    string secondMin;

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

void Shuffler::moveData(size_t sourceContainerIndex, string secondMin) {
    auto const &sourceContainer{ input[sourceContainerIndex] };
    auto &it { iterators[sourceContainerIndex] };

    ItemType secondMinItem { secondMin, { } };
    auto end { upper_bound(
        it,
        sourceContainer->end(),
        secondMinItem,
        [](auto const &item1, auto const &item2) {
          return item1.first < item2.first;
        })
    };

    while (it != end) {
      auto &targetContainer { result[currentOutputContainer] };
      targetContainer.push_back(move(*it));
      string const &value { targetContainer.back().first };

      if (targetContainer.size() >= outputContainerSize) {
        auto nextIt { next(it) };
        string nextValue;
        if (nextIt != end) nextValue = nextIt->first;
        else nextValue = secondMin;

        if (nextValue != value) ++currentOutputContainer;
      }

      ++it;
    }
}
