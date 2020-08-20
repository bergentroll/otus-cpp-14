#include "file_marker.hpp"

using namespace otus;
using namespace std;

FileMarker::FileMarker(string const &filename) {
  ifstream file { filename };

  if (!file.is_open())
    throw FailedToReadFile("failed to open file \"" + filename + '"');

  for_each(
      istreambuf_iterator<char>(file),
      istreambuf_iterator<char>(),
      [this, &file, &filename](char ch) {
        if (ch == '\n') eols.push_back(file.tellg());
        if (file.fail())throw  FailedToReadFile(
            "fail while reading file \"" + filename + '"');
      });

  file.close();
}

FileMarker::OutputType FileMarker::mark(size_t blocksNum) const {
  OutputType result { };
  result.reserve(blocksNum);

  auto blockSize { eols.size() / blocksNum };
  auto remainder { eols.size() % blocksNum };

  size_t shift { 0 };
  size_t prevMarkIndex { 0 };

  for (size_t i { 0 }; i < blocksNum; ++i) {
    // To spread remains on blocks.
    if (remainder > 0) {
      --remainder;
      ++shift;
    }

    auto markIndex { (i + 1) * blockSize + shift - 1 };
    auto mark { eols[markIndex] };

    result.push_back(make_pair(
          mark,
          markIndex - prevMarkIndex + (i == 0)));

    prevMarkIndex = markIndex;
  }

  return result;
}
