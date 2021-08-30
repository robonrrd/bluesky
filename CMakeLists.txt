cmake_minimum_required(VERSION 3.0x)
project (bluesky)
set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g")


# BlueSky main
set(BLUESKY_SRC
  src/bluesky.cpp
  src/writer.cpp
  )

add_executable(bluesky ${BLUESKY_SRC})
target_include_directories(bluesky
  PUBLIC include)

# Test heightmap/VGHT generation
set(GENERATOR_SRC
  src/generator_test.cpp
  src/generator.cpp
  )
add_executable(generator_test ${GENERATOR_SRC})
target_include_directories(generator_test
  PUBLIC include)

