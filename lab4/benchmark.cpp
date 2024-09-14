#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <chrono>
#include <fstream>
#include "main.cpp"

void benchmarkZFunction(const std::string& txt, const std::string& pat) {
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<int> positions = searchPattern(txt, pat);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "Z-function search duration: " << duration.count() << " seconds" << std::endl;
}

void benchmarkStdSearch(const std::string& txt, const std::string& pat) {
    auto start = std::chrono::high_resolution_clock::now();
    auto it = std::search(txt.begin(), txt.end(), pat.begin(), pat.end());
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    std::cout << "std::search duration: " << duration.count() << " seconds" << std::endl;

    if (it != txt.end()) {
        std::cout << "Pattern found at position: " << std::distance(txt.begin(), it) << std::endl;
    } else {
        std::cout << "Pattern not found." << std::endl;
    }
}

int main() {
    std::srand(static_cast<unsigned int>(std::time(0)));

    const int TEXT_LENGTH = 100000;
    const int PATTERN_LENGTH = 5;

    std::string txt(TEXT_LENGTH, ' ');
    std::string pat(PATTERN_LENGTH, ' ');

    for (int i = 0; i < TEXT_LENGTH; ++i) {
        txt[i] = 'a' + std::rand() % 26;
    }

    for (int i = 0; i < PATTERN_LENGTH; ++i) {
        pat[i] = 'a' + std::rand() % 26;
    }

    std::cout << "Generated text and pattern:" << std::endl;
    std::cout << "Text: " << txt.substr(0, 100) << "..." << std::endl;
    std::cout << "Pattern: " << pat << std::endl;

    benchmarkZFunction(txt, pat);
    benchmarkStdSearch(txt, pat);

    return 0;
}
