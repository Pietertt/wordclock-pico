cmake_minimum_required(VERSION 3.12)

include(pico_sdk_import.cmake)

project(pico_examples C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

set(PICO_EXAMPLES_PATH ${PROJECT_SOURCE_DIR})

pico_sdk_init()

add_compile_options(-Wall
    -Wno-format
    -Wno-unused-function
    -Wno-maybe-uninitialized
)

add_executable(wordclock
    src/main.cpp
    src/wordclock.cpp
    src/register.cpp
    src/singleregister.cpp
    src/doubleregister.cpp
    src/word.cpp
)

target_include_directories(wordclock
    PRIVATE
    include/
)

target_link_libraries(wordclock pico_stdlib)
target_link_libraries(wordclock pico_multicore)
target_link_libraries(wordclock hardware_rtc)
target_link_libraries(wordclock hardware_adc)

pico_add_extra_outputs(wordclock)
