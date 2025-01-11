#include "deduplication.h"
#include <unordered_set>
#include <iostream>
#include <fstream>  // Include for file operations

// Function to deduplicate the dataset and return duplicate count and memory saved
std::tuple<std::vector<std::string>, int, size_t> deduplicate_and_count(const std::vector<std::string>& dataset) {
    std::unordered_set<std::string> unique_data;
    std::vector<std::string> deduplicated_data;
    int duplicate_count = 0;
    size_t memory_saved = 0;

    // Iterate through the dataset and add to the set
    for (const auto& data : dataset) {
        if (unique_data.find(data) == unique_data.end()) {
            unique_data.insert(data);
            deduplicated_data.push_back(data);
        } else {
            duplicate_count++;
            size_t duplicate_size = data.size();  // Get the size of the duplicate

            // Debugging output to confirm size
           // std::cout << "Duplicate found: " << data << ", size: " << duplicate_size << " bytes" << std::endl;

            memory_saved += duplicate_size;  // Add the size of the duplicate to memory saved
        }
    }

    // Debugging output to confirm memory saved
    //std::cout << "Total memory saved: " << memory_saved << " bytes" << std::endl;

    return {deduplicated_data, duplicate_count, memory_saved};
}



// Function to save the deduplicated data to a file
void save_deduplicated_data(const std::string& output_file, const std::vector<std::string>& deduplicated_data) {
    std::ofstream out_file(output_file);

    // Check if file is successfully opened
    if (out_file.is_open()) {
        // Iterate through the deduplicated data and write to the file
        for (const auto& data : deduplicated_data) {
            out_file << data << "\n";
        }

        out_file.close();  // Close the file after writing
        // This should only print once to indicate the data was saved
        std::cout << "Deduplicated data saved to: " << output_file << std::endl;
    } else {
        std::cerr << "Error opening file for writing: " << output_file << std::endl;
    }
}
