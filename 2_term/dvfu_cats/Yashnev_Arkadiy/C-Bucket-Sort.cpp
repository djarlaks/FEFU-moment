#pragma ide diagnostic ignored "misc-no-recursion"
#include <vector>
#include <string>
#include <fstream>

using std::vector, std::string;

size_t const LEN = 3;
size_t const ALPH_LEN = 52;

void bucket_sort(vector<string> &arr, int size);

int idx(char c) {
    if('A' <= c && c <= 'Z') {
        return (c - 'A');
    }
    return (c - 'a' + 26);
}

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");
    int N;
    fin >> N;
    vector<string> arr(N);

    for (int i = 0; i < N; ++i) fin >> arr[i];
    bucket_sort(arr, N);
    for (int i = 0; i < N; ++i) fout << arr[i] << '\n';

    fin.close();
    fout.close();
    return 0;
}

void sort_with_depth(vector<string*> &bucket, int lvl);

void bucket_sort(vector<string> &arr, int size) {
    vector<string *> pointers(size);
    for (int i = 0; i < size; ++i) pointers[i] = &arr[i];

    sort_with_depth(pointers, LEN);

    vector<string> answers(size);
    for(int i = 0; i < size; ++i) answers[i] = *pointers[i];
    for(int i = 0; i < size; ++i) arr[i] = answers[i];
}

void sort_with_depth(vector<string*> &bucket, int lvl) {
    if(bucket.empty() || (lvl == 0)) return;

    vector<vector<string*>> next_layer(ALPH_LEN);
    int index = (int) LEN - lvl;

    for(auto &word : bucket) {
        next_layer[idx((*word)[index])].push_back(word);
    }

    int count = 0;
    for(int i = 0; i < ALPH_LEN; ++i) {
        sort_with_depth(next_layer[i], lvl - 1);
        for(auto &word : next_layer[i]) {
            bucket[count] = word;
            ++count;
        }
    }
}
