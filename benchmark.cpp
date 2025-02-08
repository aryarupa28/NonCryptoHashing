#include <iostream>
#include <chrono>
#include <vector>
#include <string>
#include <cstring>
#include <thread>
#include <functional> // For std::function
#include "xxhash.h"

// Function to generate synthetic data
std::vector<std::string> generate_data(size_t num_elements, size_t element_size) {
    std::vector<std::string> data;
    for (size_t i = 0; i < num_elements; ++i) {
        data.push_back(std::string(element_size, 'A' + (i % 26))); // Repeating pattern
    }
    return data;
}

// Benchmark function
void benchmark(const std::string& description, const std::function<void()>& func) {
    auto start = std::chrono::high_resolution_clock::now();
    func();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << description << " took " << duration.count() << " seconds.\n";
}

// Single-threaded hashing
void hash_data(const std::vector<std::string>& data) {
    for (const auto& item : data) {
        volatile unsigned int hash = XXH32(item.c_str(), item.size(), 0); // Prevent optimization
    }
}

// Multithreaded hashing
void multithreaded_hash(const std::vector<std::string>& data) {
    const size_t num_threads = std::thread::hardware_concurrency();
    size_t chunk_size = data.size() / num_threads;

    std::vector<std::thread> threads;
    for (size_t i = 0; i < num_threads; ++i) {
        size_t start = i * chunk_size;
        size_t end = (i == num_threads - 1) ? data.size() : start + chunk_size;
        threads.emplace_back([&data, start, end]() {
            for (size_t j = start; j < end; ++j) {
                volatile unsigned int hash = XXH32(data[j].c_str(), data[j].size(), 0); // Prevent optimization
            }
        });
    }

    for (auto& thread : threads) {
        thread.join();
    }
}

// Function to be called from main.cpp
void run_benchmarks() {
    size_t num_elements = 100000; // Number of data elements
    size_t element_size = 1024;  // Size of each element in bytes

   std::cout << "Generating synthetic data...\n";
   auto data = generate_data(num_elements, element_size);

    std::cout << "Starting benchmarks...\n";

    // Benchmark single-threaded hashing
   // benchmark("Single-threaded hashing", [&]() { hash_data(data); });

    // Benchmark multithreaded hashing
    benchmark("Multithreaded hashing", [&]() { multithreaded_hash(data); });

    std::cout << "Benchmarks completed.\n";
}
