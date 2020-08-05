#include <cstdlib>
#include <string>
#include <vector>

#include <thread_pool.hpp>

using namespace std;

int main(int argc, char **argv) {
  size_t mapThreadsNum { 6 };
  size_t reduceThreadsNum { 6 };
  string filename { "big_set.txt" };

  auto [blockSize, entries] { splitFile(filename, mapThreadsNum) };

  ThreadPool mapThreads { mapThreads };
  vector<Mapper> mappers { };
  mappers.reserve(mapThreadsNum);

  for (auto entry: entries) {
    mappers.emplace_back(filename, entry, blockSize);
    mapThread.run(mappers.back().map());
  }

  mapThreads.join();

  ThreadPool shuffleThreads { mapThreadsNum };

  // TODO run shuffle

  shuffleThreads.join();

  ThreadPool reduceThreads { reduceThreadsNum };

  // TODO run reduce

  reduceThreads.join();

  return EXIT_SUCCESS;
}
