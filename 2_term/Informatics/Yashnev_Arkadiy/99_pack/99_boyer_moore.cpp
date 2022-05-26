#include <iostream>
#include <string>
 
using namespace std;
 
int main() {
 
    string line, substr;
    getline(cin, line);
    getline(cin, substr);
    size_t sub_size = substr.size();
 
    size_t chars [128];
    for (size_t i = 0; i < 128; ++i) chars[i] = sub_size;
    for (size_t i = sub_size-2; i != size_t(-1); --i)
    {
        if (chars[substr[i]] == sub_size)
            chars[substr[i]] = sub_size - 1 - i;
    }
    /*for (size_t i = 0; i < 256; ++i)
        if (chars[i] != sub_size)
            cout << chars[i] << char(i) << '\n';*/
    for (size_t i = sub_size-1; i < line.size(); ++i)
    {
        size_t count = 0;
        while (count != sub_size && line[i-count] == substr[sub_size-1 - count])
            count++;
        if (count == sub_size)
        {
            cout << i + 1 - count << ' ';
            i += chars[line[i]]-1;
        }
        else
        {
            if (!count)
                i += chars[line[i-count]] - 1;
            else
                i += chars[substr[sub_size-1]]-1;
        }
    }
    return 0;
}