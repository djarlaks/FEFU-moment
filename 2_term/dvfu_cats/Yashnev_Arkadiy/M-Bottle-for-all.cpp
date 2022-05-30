#include <set>
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    size_t N, M; fin >> N >> M;
    long long sum = 0;
    multiset<int> thirst;

    for(size_t i = 0; i != N; ++i) {
        int in; fin >> in; sum += in;
        thirst.insert(in);
    }

    for(size_t i = 0; i != M && sum != 0; ++i) {
        auto max = thirst.rbegin();
        auto res = *max / 10;
        sum -= *max - res;
        thirst.erase(thirst.find(*max));
        thirst.insert(res);
    }

    fout << sum;
}
