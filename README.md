# Non-Crypto Hashing R&D: Duplicate Content Detection

## Project Overview
This project focuses on leveraging **xxHash**, a high-performance non-cryptographic hashing algorithm, to detect duplicate content efficiently. The system is optimized using **SIMD (Single Instruction, Multiple Data)** instructions and multithreading for maximum performance. Additionally, it includes benchmarking and simulation of Kernel Same-page Merging (KSM) to explore memory deduplication.

---

## Features
- **High-Performance Hashing**: Uses xxHash for efficient non-cryptographic hashing.
- **SIMD Optimization**: Exploits SIMD instructions (e.g., AVX2, AVX-512, NEON) for accelerated processing.
- **Multithreading Support**: Processes large datasets in parallel for scalability.
- **KSM Simulation**: Simulates memory deduplication by detecting duplicate memory pages.
- **Benchmarking**: Profiles single-threaded and multithreaded hashing performance.

---

## Prerequisites
Ensure the following are installed on your system:
- GCC or Clang (for C++17 support)
- CMake (for build configuration)
- Git (for version control)
- xxHash library (automatically downloaded by the setup script)

---

## Installation

1. Clone the Repository:
   ```bash
   git clone https://github.com/aryarupa28/NonCryptoHashing.git
   cd NonCryptoHashing
   ```

2. Build the Project:
   ```bash
   mkdir build && cd build
   cmake ..
   make
   ```

3. Run the Program:
   ```bash
   ./main
   ```

---

## File Structure
- **env.sh**: Automates environment setup, including dependency installation.
- **xhash_integration.cpp**: Implements xxHash with system-type detection (ARM or x86).
- **simd_optimization.cpp**: SIMD-optimized hashing logic.
- **parallel_hashing.cpp**: Multithreaded hashing for scalability.
- **ksm_simulation.cpp**: Simulates memory deduplication.
- **benchmark.cpp**: Evaluates system performance.
- **main.cpp**: Integrates all components into a cohesive application.

---

## Benchmarks
The system provides detailed performance metrics, including:
- Execution time for single-threaded and multithreaded hashing.
- Throughput and efficiency of SIMD optimizations.

Example Output:
```
Single-threaded hashing took 0.014447 seconds.
Multithreaded hashing took 0.00812292 seconds.
Total Pages: 1000
Duplicate Pages: 200
Memory Saved: 800 KB
```

---
## License
This project is licensed under the MIT License. See the LICENSE file for details.
