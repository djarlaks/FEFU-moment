#include <fstream>
#include <string>

using std::string, std::getline;

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    string input;

    getline(fin, input);

    bool was_capital = false;
    for(auto it : input) {
        if('A' <= it && it <= 'Z') {
            was_capital = true;
        } else if('a' <= it && it <= 'z' && was_capital) {
            fout << "NO\n";
            return 0;
        }
    }

    fout << "YES\n";
}