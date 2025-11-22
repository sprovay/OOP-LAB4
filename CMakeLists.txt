cmake_minimum_required(VERSION 3.10)
project(Lab4)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(main
    src/main.cpp
)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.15.0
  TLS_VERIFY OFF
)

FetchContent_MakeAvailable(googletest)

add_executable(test
    test/test.cpp
)

target_link_libraries(test gtest_main)