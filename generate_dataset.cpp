#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <random>
#include <string>
#include <algorithm>

// Function to generate random strings
std::string generate_random_string(int length = 10) {
    static const char alphanum[] =
        "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sizeof(alphanum) - 2);

    std::string str;
    for (int i = 0; i < length; ++i) {
        str += alphanum[dis(gen)];
    }
    return str;
}

// Function to generate dataset
void generate_dataset(const std::string& file_name, int num_entries = 100000) {
    // Randomly generate duplicate ratio between 0 and 0.3
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(0.0, 0.3);  // Range from 0 to 0.3
    float duplicate_ratio = dis(gen);

    std::vector<std::string> dataset;
    std::unordered_set<std::string> unique_entries;
    int unique_entries_count = static_cast<int>(num_entries * (1 - duplicate_ratio));
    int duplicates_count = num_entries - unique_entries_count;

    // Create unique entries
    for (int i = 0; i < unique_entries_count; ++i) {
        dataset.push_back(generate_random_string(rand() % 16 + 5)); // Random strings of length 5 to 20
        unique_entries.insert(dataset.back());
    }

    // Create duplicates by sampling from unique entries
    std::vector<std::string> duplicates;
    for (int i = 0; i < duplicates_count; ++i) {
        duplicates.push_back(*std::next(unique_entries.begin(), rand() % unique_entries.size()));
    }

    // Combine dataset with duplicates
    dataset.insert(dataset.end(), duplicates.begin(), duplicates.end());
    std::random_shuffle(dataset.begin(), dataset.end());

    // Write the dataset to file
    std::ofstream outfile(file_name);
    for (const auto& entry : dataset) {
        outfile << entry << "\n";
    }
    outfile.close();

    // Print the generated duplicate ratio
    std::cout << "Generated dataset with " << num_entries << " entries, ";
    std::cout << duplicates_count << " duplicates, ";
    std::cout << "duplicate ratio: " << duplicate_ratio * 100 << "% saved to " << file_name << std::endl;
}

// Function to deduplicate the dataset and save to output file
void deduplicate_and_save(const std::string& input_file, const std::string& output_file) {
    std::ifstream infile(input_file);
    std::unordered_set<std::string> unique_entries;
    std::string line;

    // Read the dataset from the file
    while (std::getline(infile, line)) {
        unique_entries.insert(line);
    }

    // Write the unique entries to the output file
    std::ofstream outfile(output_file);
    for (const auto& entry : unique_entries) {
        outfile << entry << "\n";
    }

    infile.close();
    outfile.close();
    std::cout << "Deduplicated data saved to: " << output_file << std::endl;
}

int main() {
    std::string dataset_file = "external_dataset.txt";
    std::string output_file = "deduplicated_output.txt";
    int num_entries = 100000; // Default number of entries

    // Step 1: Generate dataset
    generate_dataset(dataset_file, num_entries);  // Random duplicate ratio

    // Step 2: Deduplicate and save the result
    deduplicate_and_save(dataset_file, output_file);

    return 0;
}
