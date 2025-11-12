cmake_minimum_required(VERSION 3.24)

project("Farming Simulator")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

set(VEGETABLE_SRCS
  src/vegetables/carrot.cpp
  src/vegetables/beet.cpp
  src/vegetables/lettuce.cpp
  src/vegetables/spinach.cpp
  src/vegetables/brussels_sprouts.cpp
)

add_executable(farm_printer_test
  tests/farm_printer_test.cpp
  src/farm_printer.cpp
  src/farm.cpp
  src/soil.cpp
  src/player.cpp
  ${VEGETABLE_SRCS}
)

add_executable(farm_test
  tests/farm_test.cpp
  src/farm.cpp
  src/soil.cpp
  src/player.cpp
  ${VEGETABLE_SRCS}
)

add_executable(soil_test tests/soil_test.cpp src/soil.cpp)
add_executable(vegetables_test tests/vegetables_test.cpp ${VEGETABLE_SRCS})
add_executable(player_test tests/player_test.cpp src/player.cpp)

add_executable(main
  main.cpp
  src/farm.cpp
  src/farm_printer.cpp
  src/soil.cpp
  src/player.cpp
  ${VEGETABLE_SRCS}
)

target_link_libraries(farm_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(farm_printer_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(soil_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(vegetables_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(player_test PRIVATE Catch2::Catch2WithMain)
