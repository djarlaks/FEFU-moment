#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    string str;
    getline(cin, str);
    auto vec = prefix(str);
    for(auto it : vec) {
        cout << it << " ";
    }
    cout << "\n";
    cout << vec.size() - vec.back();
    return 0;
}
