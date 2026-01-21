#include <iostream>
#include <fstream>
#include <random>
#include <cstdint>
#include <cstdlib>

int main(int argc, char* argv[]) {
    // Check if correct number of arguments are provided
    if (argc < 3 || argc > 5) {
        std::cerr << "Usage: " << argv[0] << " <number_of_randoms> <output_file> [min_limit] [max_limit]" << std::endl;
        std::cerr << "Example: " << argv[0] << " 10 output.txt" << std::endl;
        std::cerr << "Example: " << argv[0] << " 10 output.txt 100" << std::endl;
        std::cerr << "Example: " << argv[0] << " 10 output.txt 100 1000" << std::endl;
        std::cerr << "\nmin_limit and max_limit are optional and default to 0 and " << UINT32_MAX << " respectively" << std::endl;
        return 1;
    }

    // Parse command line arguments
    int count = std::atoi(argv[1]);
    std::string output_file = argv[2];

    // Parse optional limits (defaults to 0 and UINT32_MAX)
    uint32_t min_limit = 0;
    uint32_t max_limit = UINT32_MAX;

    if (argc >= 4) {
        unsigned long long temp = std::strtoull(argv[3], nullptr, 10);
        if (temp > UINT32_MAX) {
            std::cerr << "Error: Min limit exceeds uint32_t max" << std::endl;
            return 1;
        }
        min_limit = static_cast<uint32_t>(temp);
    }

    if (argc == 5) {
        unsigned long long temp = std::strtoull(argv[4], nullptr, 10);
        if (temp > UINT32_MAX) {
            std::cerr << "Warning: Max limit exceeds uint32_t max, using " << UINT32_MAX << std::endl;
            max_limit = UINT32_MAX;
        }
        else if (temp == 0) {
            std::cerr << "Error: Max limit must be positive (greater than 0)" << std::endl;
            return 1;
        }
        else {
            max_limit = static_cast<uint32_t>(temp);
        }
    }

    // Validate limits
    if (min_limit >= max_limit) {
        std::cerr << "Error: Min limit (" << min_limit << ") must be less than max limit (" << max_limit << ")" << std::endl;
        return 1;
    }

    // Validate count
    if (count <= 0) {
        std::cerr << "Error: Number of random numbers must be positive" << std::endl;
        return 1;
    }

    // Setup random number generator
    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<uint32_t> dist(min_limit, max_limit);

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
    std::cout << "Successfully generated " << count << " random numbers (" << min_limit << " to " << max_limit << ") to " << output_file << std::endl;

    return 0;
}
