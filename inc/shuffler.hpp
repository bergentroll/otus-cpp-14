#pragma once

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

namespace otus {
  /// Shuffler merges multiple sorted containers preserving sorting.
  class Shuffler {
  public:
    using ItemType = std::pair<std::string, std::vector<std::string>>;
    using InputType = std::vector<std::vector<ItemType> *>;
    using OutputType = std::vector<std::vector<ItemType>>;

    Shuffler(InputType &input, size_t resultContainersNumber);

    /** @brief Shuffle data from input containers to inner.
     *
     * After call date will be moved to internal containers. Input containers
     * will be cleaned.
     */
    void operator()();

    OutputType & getResult() { return result; }

  private:
    size_t const roomSize { 10 };
    InputType &input;
    OutputType result;
    size_t outputContainerSize;
    size_t currentOutputContainer { };
    std::vector<std::vector<ItemType>::iterator> iterators { };
    std::vector<std::pair<std::string, size_t>> currentValues { };

    void moveData(size_t sourceContainerIndex, std::string secondMin);
  };
}
