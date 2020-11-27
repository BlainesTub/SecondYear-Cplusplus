cmake_minimum_required(VERSION 3.5.1)

project(07_assign)

# in case you decide to use gcc
IF(CMAKE_COMPILER_IS_GNUCC)
   SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "--std=c++14 -pedantic -Wall -Werror-Wextra")
ENDIF(CMAKE_COMPILER_IS_GNUCC)

# make Visual studio and Xcode output the binaries in the same build directory
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
SET( CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}")

set(binary expression_tree)

add_executable(${binary} ${binary}.cpp parser.cpp expression_tree.hpp main.cpp)


target_compile_features(${binary} PRIVATE cxx_decltype_auto cxx_auto_type)


enable_testing()

# set the binary to bes tested in each of the tests below. 
set(test_cmd ${CMAKE_BINARY_DIR}/${binary}${CMAKE_EXECUTABLE_SUFFIX} )
set(tester   ${CMAKE_CURRENT_SOURCE_DIR}/tester-mst.cmake)
set(loc ${CMAKE_CURRENT_SOURCE_DIR})


add_test(
    NAME test01 
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=01 -DLOC=${loc} -P ${tester}
)

add_test(
    NAME test02
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=02 -DLOC=${loc} -P ${tester}
)

add_test(
    NAME test03 
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=03 -DLOC=${loc} -P ${tester}
)

add_test(
    NAME test04
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=04 -DLOC=${loc} -P ${tester}
)

add_test(
    NAME test05
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=05 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test06
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=06 -DLOC=${loc} -P ${tester}
)

add_test(
    NAME test07
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=07 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test08
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=08 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test09
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=09 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test10
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=10 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test11
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=11 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test12
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=12 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test13
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=13 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test14
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=14 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test15
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=15 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test16
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=16 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test17
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=17 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test18
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=18 -DLOC=${loc} -P ${tester}
)
add_test(
    NAME test19
    COMMAND ${CMAKE_COMMAND} -DEXE=${test_cmd} -D ID=19 -DLOC=${loc} -P ${tester}
)