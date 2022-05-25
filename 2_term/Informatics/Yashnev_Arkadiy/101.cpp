#include <iostream>
#include <string>
#include <vector>

using std::string, std::cin, std::cout, std::vector;

vector<int> prefix(string const &str) {
    vector<int> prefix(str.size());

    for(size_t i = 1; i != str.size(); ++i) {
        while(i + prefix[i] < str.size() && str[prefix[i]] == str[i + prefix[i]]) {
            ++prefix[i];
        }
    }

    return prefix;
}

int main() {
    string str;
    cin >> str; 
    auto z = prefix(str);
    for(auto it : z) {
        cout << it << " ";
    }
    cout << "\n";
}