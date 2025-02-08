cmake_minimum_required(VERSION 3.10)
project(DuplicateContentDetection)

set(CMAKE_CXX_STANDARD 17)

# Set up SIMD flags for x86/ARM
if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64")
    set(SIMD_FLAGS "-mavx2")
elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "aarch64")
    set(SIMD_FLAGS "-mfpu=neon")
endif()

# Include directories
include_directories(${CMAKE_SOURCE_DIR})

# Link libraries
find_package(XXHash REQUIRED)

# Source files
add_executable(deduplication main.cpp xxhash_integration.cpp simd_optimization.cpp parallel_hashing.cpp ksm_simulation.cpp benchmark.cpp)

# Add SIMD optimization flags
target_compile_options(deduplication PRIVATE ${SIMD_FLAGS})

# Link the XXHash library
target_link_libraries(deduplication xxhash)
