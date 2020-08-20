#include "mapper.hpp"

using namespace otus;
using namespace std;

Mapper::Mapper(string const &filename, PosType begin, PosType end, size_t size):
file(filename) {
  if (!file.is_open())
    throw FailedToReadFile("failed to open file \"" + filename + '"');

  file.seekg(begin);
  string line;
  tokens.reserve(size);
  while (file.tellg() <= end && getline(file, line)) {
    tokens.push_back(line);
    if (file.fail())throw  FailedToReadFile(
        "fail while reading file \"" + filename + '"');
  }
}

void Mapper::operator()() {
  sort(tokens.begin(), tokens.end());

  result.reserve(tokens.size());

  for (auto const &token: tokens)
    result.push_back(make_pair(token, process(token)));
}

vector<string> Mapper::process(string const &item) {
  vector<string> result { };
  result.reserve(item.length());

  string buf { };
  for (auto ch: item) {
    buf += ch;
    result.push_back(buf);
  }

  return result;
}
