cmake_minimum_required(VERSION 3.10)
project(dec0006 VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(main main.cpp)
target_link_libraries(main gtest gtest_main pthread)

include(CPack)