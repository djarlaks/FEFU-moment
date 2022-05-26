#include <iostream>
#include <string>
#include <vector>

using namespace std;
typedef unsigned long long u64;

vector<u64> find(string const &text, string const &pattern) {
    vector<u64> ans;
    auto p_size = pattern.size();
    auto t_size = text.size();
    u64 p_sum = 0, t_sum = 0;

    for(u64 i = 0; i != p_size; ++i) {
        p_sum += pattern[i] - 'a' + 1;
        t_sum += text[i] - 'a' + 1;
    }

    for(u64 i = 0; i < t_size - p_size + 1; ++i) {
        if(p_sum == t_sum) {
            bool is_substring = true;
            for(u64 j = 0; j != p_size / 2 + 1; ++j) {
                if(text[i + j] != pattern[j] || pattern[p_size - j - 1] != text[p_size + i - j - 1]) {
                    is_substring = false;
                    break;
                }
            }

            if(is_substring) {
                ans.push_back(i);
            }
        }

        t_sum += -(text[i] - 'a' + 1) + (text[i + p_size] - 'a' + 1);
    }

    return ans;
}

int main() {
    string text, pattern;
    cin >> text >> pattern;

    auto ans = find(text, pattern);
    for(auto it : ans) {
        cout << it << " ";
    }
}