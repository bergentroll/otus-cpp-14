#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <vector>

#include "aliases.hpp"
#include "file_marker.hpp"
#include "shuffler.hpp"

using namespace std;
using namespace otus;

BOOST_AUTO_TEST_SUITE(FileMarkerTest);

BOOST_AUTO_TEST_CASE(file_marker_1) {
  vector<PosType> expected { 39, 69, 99 };

  string filename { "file1.txt" };
  ofstream file { filename };
  for (int i { }; i < 10; ++i) file << "012345678\n";
  file.close();

  FileMarker marker { filename };
  auto result { marker.mark(3) };
  BOOST_CHECK_EQUAL_COLLECTIONS(
      result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(file_marker_2) {
  vector<PosType> expected {
    9, 19, 29, 39, 49, 59, 69, 79, 89, 99,
    99, 99, 99, 99, 99, 99, 99, 99, 99, 99
  };

  string filename { "file1.txt" };
  ofstream file { filename };
  for (int i { }; i < 10; ++i) file << "012345678\n";
  file.close();

  FileMarker marker { filename };
  auto result { marker.mark(20) };
  BOOST_CHECK_EQUAL_COLLECTIONS(
      result.begin(), result.end(), expected.begin(), expected.end());
}

BOOST_AUTO_TEST_CASE(shuffler_1) {
  vector<Shuffler::ItemType>
    v1 { { "A", { } }, { "B", { } }, { "C", { } }, { "D", { } } },
    v2 { { "E", { } }, { "F", { } }, { "G", { } } },
    v3 { { "H", { } }, { "I", { } }, { "J", { } } },
    v4 { { "K", { } }, { "L", { } }, { "M", { } } };

  Shuffler::InputType input { &v1, &v2, &v3, &v4 };
  Shuffler shuffler { input, 3 };

  shuffler();

  /// TODO
  for (auto &i: shuffler.getResult()) {
    for (auto &j: i) {
      cerr << j.first << endl;
    }
    cerr << endl;
  }
}

BOOST_AUTO_TEST_SUITE_END();
