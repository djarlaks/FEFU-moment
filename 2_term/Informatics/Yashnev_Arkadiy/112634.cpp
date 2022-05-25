// 112634
#include "iostream"

using std::cin, std::cout;
void dfs(int size, bool **arr, bool *visits, size_t id = 0);

int main() {
    int N;
    cin >> N;

    bool *visits = new bool[N];
    for (size_t i = 0; i < N; ++i) visits[i] = false;

    bool **arr = new bool*[N];
    for (size_t i = 0; i < N; ++i) {
        arr[i] = new bool[N];
        for (size_t j = 0; j < N; ++j) {
            cin >> arr[i][j];
        }
    }

    dfs(N, arr, visits);
    int sum = 0;
    for (size_t i = 0; i < N; ++i) {
        if (visits[i]) ++sum;
        delete[] arr[i];
    }

    if (sum == N) cout << "YES";
    else cout << "NO";

    delete[] arr;
    return 0;
}

void dfs(int size, bool **arr, bool *visits, size_t id) {
    visits[id] = true;
    for (size_t i = 0; i < size; ++i) {
        if (arr[id][i] && !visits[i]) {
            dfs(size, arr, visits, i);
        }
    }
}
