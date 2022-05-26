#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef unsigned long long u64;

vector<u64> find(string const &text, string const &pattern) {
    vector<u64> entry;
    auto t_size = text.size();
    auto p_size = pattern.size();

    for(u64 i = 0; i != t_size - p_size + 1; ++i) {
        for(u64 j = 0; j != p_size && text[i + j] == pattern[j]; ++j) {
            if(j == p_size - 1) {
                entry.push_back(i);
                break;
            }
        }
    }

    return entry;
}

int main() {
    string text, pattern;
    cin >> text >> pattern;

    auto ans = find(text, pattern);
    for(auto it : ans) {
        cout << it << " ";
    }
}