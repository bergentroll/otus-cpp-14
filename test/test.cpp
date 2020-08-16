#define BOOST_TEST_MAIN

#include <boost/test/unit_test.hpp>
#include <fstream>
#include <vector>

#include "aliases.hpp"
#include "file_marker.hpp"

using namespace std;
using namespace otus;

BOOST_AUTO_TEST_SUITE(FileMarkerTest);

BOOST_AUTO_TEST_CASE(test1) {
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

BOOST_AUTO_TEST_CASE(test2) {
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

/// TODO Shuffler

BOOST_AUTO_TEST_SUITE_END();
