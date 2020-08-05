#include <cstdlib>
#include <string>

int main(int argc, char **argv) {
  size_t mThreadsNum { 6 };
  size_t rThreadsNum { 6 };
  string filename { "big_set.txt" }

  auto [blockSize, entries] { splitFile(filename, mThreadsNum };

  ThreadPool mapThreads { };

  for (auto entry: entries) {
    mapThread.run(Mapper(entry, blockSize));
  }

  mapThreads.join();

  ThreadPool shuffleThreads { } 

  // TODO run shuffle

  shuffleThreads.join();

  ThreadPool reduceThreads { };

  // TODO run reduce

  reduceThreads.join();

  return EXIT_SUCCESS;
}
