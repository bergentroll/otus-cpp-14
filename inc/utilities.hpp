#pragma once

#include <fstream>
#include <stdexcept>

namespace otus {
  using PosType = std::ifstream::pos_type;

  class FailedToReadFile: public std::runtime_error {
  public:
    FailedToReadFile(std::string const &message):
      std::runtime_error(message.c_str()) { }
  };
}
