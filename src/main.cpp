#include <boost/program_options.hpp>
#include <boost/serialization/strong_typedef.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "file_marker.hpp"
#include "mapper.hpp"
#include "reducer.hpp"
#include "shuffler.hpp"
#include "thread_pool.hpp"

using namespace std;
using namespace otus;
namespace po = boost::program_options;
using 
  boost::any,
  boost::any_cast,
  boost::lexical_cast,
  boost::bad_lexical_cast;

BOOST_STRONG_TYPEDEF(int, ThreadsNum);

void validate(any& v, const vector<string>& values, ThreadsNum*, int) {
  po::validators::check_first_occurrence(v);
  const string &str { po::validators::get_single_string(values) };
  try {
    v = lexical_cast<ThreadsNum>(str);
  } catch (bad_lexical_cast const &e) {
    throw po::error("unexpected threads amount " + str);
  }
  auto port { any_cast<ThreadsNum>(v) };
  if (port < 1) throw po::error("threads amount must be greater than 0");
}

int main(int argc, char **argv) {
  string filename;
  size_t mapThreadsNum;
  size_t reduceThreadsNum;

  try {
    po::positional_options_description positional_description { };
    positional_description.add("src", 1);
    positional_description.add("mnum", 1);
    positional_description.add("rnum", 1);

    po::options_description description { "Hidden options" };
    description.add_options()
      ("src", po::value<string>()->composing()->required(),
       "input file")
      ("mnum", po::value<ThreadsNum>()->composing()->required(),
       "numer of mapping threads")
      ("rnum", po::value<ThreadsNum>()->composing()->required(),
       "number of reduce threads");

    po::variables_map options;

    po::store(
      po::command_line_parser(argc, argv)
        .positional(positional_description)
        .options(description)
        .run(),
      options);
    po::notify(options);

    filename = options["src"].as<string>();
    mapThreadsNum = options["mnum"].as<ThreadsNum>();
    reduceThreadsNum = options["rnum"].as<ThreadsNum>();

  } catch (po::error const &e) {
    cerr << "Options error: " << e.what() << endl;
    return EXIT_FAILURE;
  }

  std::vector<PosType> marks { };
  marks.reserve(mapThreadsNum);

  try {
    FileMarker marker { filename };
    marks = marker.mark(mapThreadsNum);
  }
  catch (FileMarker::FailedToReadFile const &e) {
    std::cerr << "Error: " << e.what() << endl;
    return EXIT_FAILURE;
  }

  ThreadPool<decltype(&Mapper::run), Mapper*> mapThreads { mapThreadsNum };
  vector<Mapper> mappers { };
  mappers.reserve(mapThreadsNum);

  PosType begin { 0 };
  for (auto end: marks) {
    mappers.emplace_back(filename, begin, end);
    Mapper &mapper { mappers.back() };
    mapThreads.run(&Mapper::run, &mapper);
    begin = end + PosType(1);
  }

  mapThreads.join();

  // FIXME Eliminate copying.
  Shuffler::InputType containers { };
  containers.reserve(mapThreadsNum);
  for (auto &i: mappers) {
    containers.push_back(i.getResult());
  }

  //// TODO Run parrallel.
  Shuffler shuffler { containers };

  shuffler();

  auto const &cont { shuffler.getResult() };

  for (auto i: cont) {
    cout << i.first << "\n";
  }

  //reduceThreadsNum = mapThreadsNum;
  //ThreadPool<decltype(&Reducer::run), Reducer*> reduceThreads { reduceThreadsNum };
  //vector<Reducer> reducers { };
  //reducers.reserve(reduceThreadsNum);

  ///// TODO It seems it can be generalized.
  //for (auto &item: mappers) {
  //  reducers.emplace_back(item.getResult());
  //  Reducer &reducer { reducers.back() };
  //  reduceThreads.run(&Reducer::run, &reducer);
  //}

  //reduceThreads.join();

  return EXIT_SUCCESS;
}
