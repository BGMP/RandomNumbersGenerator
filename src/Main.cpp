#include <iostream>
#include <fstream>
#include <random>
#include <cstdint>
#include <cstdlib>

int main(int argc, char* argv[]) {
    // Check if correct number of arguments are provided
    if (argc < 3 || argc > 4) {
        std::cerr << "Usage: " << argv[0] << " <number_of_randoms> <output_file> [max_limit]" << std::endl;
        std::cerr << "Example: " << argv[0] << " 10 output.txt" << std::endl;
        std::cerr << "Example: " << argv[0] << " 10 output.txt 1000" << std::endl;
        std::cerr << "\nmax_limit is optional and defaults to " << UINT32_MAX << " (uint32_t max)" << std::endl;
        return 1;
    }

    // Parse command line arguments
    int count = std::atoi(argv[1]);
    std::string output_file = argv[2];

    // Parse optional upper limit (defaults to UINT32_MAX)
    uint32_t max_limit = UINT32_MAX;
    if (argc == 4) {
        unsigned long long temp = std::strtoull(argv[3], nullptr, 10);
        if (temp > UINT32_MAX) {
            std::cerr << "Warning: Limit exceeds uint32_t max, using " << UINT32_MAX << std::endl;
            max_limit = UINT32_MAX;
        }
        else if (temp == 0) {
            std::cerr << "Error: Limit must be positive (greater than 0)" << std::endl;
            return 1;
        }
        else {
            max_limit = static_cast<uint32_t>(temp);
        }
    }

    // Validate count
    if (count <= 0) {
        std::cerr << "Error: Number of random numbers must be positive" << std::endl;
        return 1;
    }

    // Setup random number generator
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<uint32_t> dist(0, max_limit);

    // Open output file
    std::ofstream outfile(output_file);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << output_file << std::endl;
        return 1;
    }

    // Generate and write random numbers
    for (int i = 0; i < count; i++) {
        uint32_t random_num = dist(gen);
        outfile << random_num << std::endl;
    }

    outfile.close();
    std::cout << "Successfully generated " << count << " random numbers (0 to " << max_limit << ") to " << output_file << std::endl;

    return 0;
}
