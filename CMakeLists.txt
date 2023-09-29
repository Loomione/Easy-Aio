cmake_minimum_required(VERSION 3.10)

project(MyAIOProject)

# Find the libaio library
find_library(LIBAIO_LIBRARY NAMES aio)

# Source files
set(SOURCES
    src/LinuxAio.cpp
    src/test.cpp
)

# Executable target
add_executable(my_aio_program ${SOURCES})

# Link the libaio library
target_link_libraries(my_aio_program ${LIBAIO_LIBRARY})
