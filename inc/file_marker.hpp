#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <vector>

#include "utilities.hpp"

namespace otus {
  class FileMarker {
  public:
    using OutputType = std::vector<std::pair<PosType, size_t>>;

    FileMarker(std::string const &filename);

    /// Get positions of last \n in blocks.
    OutputType mark(size_t blocksNum) const;

    private:
    std::vector<PosType> eols { };
  };
}
