cmake_minimum_required(VERSION 3.20)

project(martingale-pricer VERSION 0.1.0 LANGUAGES CXX)

option(MARTINGALE_BUILD_TESTS "Build tests" ON)
option(MARTINGALE_BUILD_BENCHMARKS "Build benchmarks" OFF)
option(MARTINGALE_SANITIZE "Enable AddressSanitizer and UndefinedBehaviorSanitizer" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(martingale STATIC src/placeholder.cpp)
target_include_directories(martingale PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_compile_options(martingale PRIVATE -Wall -Wextra -Wpedantic)

if(MARTINGALE_SANITIZE)
  target_compile_options(martingale PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
  target_link_options(martingale PRIVATE -fsanitize=address,undefined)
endif()

include(FetchContent)

if(MARTINGALE_BUILD_TESTS)
  enable_testing()
  find_package(Catch2 3 QUIET)
  if(NOT Catch2_FOUND)
    FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG v3.7.1
    )
    FetchContent_MakeAvailable(Catch2)
  endif()

  add_executable(tests tests/smoke_test.cpp)
  target_link_libraries(tests PRIVATE martingale Catch2::Catch2WithMain)
  target_compile_options(tests PRIVATE -Wall -Wextra -Wpedantic)
  add_test(NAME tests COMMAND tests)

  if(MARTINGALE_SANITIZE)
    target_compile_options(tests PRIVATE -fsanitize=address,undefined -fno-omit-frame-pointer)
    target_link_options(tests PRIVATE -fsanitize=address,undefined)
  endif()
endif()

if(MARTINGALE_BUILD_BENCHMARKS)
  FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.1
  )
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
  FetchContent_MakeAvailable(benchmark)

  add_executable(benchmarks benchmarks/placeholder_benchmark.cpp)
  target_link_libraries(benchmarks PRIVATE martingale benchmark::benchmark)
  target_compile_options(benchmarks PRIVATE -Wall -Wextra -Wpedantic)
endif()
