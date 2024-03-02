#include <iostream>
#include <chrono>
#include <algorithm>
#include <memory>
#include <vector>

#include "main.cpp"

bool cmp(const std::pair<size_t, size_t>& a, const std::pair<size_t, size_t>& b) {
    return a.first < b.first;
}

int main() {

    TVector<TPair> data;
    std::vector<std::pair<size_t, size_t>> benchmarkData;

    TPair pair;
    while (std::cin >> pair.key >> pair.value) {
        data.PushBack(pair);
        benchmarkData.push_back({pair.key, pair.value});
    }

    auto start1 = std::chrono::high_resolution_clock::now();
    Sort(data);
    auto finish1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    sort(benchmarkData.begin(), benchmarkData.end(), cmp);
    auto finish2 = std::chrono::high_resolution_clock::now();

    auto start3 = std::chrono::high_resolution_clock::now();
    stable_sort(benchmarkData.begin(), benchmarkData.end(), cmp);
    auto finish3 = std::chrono::high_resolution_clock::now();

    auto duration1 = std::chrono::duration_cast<std::chrono::microseconds>(finish1 - start1);
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(finish2 - start2);
    auto duration3 = std::chrono::duration_cast<std::chrono::microseconds>(finish3 - start3);
    std::cout << "my sort duration: " << duration1.count() << std::endl;
    std::cout << "std sort duration: " << duration2.count() << std::endl;
    std::cout << "std stable_sort duration: " << duration3.count() << std::endl;

    return 0;
}
