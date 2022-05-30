#include <fstream>
#include <vector>
#include <functional>

using namespace std;

struct Heap {
    vector<int> data;
    function<bool(int, int)> pred;

    Heap(size_t size, function<bool(int, int)> p) {
        data = vector<int>();
        data.reserve(size);
        pred = p;
    }

    void insert(int elem) {
        data.push_back(elem);
        size_t len = data.size() - 1;
        bubble_up(len);
    }

    void bubble_up(size_t idx) {
        if(idx == 0) return;

        size_t parent = (idx - 1) / 2;
        if(pred(data[idx], data[parent])) {
            swap(data[idx], data[parent]);
            bubble_up(parent);
        }
    }

    void bubble_down(size_t idx) {
        size_t l = 2 * idx + 1;
        size_t r = 2 * idx + 2;
        size_t size = data.size();
        size_t least = idx;

        if(l < size && pred(data[l], data[least])) {
            least = l;
        }

        if(r < size && pred(data[r], data[least])) {
            least = r;
        }

        if(least != idx) {
            swap(data[idx], data[least]);
            bubble_down(least);
        }
    }

    int extract() {
        int root = data[0];
        int last = data.back();
        data.pop_back();
        data[0] = last;
        bubble_down(0);
        return root;
    }
};

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");
    size_t size; fin >> size;

    auto min = [](int a, int b) { return a < b; };
    auto max = [](int a, int b) { return a > b; };
    Heap top_nums(size, min);
    Heap bot_nums(size, max);

    for(size_t i = 0; i != size; ++i) {
        int n; fin >> n;
        if(top_nums.data.size() != 0) {
            int top_min = top_nums.data[0];
            if(n > top_min) {
                top_nums.insert(n);
            } else {
                bot_nums.insert(n);
            }
        } else {
            bot_nums.insert(n);
        }

        while(top_nums.data.size() > bot_nums.data.size()) {
            bot_nums.insert(top_nums.extract());
        }

        while(top_nums.data.size() + 1 < bot_nums.data.size()) {
            top_nums.insert(bot_nums.extract());
        }

        fout << bot_nums.data[0] << " ";
    }
}