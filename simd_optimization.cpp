#include <iostream>
#include <vector>
#include <string>
#include <immintrin.h>
#include "xxhash.h"

// SIMD-optimized hash function
// SIMD-optimized hash function
void simd_optimized_hash(const std::vector<std::string>& data) {
    std::cout << "Using SIMD-optimized hashing...\n";

#ifdef AVX2
    std::cout << "AVX2 optimization is enabled.\n";  // Ensure AVX2 is used

    for (const auto& element : data) {
        size_t length = element.size();
        const char* input = element.c_str();

        unsigned int hash = 0;
        size_t chunks = length / 32; // 256 bits = 32 bytes

        std::cout << "Processing element of length " << length << "...\n"; // Debugging output

        // Process each 256-bit chunk
        for (size_t i = 0; i < chunks; ++i) {
            __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(input + i * 32));
            unsigned int chunk_hash = XXH32(reinterpret_cast<const char*>(&chunk), 32, 0);
            hash ^= chunk_hash;

            // Debugging output for each chunk
            std::cout << "Processing chunk " << i << " of element (length: " << length << "), Hash: " << chunk_hash << "\n";
        }

        // Handle remaining bytes if any
        size_t remaining = length % 32;
        if (remaining > 0) {
            unsigned int remaining_hash = XXH32(input + chunks * 32, remaining, 0);
            hash ^= remaining_hash;
            // Debugging output for the remaining data
            std::cout << "Handling remaining " << remaining << " bytes, Hash: " << remaining_hash << "\n";
        }

        std::cout << "Hash for element: " << hash << "\n";
    }
#else
    std::cout << "AVX2 optimization is not available. Falling back to regular hashing.\n";
    // Fallback to regular hashing if AVX2 is not available
    for (const auto& element : data) {
        unsigned int hash = XXH32(element.c_str(), element.size(), 0);
        std::cout << "Hash for element: " << hash << "\n";
    }
#endif

    std::cout << "SIMD optimized hashing completed for " << data.size() << " elements.\n";
}
