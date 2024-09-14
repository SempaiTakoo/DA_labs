#include <iostream>
#include <map>
#include <chrono>
#include <random>
#include <string>
#include <algorithm>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <cstdlib>
#include <cctype>
#include "main.cpp"

int main() {
    // Генератор случайных чисел и строк
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 25);
    std::uniform_int_distribution<> num(0, 1000000);

    const int testSize = 10000;
    std::vector<std::string> words;
    for (int i = 0; i < testSize; ++i) {
        std::string word;
        for (int j = 0; j < 10; ++j) {
            word += 'a' + dis(gen);
        }
        words.push_back(word);
    }

    // Бенчмарк декартового дерева
    node *root = nullptr;
    auto start = std::chrono::high_resolution_clock::now();

    for (const auto &word : words) {
        insert(root, new node(word.c_str(), num(gen)));
    }
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertTimeTreap = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (const auto &word : words) {
        search(root, word.c_str());
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> searchTimeTreap = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (const auto &word : words) {
        remove(root, word.c_str());
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removeTimeTreap = end - start;

    // Бенчмарк std::map
    std::map<std::string, uint64_t> map;
    start = std::chrono::high_resolution_clock::now();
    for (const auto &word : words) {
        map[word] = num(gen);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insertTimeMap = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (const auto &word : words) {
        map.find(word);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> searchTimeMap = end - start;

    start = std::chrono::high_resolution_clock::now();
    for (const auto &word : words) {
        map.erase(word);
    }
    end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> removeTimeMap = end - start;

    std::cout << "Treap Insertion: " << insertTimeTreap.count() << " seconds\n";
    std::cout << "Treap Search: " << searchTimeTreap.count() << " seconds\n";
    std::cout << "Treap Removal: " << removeTimeTreap.count() << " seconds\n";

    std::cout << "Map Insertion: " << insertTimeMap.count() << " seconds\n";
    std::cout << "Map Search: " << searchTimeMap.count() << " seconds\n";
    std::cout << "Map Removal: " << removeTimeMap.count() << " seconds\n";

    destroy(root);

    return 0;
}
