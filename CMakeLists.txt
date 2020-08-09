cmake_minimum_required(VERSION 3.12.4)

if($ENV{TRAVIS_BUILD_NUMBER})
  set(VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
else()
  set(VERSION 0.0.0)
endif()
project(yamr VERSION ${VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

### Dependencies ##############################################################

set(SRC_PATH "src/")
set(TEST_PATH "test/")
include_directories("inc/")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(
  Boost 1.65
  COMPONENTS program_options
  OPTIONAL_COMPONENTS unit_test_framework)

find_package(Threads REQUIRED)

### Main targets ##############################################################

#add_library(
#  ${CMAKE_PROJECT_NAME}-obj
#  #STATIC ${SRC_PATH}/.cpp)
#  )
#target_link_libraries(
#  ${CMAKE_PROJECT_NAME}-obj
#  ${CMAKE_THREAD_LIBS_INIT}
#  stdc++fs)

add_executable(
  ${CMAKE_PROJECT_NAME}
  ${SRC_PATH}/main.cpp)
target_link_libraries(
  ${CMAKE_PROJECT_NAME}
  ${CMAKE_THREAD_LIBS_INIT}
#  ${CMAKE_PROJECT_NAME}-obj
  ${Boost_PROGRAM_OPTIONS_LIBRARY})

### Tests #####################################################################

if(Boost_UNIT_TEST_FRAMEWORK_FOUND)
  add_executable(test-suite ${TEST_PATH}/test.cpp)
  target_link_libraries(
    test-suite
    PRIVATE
    #${CMAKE_PROJECT_NAME}-obj
    Boost::unit_test_framework)
  add_test(test-suite test-suite)
else()
  message(
    WARNING "Test suite will not be launched because Boost.Test not found.")
endif()

enable_testing()

### Packing ###################################################################

install(TARGETS ${CMAKE_PROJECT_NAME} RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_CONTACT bergentroll@insiberia.net)
set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)
