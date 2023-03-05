cmake_minimum_required(VERSION 3.0)
project(the-bad-one)

set(COMPILE_FLAGS on)

add_subdirectory(libs/catch2)

add_executable(the-bad-one
    src/core/dice_bucket.cc
    src/core/dice_rng.cc
    src/core/match.cc
    src/core/player.cc
    src/main.cc
)
target_compile_options(the-bad-one PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/WX /W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++>
)
set_property(TARGET the-bad-one PROPERTY CXX_STANDARD 20)

add_executable(tests
    src/core/dice_bucket.cc
    src/core/dice_rng.cc
    src/core/match.cc
    src/core/player.cc
    tests/main.cc
    tests/dice_bucket_test.cc
    tests/dice_rng_test.cc
    tests/expected_test.cc
    tests/match_test.cc
    tests/player_test.cc
)
target_include_directories(tests
  PRIVATE src/
)
target_link_libraries(tests
  PRIVATE Catch2WithMain
)
target_compile_options(tests PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/WX /W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation -Wnull-dereference -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++>
)
set_property(TARGET tests PROPERTY CXX_STANDARD 20)

include(CTest)
include(Catch)
catch_discover_tests(tests)