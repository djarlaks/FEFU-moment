#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct BridgeCount {
    size_t single_color;
    size_t multi_color;

    BridgeCount() = default;
};

struct node {
    bool has_bridge;
    bool checked;
};

int main() {
    size_t size; cin >> size;
    vector<vector<node>> graph(size, vector<node>(size));
    vector<string> countries(size);

    for(auto &i : graph) {
        for(auto &j : i) {
            cin >> j.has_bridge;
        }
    }

    for(auto &it : countries) {
        cin >> it;
    }

    BridgeCount bc{};
    for(size_t i = 0; i != size; ++i) {
        for(size_t j = 0; j != size; ++j) {
            if(i != j && !graph[i][j].checked && graph[i][j].has_bridge) {
                countries[i] == countries[j] ? ++bc.single_color : ++bc.multi_color;
                graph[i][j].checked = graph[j][i].checked = true;
            }
        }
    }

    cout << bc.single_color << " " << bc.multi_color;
}