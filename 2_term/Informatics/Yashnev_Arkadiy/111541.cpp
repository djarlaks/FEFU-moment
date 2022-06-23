#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> graph;
vector<bool> used;
bool ans;

void dfs(int v, int father) {
    used[v] = true;
    for (auto point : graph[v]) {
        if (point == father)
            continue;
        if (!used[point]) {
            dfs(point, v);
        } else {
            ans = false;
            break;
        }
    }
}

int main() {
    int n; cin >> n;

    graph.resize(n);
    used.resize(n, false);

    int ribs = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int num; cin >> num;
            if (num == 1) {
                graph[i].push_back(j);
                ribs++;
            }
        }
    }

    ans = true;
    ribs /= 2;
    if (ribs == n - 1) {
        dfs(0, -1);
    } else {
        cout << "NO";
        return 0;
    }

    if(ans) cout << "YES";
    else cout << "NO";

    return 0;
}
