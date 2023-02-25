cmake_minimum_required(VERSION 3.0)
project(the-bad-one)

add_executable(the-bad-one
    src/main.cc
)
target_compile_options(the-bad-one PRIVATE
  $<$<CXX_COMPILER_ID:MSVC>:/WX /W4>
  $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Werror -Wall -Wextra -Wshadow -Wnon-virtual-dtor -pedantic -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wconversion -Wsign-conversion -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wimplicit-fallthrough -Weffc++>
)