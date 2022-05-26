#include "iostream"
#include "string"
 
using std::cin, std::cout;
typedef std::string str;
 
void KMP(const str& string, const str& sample);


int main() {
    str string, sample;
    cin >> string >> sample;
 
    KMP(string, sample);
 
    return 0;
}


void prefix(int *pi, str const &string) {
    for(size_t i = 1; i != string.size(); ++i) {
        int j = pi[i - 1];
        while(j > 0 && string[i] != string[j])
            j = pi[j - 1];
        if(string[i] == string[j]) ++j;
        pi[i] = j;
    }
}
 
void KMP(const str& string, const str& sample) {
    str line = sample + '&' + string;
    auto l_size = line.size();
    auto s_size = sample.size();
    int *pi = new int[l_size]{};
    prefix(pi, line);
    for (size_t i = s_size+1; i < l_size; ++i) {
        if (pi[i] == s_size) {
            cout << i-2*s_size << ' ';
        }
    }
    delete[] pi;
}