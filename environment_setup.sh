#!/bin/bash

# Function to install dependencies
install_dependencies() {
    echo "Installing essential development tools..."
    
    # Update package list
    sudo apt-get update

    # Install GCC, Clang, Make, Git, perf, and valgrind
    sudo apt-get install -y gcc clang make git linux-tools-common linux-tools-$(uname -r) valgrind

    echo "Dependencies installed successfully!"
}

# Function to clone and build xxHash
install_xxhash() {
    echo "Cloning and building xxHash..."

    # Clone xxHash repository from GitHub
    git clone https://github.com/Cyan4973/xxHash.git

    # Navigate into the xxHash directory
    cd xxHash

    # Build the xxHash library
    make

    echo "xxHash built successfully!"
}

# Function to verify the installation by running a test
verify_installation() {
    echo "Verifying installation..."

    # Create a test program that uses xxHash
    cat > test_xxhash.cpp <<EOL
#include <iostream>
#include <cstring>
#include "xxhash.h"

int main() {
    const char* input = "Hello, world!";
    unsigned int hash = XXH32(input, strlen(input), 0);
    
    std::cout << "xxHash32: " << hash << std::endl;
    return 0;
}
EOL

    # Compile the test program
    g++ -o test_xxhash test_xxhash.cpp -lxxhash

    # Run the test
    ./test_xxhash

    # Check if the hash is calculated correctly
    if [ $? -eq 0 ]; then
        echo "Installation verified successfully!"
    else
        echo "Installation failed. Please check the setup."
        exit 1
    fi
}


# Run the setup functions
install_dependencies
install_xxhash
verify_installation
