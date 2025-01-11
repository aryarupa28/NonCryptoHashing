#include <fstream>
#include <vector>
#include <string>
#include "dataset_loader.h"
#include <iostream>


std::vector<std::string> load_dataset(const std::string& dataset_path) {
    std::vector<std::string> dataset;
    std::ifstream input_file(dataset_path);

    if (input_file.is_open()) {
        std::string line;
        while (getline(input_file, line)) {
            dataset.push_back(line);
        }
        input_file.close();
    } else {
        std::cerr << "Error opening file: " << dataset_path << std::endl;
    }

    return dataset;
}
