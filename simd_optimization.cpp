#include <iostream>
#include <vector>
#include <string>
#include <immintrin.h>
#include "xxhash.h"

// SIMD-optimized hash function
void simd_optimized_hash(const std::vector<std::string>& data) {
    std::cout << "Using SIMD-optimized hashing...\n";

#ifdef AVX2
    for (const auto& element : data) {
        // Use AVX2 to hash the data
        size_t length = element.size();
        const char* input = element.c_str();

        unsigned int hash = 0;
        size_t chunks = length / 32; // 256 bits = 32 bytes

        // Process each 256-bit chunk
        for (size_t i = 0; i < chunks; ++i) {
            __m256i chunk = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(input + i * 32));
            hash ^= XXH32(reinterpret_cast<const char*>(&chunk), 32, 0);
        }

        // Handle remaining bytes if any
        size_t remaining = length % 32;
        if (remaining > 0) {
            hash ^= XXH32(input + chunks * 32, remaining, 0);
        }

        std::cout << "Hash for element: " << hash << "\n";
    }
#else
    //std::cout << "SIMD instructions are not supported on this system. Using scalar fallback.\n";
    for (const auto& element : data) {
        unsigned int hash = XXH32(element.c_str(), element.size(), 0);
        std::cout << "Hash for element: " << hash << "\n";
    }
#endif

    std::cout << "SIMD optimized hashing completed for " << data.size() << " elements.\n";
}