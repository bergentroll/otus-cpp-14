#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <vector>

#include "file_marker.hpp"
#include "shuffler.hpp"
#include "utilities.hpp"

using namespace std;
using namespace otus;

namespace std {
  ostream & operator<<(
      ostream & stream,
      vector<Shuffler::ItemType> const & collection) {
    stream << "[ ";
    for (auto it { collection.cbegin() }; it != collection.cend(); ++it) {
      stream << it->first;
      if (next(it) != collection.cend()) stream << ", ";
    }
    stream << " ]";
    return stream;
  }

  ostream & operator<<(ostream & stream, pair<PosType, size_t> const & item) {
    stream << "[ " << item.first << ", " << item.second << " ]";
    return stream;
  }
}

BOOST_AUTO_TEST_SUITE(FileMarkerTest);

BOOST_AUTO_TEST_CASE(file_marker_1) {
  FileMarker::OutputType expected { { 39 , 4 }, { 69, 3 }, { 99, 3 } };

  string filename { "file1.txt" };
  ofstream file { filename };
  for (int i { }; i < 10; ++i) file << "012345678\n";
  file.close();

  FileMarker marker { filename };
  auto result { marker.mark(3) };

  BOOST_CHECK_EQUAL_COLLECTIONS(
      result.cbegin(), result.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_CASE(file_marker_2) {
  FileMarker::OutputType expected {
    {  9, 1 }, { 19, 1 }, { 29, 1 }, { 39, 1 }, { 49, 1 },
    { 59, 1 }, { 69, 1 }, { 79, 1 }, { 89, 1 }, { 99, 1 },
    { 99, 0 }, { 99, 0 }, { 99, 0 }, { 99, 0 }, { 99, 0 },
    { 99, 0 }, { 99, 0 }, { 99, 0 }, { 99, 0 }, { 99, 0 }
  };

  string filename { "file2.txt" };
  ofstream file { filename };
  for (int i { }; i < 10; ++i) file << "012345678\n";
  file.close();

  FileMarker marker { filename };
  auto result { marker.mark(20) };
  BOOST_CHECK_EQUAL_COLLECTIONS(
      result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE(ShufflerTest);

BOOST_AUTO_TEST_CASE(shuffler_steady) {
  vector<Shuffler::ItemType>
    v1 { { "A", { } }, { "B", { } }, { "C", { } }, { "D", { } } },
    v2 { { "E", { } }, { "F", { } }, { "G", { } } },
    v3 { { "H", { } }, { "I", { } }, { "J", { } } },
    v4 { { "K", { } }, { "L", { } }, { "M", { } } };

  Shuffler::OutputType expected {
    { { "A", { } }, { "B", { } }, { "C", { } }, { "D", { } }, { "E", { } } },
    { { "F", { } }, { "G", { } }, { "H", { } }, { "I", { } }, { "J", { } } },
    { { "K", { } }, { "L", { } }, { "M", { } } }
  };

  Shuffler::InputType input { &v1, &v2, &v3, &v4 };
  Shuffler shuffler { input, 3 };

  shuffler();

  auto &result = shuffler.getResult();

  BOOST_CHECK_EQUAL_COLLECTIONS(
      result.cbegin(), result.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_CASE(shuffler_twins_in_different_containers) {
  vector<Shuffler::ItemType>
    v1 { { "A", { } }, { "B", { } }, { "C", { } }, { "D", { } } },
    v2 { { "E", { } }, { "F", { } }, { "G", { } } },
    v3 { { "H", { } }, { "I", { } }, { "J", { } } },
    v4 { { "J", { } }, { "J", { } }, { "M", { } } };

  Shuffler::OutputType expected {
    { { "A", { } }, { "B", { } }, { "C", { } }, { "D", { } }, { "E", { } } },
    { { "F", { } }, { "G", { } }, { "H", { } }, { "I", { } }, { "J", { } },
      { "J", { } }, { "J", { } } },
    { { "M", { } } }
  };

  Shuffler::InputType input { &v1, &v2, &v3, &v4 };
  Shuffler shuffler { input, 3 };

  shuffler();

  auto &result = shuffler.getResult();

  BOOST_CHECK_EQUAL_COLLECTIONS(
      result.cbegin(), result.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_CASE(shuffler_twins_in_one_container) {
  vector<Shuffler::ItemType>
    v1 { { "A", { } }, { "B", { } }, { "C", { } }, { "D", { } } },
    v2 { { "E", { } }, { "E", { } }, { "E", { } } },
    v3 { { "H", { } }, { "I", { } }, { "J", { } } },
    v4 { { "K", { } }, { "L", { } }, { "M", { } } };

  Shuffler::OutputType expected {
    { { "A", { } }, { "B", { } }, { "C", { } }, { "D", { } }, { "E", { } },
      { "E", { } }, { "E", { } } },
    { { "H", { } }, { "I", { } }, { "J", { } }, { "K", { } }, { "L", { } } },
    { { "M", { } } }
  };

  Shuffler::InputType input { &v1, &v2, &v3, &v4 };
  Shuffler shuffler { input, 3 };

  shuffler();

  auto &result = shuffler.getResult();

  BOOST_CHECK_EQUAL_COLLECTIONS(
      result.cbegin(), result.cend(), expected.cbegin(), expected.cend());
}

BOOST_AUTO_TEST_SUITE_END();
