#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <chrono>

// Implementación de DecToHex
std::string DecToHex(int decimal) {
    std::stringstream ss;
    ss << std::hex << decimal;
    return ss.str();
}

// Implementación de HexToDec
int HexToDec(const std::string& hex) {
    int decimal;
    std::stringstream ss;
    ss << std::hex << hex;
    ss >> decimal;
    return decimal;
}

int main() {
    std::vector<int> test_numbers = {0, 1, 15, 16, 255, 1024, 65535, 1048576, 2147483647};
    const int repeats = 10000;

    // Mido DecToHex
    auto start = std::chrono::high_resolution_clock::now();
    for (int r = 0; r < repeats; ++r)
        for (int n : test_numbers)
            DecToHex(n);
    auto mid = std::chrono::high_resolution_clock::now();

    // Mido HexToDec
    for (int r = 0; r < repeats; ++r)
        for (int n : test_numbers)
            HexToDec(DecToHex(n));
    auto end = std::chrono::high_resolution_clock::now();

    double time_dh = std::chrono::duration<double>(mid - start).count();
    double time_hd = std::chrono::duration<double>(end - mid).count();
    int total_calls = test_numbers.size() * repeats;

    std::cout << "DecToHex: total " << time_dh << " s, avg "
              << (time_dh / total_calls) << " s/call\n";
    std::cout << "HexToDec: total " << time_hd << " s, avg "
              << (time_hd / total_calls) << " s/call\n";

    return 0;
}
