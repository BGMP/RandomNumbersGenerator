#include <iostream>
#include <fstream>
#include <random>
#include <cstdint>

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " <number_of_randoms> <output_file>" << std::endl;
        std::cerr << "Example: " << argv[0] << " 10 output.txt" << std::endl;
        return 1;
    }

    int count = std::atoi(argv[1]);
    std::string output_file = argv[2];

    if (count <= 0) {
        std::cerr << "Error: Number of random numbers must be positive" << std::endl;
        return 1;
    }

    std::random_device rd;  // Seed
    std::mt19937 gen(rd()); // Mersenne Twister engine
    std::uniform_int_distribution<uint32_t> dist(0, UINT32_MAX);

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
    std::cout << "Successfully generated " << count << " random numbers to " << output_file << std::endl;

    return 0;
}
