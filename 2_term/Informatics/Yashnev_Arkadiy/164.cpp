#include <iostream>
#include <queue>

using std::cin, std::cout, std::queue;
void dfs(int size, bool **arr, bool *visits, size_t id = 0);
void bfs(int size, bool **arr, bool *visits, queue<int> &q, size_t id = 0);

int main() {
    int N, id;
    cin >> N >> id;

    bool *visits = new bool[N]{};
    queue<int> q;

    bool **arr = new bool*[N];
    *arr = new bool[N * N];
    for(size_t i = 1; i < N; ++i) {
        arr[i] = arr[i - 1] + N;
    }
    for(size_t i = 0; i != N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            cin >> arr[i][j];
        }
    }

    bfs(N, arr, visits, q, id - 1); // <-------------------- ¬Ґ­пвм dfs/bfs вгв

    int sum = 0;
    for (size_t i = 0; i < N; ++i) {
        if (visits[i]) ++sum;
    }
    cout << sum;

    delete[] *arr;
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

void bfs(int size, bool **arr, bool *visits, queue<int> &q, size_t id) {
    visits[id] = true;
    for (size_t i = 0; i < size; ++i) {
        if (arr[id][i] && !visits[i]) {
            q.push((int) i);
            visits[i] = true;
        }
    }

    while(!q.empty()) {
        size_t new_id = q.front();
        q.pop();
        bfs(size, arr, visits, q, new_id);
    }
}
