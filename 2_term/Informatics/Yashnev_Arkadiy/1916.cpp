#include <iostream>
#include <string>

using std::cin, std::cout;

int const transition_table[8][4] = {
        /*    Цифра | E\e  |  .  | Знак */
        {1, -1, -1, 2},
        {1, 3, 4, -1},
        {1, -1, -1, -1},
        {5, -1, -1, 6},
        {7, -1, -1, -1},
        {5, -1, -1, -1},
        {5, -1, -1, -1},
        {7, 3, -1, -1}
};

bool ans[] = { false, true, false, false, false, true, false, true };

int transit(int cur, char next) {
    if('0' <= next && next <= '9') return transition_table[cur][0];
    else if(next == 'E' || next == 'e') return transition_table[cur][1];
    else if(next == '.') return transition_table[cur][2];
    else if(next == '-' || next == '+') return transition_table[cur][3];

    return -1;
}

int main() {
    std::string input; cin >> input;

    int state = 0;
    for(auto it : input) {
        if((state = transit(state, it)) == -1) break;
    }

    if(state == -1 || !ans[state]) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
    }
}
