#include "reducer.hpp"

using namespace otus;
using namespace std;

void Reducer::operator()() const {
  if (data.empty()) return;

  stringstream filename { };
  filename << this_thread::get_id() << ".txt";
  ofstream file { filename.str() };

  size_t globalIndex { };

  for (vector<ItemType>::size_type i { }; i < data.size() - 1; ++i) {
    size_t localIndex { };
    auto const &prefixes { data[i].second };
    auto const &nextPrefixes { data[i + 1].second };

    string prefix, prefixOfNext;
    while (localIndex < prefixes.size() && localIndex < nextPrefixes.size()) {
      prefix = prefixes.at(localIndex);
      prefixOfNext = nextPrefixes.at(localIndex);
      if (prefix != prefixOfNext) break;
      ++localIndex;
    }

    auto resultIndex { max(globalIndex, localIndex) };
    resultIndex = min(resultIndex, prefixes.size() - 1);

    auto result { prefixes.size()? prefixes[resultIndex]: "" };

    file << result << '\n';

    globalIndex = localIndex;
  }

  auto const &lastPrefixes { data.back().second };
  auto resultIndex = min(globalIndex, lastPrefixes.size() - 1);
  auto result { lastPrefixes[resultIndex] };

  file << result << '\n';
}
