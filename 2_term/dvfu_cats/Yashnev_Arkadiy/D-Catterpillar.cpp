#include <vector>
#include <iostream>

using namespace std;

enum state {
    descent = -1,
    climb = 1,
    end = 0,
};

int main() {
    size_t L, N; cin >> L >> N;
    size_t time = 0;

    vector<size_t> heights(N);
    vector<state> states(N);
    cin >> heights[0];
    for(size_t i = 1; i != N; ++i) {
        cin >> heights[i];
        states[i - 1] = heights[i - 1] < heights[i] ? climb : descent;
    }
    states.back() = state::end;

    int state_diff = 0;
    for(size_t i = 0; i != L; ++i) {
        state_diff += states[i];
    }

    for(size_t head = L - 1; head != N - 1; ++head, 
        state_diff += states[head] - states[head - L]) {
        if(state_diff >= 0 || states[head] == climb) {
            ++time;
        }
    }

    cout << time;
}
