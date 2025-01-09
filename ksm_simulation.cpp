#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <cstring>
#include "xxhash.h"

// Memory page size (4 KB)
const size_t PAGE_SIZE = 4096;

// Function to generate synthetic memory data
std::vector<std::string> generate_memory_data(size_t num_pages) {
    std::vector<std::string> memory_data;
    for (size_t i = 0; i < num_pages; ++i) {
        if (i % 5 == 0) {
            // Introduce duplicate pages every 5 pages
            memory_data.push_back("Duplicate_Page_Data_" + std::to_string(i / 5));
        } else {
            memory_data.push_back("Unique_Page_Data_" + std::to_string(i));
        }
    }
    return memory_data;
}

// Function to simulate KSM
void simulate_ksm(const std::vector<std::string>& memory_data) {
    std::unordered_set<unsigned int> unique_hashes;
    size_t total_pages = memory_data.size();
    size_t duplicate_pages = 0;

    for (const auto& page : memory_data) {
        unsigned int hash = XXH32(page.c_str(), page.size(), 0);
        if (unique_hashes.find(hash) != unique_hashes.end()) {
            duplicate_pages++;
        } else {
            unique_hashes.insert(hash);
        }
    }

    std::cout << "Total Pages: " << total_pages << std::endl;
    std::cout << "Duplicate Pages: " << duplicate_pages << std::endl;
    std::cout << "Unique Pages: " << unique_hashes.size() << std::endl;
    std::cout << "Memory Saved: " << (duplicate_pages * PAGE_SIZE) / 1024.0 << " KB" << std::endl;
}

// Function to be called from main.cpp
void ksm_simulation() {
    size_t num_pages = 1000; // Simulate 1000 memory pages
    std::vector<std::string> memory_data = generate_memory_data(num_pages);

    //std::cout << "Simulating Kernel Same-page Merging (KSM)..." << std::endl;
    simulate_ksm(memory_data);
}
