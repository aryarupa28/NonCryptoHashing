#include "environment_setup.h"
#include "deduplication.h"
#include "ksm_simulation.h"
#include "benchmark.h"
#include "parallel_hashing.h"
#include "dataset_loader.h"  
#include <iostream>
#include <unordered_map>
#include <vector>

int main() {
    std::string dataset_path = "external_dataset.txt";

    // Step 1: Environment Setup
    setup_environment();  // Ensure implementation exists in environment_setup.cpp

    // Step 2: Load Dataset
    auto dataset = load_dataset(dataset_path);
    if (dataset.empty()) {
        std::cerr << "Dataset is empty or could not be loaded!" << std::endl;
        return 1;
    }

    // Perform deduplication and count duplicates and memory savings
    std::cout << "Starting deduplication..." << std::endl;
   auto [deduplicated_data, duplicate_count, memory_saved] = deduplicate_and_count(dataset);


    /* Print the deduplicated data
    std::cout << "\nDeduplicated Data:" << std::endl;
    for (const auto& data : deduplicated_data) {  // Use the correct deduplicated dataset
        std::cout << data << std::endl;
    }*/

    // Save the deduplicated data to a file
    save_deduplicated_data("deduplicated_output.txt", deduplicated_data);

    // Display the statistics only once
    std::cout << "\nTotal Pages: " << dataset.size() << std::endl;
    std::cout << "Unique Pages: " << dataset.size() - duplicate_count << std::endl;
    std::cout << "Duplicate Pages: " << duplicate_count << std::endl;
    // Display the memory saved, in bytes if it's less than 1 KB
if (memory_saved < 1024) {
    std::cout << "Memory Saved: " << memory_saved << " bytes" << std::endl;
} else {
    std::cout << "Memory Saved: " << (memory_saved / 1024) << " KB" << std::endl;
}




    // Step 6: Simulate Kernel Same-page Merging (KSM)
    simulate_ksm(deduplicated_data);  // Pass the deduplicated dataset to the KSM simulation function

    // Step 8: Run Benchmarks
    run_benchmarks();  // Ensure benchmarking logic is correctly implemented

    // Step 9: Test Parallel Hashing
    test_parallel_hashing(deduplicated_data);  // Test parallel hashing with the deduplicated dataset

    std::cout << "Integration complete. System is ready for use." << std::endl;
    return 0;
}