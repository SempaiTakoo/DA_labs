#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std;

vector<int> lcs(const vector<string>& A, const vector<string>& B) {
    size_t len_a = A.size(), len_b = B.size();
    vector<int> dp_curr(len_b + 1, 0), dp_prev(len_b + 1, 0);

    for (size_t i = 1; i <= len_a; ++i) {
        for (size_t j = 1; j <= len_b; ++j) {
            if (A[i - 1] == B[j - 1]) dp_curr[j] = dp_prev[j - 1] + 1;
            else dp_curr[j] = max(dp_curr[j - 1], dp_prev[j]);
        }
        swap(dp_prev, dp_curr);
    }

    return dp_prev;
}

vector<string> hirschberg_recursive(const vector<string>& A, const vector<string>& B) {
    size_t len_a = A.size(), len_b = B.size();

    if (len_a == 0 || len_b == 0) return {};
    if (len_a == 1) {
        return find(B.begin(), B.end(), A[0]) != B.end() ? vector<string>{A[0]} : vector<string>{};
    }
    if (len_b == 1) {
        return find(A.begin(), A.end(), B[0]) != A.end() ? vector<string>{B[0]} : vector<string>{};
    }

    size_t mid_a = len_a / 2;
    vector<int> lcs_score(len_b + 1, 0);

    vector<int> left_tmp = lcs(
          vector<string>(A.begin(), A.begin() + mid_a),
          vector<string>(B.begin(), B.end())
    );

    vector<int> right_tmp = lcs(
          vector<string>(A.rbegin(), A.rbegin() + (len_a - mid_a)),
          vector<string>(B.rbegin(), B.rend())
    );

    for (size_t i = 0; i <= len_b; ++i) {
        lcs_score[i] = left_tmp[i] + right_tmp[len_b - i];
    }

    size_t best_split = distance(lcs_score.begin(), max_element(lcs_score.begin(), lcs_score.end()));

    vector<string> left_part = hirschberg_recursive(
      vector<string>(A.begin(), A.begin() + mid_a),
      vector<string>(B.begin(), B.begin() + best_split)
    );
    vector<string> right_part = hirschberg_recursive(
      vector<string>(A.begin() + mid_a, A.end()),
      vector<string>(B.begin() + best_split, B.end())
    );

    left_part.insert(left_part.end(), right_part.begin(), right_part.end());
    return left_part;
}

vector<string> hirschberg(const vector<string>& A, const vector<string>& B) {
    return hirschberg_recursive(A, B);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    string line1, line2;
    getline(cin, line1);
    getline(cin, line2);

    istringstream iss1(line1), iss2(line2);
    vector<string> A((istream_iterator<string>(iss1)), istream_iterator<string>());
    vector<string> B((istream_iterator<string>(iss2)), istream_iterator<string>());

    vector<string> lcs = hirschberg(A, B);

    cout << lcs.size() << endl;
    for (const string& word : lcs) {
        cout << word << " ";
    }
    cout << endl;

    return 0;
}
