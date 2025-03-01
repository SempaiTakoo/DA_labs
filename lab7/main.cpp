#include <iostream>
#include <vector>
#include <climits>
#include <chrono>

using namespace std;

int main() {
    long long n, m;
    cin >> n >> m;

    vector<vector<long long>> A(n, vector<long long>(m));
    for (long long i = 0; i < n; ++i) {
        for (long long j = 0; j < m; ++j) {
            cin >> A[i][j];
        }
    }

    vector<vector<long long>> dp(n, vector<long long>(m, LLONG_MAX));

    vector<vector<long long>> parent(n, vector<long long>(m, -1));

    for (long long j = 0; j < m; ++j) {
        dp[0][j] = A[0][j];
    }

    auto start = chrono::high_resolution_clock::now();

    for (long long i = 1; i < n; ++i) {
        for (long long j = 0; j < m; ++j) {

            for (long long dj = -1; dj <= 1; ++dj) {
                long long prev_j = j + dj;
                if (prev_j >= 0 && prev_j < m) {
                    long long cost = dp[i - 1][prev_j] + A[i][j];
                    if (cost < dp[i][j]) {
                        dp[i][j] = cost;
                        parent[i][j] = prev_j;
                    }
                }
            }
        }
    }

    long long min_cost = LLONG_MAX;
    long long min_index = -1;
    for (long long j = 0; j < m; ++j) {
        if (dp[n - 1][j] < min_cost) {
            min_cost = dp[n - 1][j];
            min_index = j;
        }
    }

    cout << min_cost << endl;

    vector<pair<long long, long long>> path;
    long long i = n - 1;
    while (i >= 0) {
        path.push_back({i + 1, min_index + 1});
        min_index = parent[i][min_index];
        --i;
    }

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << elapsed.count() << " seconds\n";


    // for (long long i = path.size() - 1; i >= 0; --i) {
    //     cout << "(" << path[i].first << "," << path[i].second << ") ";
    // }
    // cout << endl;

    return 0;
}
