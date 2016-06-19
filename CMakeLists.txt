cmake_minimum_required(VERSION 3.5)
project(waveGen)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES main/main.c main/main.h libwav/wav.c libwav/wav.h)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

add_executable(waveGen ${SOURCE_FILES})
target_link_libraries(waveGen m)