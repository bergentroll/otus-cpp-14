#include <cstdlib>
#include <string>
#include <iostream>
#include <vector>

#include "thread_pool.hpp"
#include "file_marker.hpp"

using namespace std;
using namespace otus;

int main(int argc, char **argv) {
  size_t mapThreadsNum { 6 };
  size_t reduceThreadsNum { 6 };
  string filename { "../small_steady_set.txt" };

  std::vector<FileMarker::PosType> marks { };
  marks.reserve(mapThreadsNum);

  try {
    FileMarker marker { filename };
    marks = marker.mark(mapThreadsNum);
  }
  catch (FileMarker::FailedToReadFile const &e) {
    std::cerr << "Error: " << e.what() << endl;
    return EXIT_FAILURE;
  }

  //ThreadPool mapThreads { mapThreads };
  //vector<Mapper> mappers { };
  //mappers.reserve(mapThreadsNum);

  //for (auto entry: entries) {
  //  mappers.emplace_back(filename, entry, blockSize);
  //  mapThread.run(mappers.back().map());
  //}

  //mapThreads.join();

  //ThreadPool shuffleThreads { mapThreadsNum };

  //// TODO run shuffle

  //shuffleThreads.join();

  //ThreadPool reduceThreads { reduceThreadsNum };

  //// TODO run reduce

  //reduceThreads.join();

  return EXIT_SUCCESS;
}
