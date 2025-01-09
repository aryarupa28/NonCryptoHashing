#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include "xxhash.h"

// Global mutex for result synchronization
std::mutex result_mutex;

// Thread function to compute hash for a chunk
void hash_chunk(const char* data, size_t start, size_t length, unsigned int& result) {
    unsigned int chunk_hash = XXH32(data + start, length, 0);
    std::lock_guard<std::mutex> lock(result_mutex);
    result ^= chunk_hash; // Combine hashes (e.g., XOR for simplicity)
}

int test_parallel_hashing(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <input_string>" << std::endl;
        return 1;
    }

    const char* input = argv[1];
    size_t length = strlen(input);

    const size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = length / num_threads;

    std::vector<std::thread> threads;
    unsigned int result = 0;

    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t chunk_length = (i == num_threads - 1) ? length - start : chunk_size;
        threads.emplace_back(hash_chunk, input, start, chunk_length, std::ref(result));
    }

    // Join threads
    for (auto& thread : threads) {
        thread.join();
    }

    std::cout << "Final Hash: " << result << std::endl;

    return 0;
}
