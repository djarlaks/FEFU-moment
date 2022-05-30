#include <fstream>
#include <vector>

using namespace std;

int main() {
    ifstream fin("heapsort.in");
    ofstream fout("heapsort.out");
    int n; fin >> n;

    vector<int> heap(n);
    heap[0] = 1;
    int cur = 0;

    for(int i = 1; i != n; ++i) {
        for(int j = cur + 1; j > 1; j /= 2) {
            heap[j - 1] = heap[j / 2 - 1];
        }
        heap[0] = i + 1;
        heap[++cur] = 1;
    }

    for(auto it : heap) {
        fout << it << " ";
    }
}
