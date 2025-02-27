#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>
#include <chrono>

using namespace std;


vector<int> LCS_score(const vector<string>& X, const vector<string>& Y) {
    size_t n = X.size(), m = Y.size();
    vector<int> dp_cur(m + 1, 0), dp_prev(m + 1, 0);

    for (size_t i = 1; i <= n; ++i) {
        for (size_t j = 1; j <= m; ++j) {
            if (X[i - 1] == Y[j - 1]) {
                dp_cur[j] = dp_prev[j - 1] + 1;
            }
            else {
                dp_cur[j] = max(dp_cur[j - 1], dp_prev[j]);
            }
        }
        swap(dp_prev, dp_cur);
    }

    return dp_prev;
}


vector<string> recursive_hirschberg(
    const vector<string>& X, const vector<string>& Y
) {
    size_t n = X.size(), m = Y.size();

    if (n == 0 || m == 0) {
        return {};
    }

    if (n == 1) {
        if (find(Y.begin(), Y.end(), X[0]) == Y.end()) {
            return vector<string>{};
        } else {
            return vector<string>{X[0]};
        }
    }

    if (m == 1) {
        if (find(X.begin(), X.end(), Y[0]) == X.end()) {
            return vector<string>{};
        } else {
            return vector<string>{Y[0]};
        }
    }

    size_t mid_x = n / 2;
    vector<int> lcs_score(m + 1, 0);

    vector<int> top_lcs_score = LCS_score(
        vector<string>(X.begin(), X.begin() + mid_x),
        vector<string>(Y.begin(), Y.end())
    );
    vector<int> bot_lcs_score = LCS_score(
        vector<string>(X.rbegin(), X.rbegin() + (n - mid_x)),
        vector<string>(Y.rbegin(), Y.rend())
    );

    for (size_t i = 0; i <= m; ++i) {
        lcs_score[i] = top_lcs_score[i] + bot_lcs_score[m - i];
    }

    size_t best_split = distance(
        lcs_score.begin(),
        max_element(lcs_score.begin(), lcs_score.end())
    );

    vector<string> left_part = recursive_hirschberg(
        vector<string>(X.begin(), X.begin() + mid_x),
        vector<string>(Y.begin(), Y.begin() + best_split)
    );
    vector<string> right_part = recursive_hirschberg(
        vector<string>(X.begin() + mid_x, X.end()),
        vector<string>(Y.begin() + best_split, Y.end())
    );

    left_part.insert(left_part.end(), right_part.begin(), right_part.end());
    return left_part;
}


vector<string> hirschberg(const vector<string>& X, const vector<string>& Y) {
    return recursive_hirschberg(X, Y);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);

    istringstream iss1(line1), iss2(line2);
    vector<string> X(
        (istream_iterator<string>(iss1)), istream_iterator<string>()
    );
    vector<string> Y(
        (istream_iterator<string>(iss2)), istream_iterator<string>()
    );

    auto start = chrono::high_resolution_clock::now();

    vector<string> lcs = hirschberg(X, Y);

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> elapsed = end - start;

    cout << elapsed.count() << " seconds\n";

    // cout << lcs.size() << endl;
    // for (const string& word : lcs) {
    //     cout << word << ' ';
    // }
    // cout << '\n';

    return 0;
}
