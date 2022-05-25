#include <iostream>
#include <vector>
#include <string>

using std::vector, std::string, std::cin, std::cout;

vector<size_t> prefix(string const &str) {
    auto size = str.size();

    vector<size_t> prefix(size);
    for(size_t i = 1; i != size; ++i) {
        auto j = prefix[i - 1];
        while(j > 0 && str[i] != str[j]) {
            j = prefix[j - 1];
        }

        if(str[i] == str[j]) ++j;
        prefix[i] = j;
    }

    return prefix;
}

int main() {
    string input;
    cin >> input;
    auto pref = prefix(input);
    for(auto it : pref) {
        cout << it << " ";
    }
}
