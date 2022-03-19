#include <fstream>
#include <stack>
#include <vector>

// структура для наглядности чтобы эзотерический код не вызывал разрыв жопы
struct height {
    size_t height;
    int left_border, right_border;
};

int main() {
    std::ifstream fin("input.txt");
    std::ofstream fout("output.txt");

    size_t n; fin >> n;
    std::vector<height> heights(n, {
        0,
        -1, // -1 для ничем не заблокированного обзора
        -1
    });

    // в стэке будем временно хранить номера зданий (?) обзор которых не заблокирован
    std::stack<size_t> ids;

    for(size_t i = 0; i != n; ++i) {
        fin >> heights[i].height;
    }

    for(size_t i = 0; i != n; ++i) {
        // в этом цикле мы смотрим наткнулись ли мы на элемент больший чем последний вошедший в стэк
        // когда мы его обнаруживаем то помечаем что для данного элемента это является правой границей обзора
        while(!ids.empty() && heights[ids.top()].height < heights[i].height) {
            heights[ids.top()].right_border = (int) i;
            ids.pop();
        }
        // каждый раз мы должны добавлять новйы элемент на проверку
        ids.push((int) i);
    }

    // а вы знали что в стэке нет .clear()?? а я вот сегодня узнал
    while(!ids.empty()) ids.pop();

    for(size_t i = n - 1; i != SIZE_MAX; --i) {
        // то же самое но для левых границ
        while(!ids.empty() && heights[ids.top()].height < heights[i].height) {
            heights[ids.top()].left_border = (int) i;
            ids.pop();
        }
        ids.push(i);
    }

    for(int i = 0; i != n; ++i) {
        int ans = 0;
        if(heights[i].left_border >= 0) {
            ans = i - heights[i].left_border;
        }

        if(heights[i].right_border >= 0 &&
        (heights[i].right_border - i < ans || ans == 0)) {
            ans = heights[i].right_border - i;
        }

        fout << ans << " ";
    }

    fin.close();
    fout.close();
}
