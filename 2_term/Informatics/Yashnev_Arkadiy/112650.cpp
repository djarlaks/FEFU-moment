#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    size_t n; cin >> n;
    vector<vector<int>> graph(n, vector<int>(n));
    vector<pair<int, int>> ostov(n - 1);
    vector<int> colors(n);
    for(size_t i = 0; i != n; ++i) {
        colors[i] = i;
    }

    for(auto &it : graph) {
        for(auto &it : it) {
            cin >> it;
        }
    }

    for(size_t k = 0; k != n - 1; ++k) {
        int min_dist = INT32_MAX;
        int i_min, j_min;
        for(size_t i = 0; i != n; ++i) {
            for(size_t j = 0; j != n; ++j) {
                int cur = graph[i][j];
                if(colors[i] != colors[j] && cur < min_dist && cur != 0) {
                    i_min = i;
                    j_min = j;
                    min_dist = cur;
                }
            }
        }
        ostov[k].first = i_min;
        ostov[k].second = j_min;
        int c = colors[j_min];
        for(size_t i = 0; i != n; ++i) {
            if(colors[i] == c) {
                colors[i] = colors[i_min];
            }
        }
    }

    sort(ostov.begin(), ostov.end());
    for(auto const &it : ostov) {
        cout << it.first + 1 << " " << it.second + 1 << "\n";
    }
}
