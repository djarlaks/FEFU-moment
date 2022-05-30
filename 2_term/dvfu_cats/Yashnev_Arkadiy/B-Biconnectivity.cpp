#include "fstream"
#include "vector"
 
#define in_min(a, b) (in[a] < in[b] ? (a) : (b))
int *in, *up, timer = 0;
std::vector<std::vector<int>> graph;
std::vector<int> answers;
void DFS_finding_articulations(int, int);
 
int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int N, M;
    fin >> N >> M;
    graph.resize(N);
    in = new int[N]{0};
    up = new int[N];
    for (int i = 0; i < N; ++i) up[i] = i;
 
    for (int line = 0, num1, num2; line < M; ++line) {
        fin >> num1 >> num2;
        graph[num1 - 1].push_back(num2 - 1);
        graph[num2 - 1].push_back(num1 - 1);
    }
    DFS_finding_articulations(0, -1);
    fout << answers.size();
    for (int num : answers) fout << ' ' << num + 1;
 
    delete[] in;
    delete[] up;
    fin.close();
    fout.close();
    return 0;
}
 
void DFS_finding_articulations(int cell_id, int father_id) {
    in[cell_id] = ++timer;
    bool articulation_flag = false;
    int children = 0;
    for (int sun_id : graph[cell_id]) {
        if ((sun_id != father_id) && (in[sun_id] < in[cell_id])) {
            if (in[sun_id] == 0) {
                ++children;
                DFS_finding_articulations(sun_id, cell_id);
                if(in[up[sun_id]] >= in[cell_id]) articulation_flag = true;
                up[cell_id] = in_min(up[cell_id], up[sun_id]);
            }
            else up[cell_id] = in_min(up[cell_id], sun_id);
        }
    }
    if ((father_id == -1) && (children < 2)) articulation_flag = false;
    if (articulation_flag) answers.push_back(cell_id);
}
