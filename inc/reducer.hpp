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

    /**
     * data may be empty.
     */
    Reducer (std::vector<ItemType> const &data):
    data(data) { }

    void operator()() const;

  private:
    std::vector<ItemType> const &data;
  };
}
