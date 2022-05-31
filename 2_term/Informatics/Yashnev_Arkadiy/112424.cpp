#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>

using std::cin, std::cout, std::string;

double to_num(string str) {
    if(std::isalpha(str.back())) {
        str.erase(str.size() - 1, 1);
    }

    if(str == "+") {
        return 1;
    } else if(str == "-") {
        return -1;
    } else {
        return stod(str);
    }
}

inline bool is_op(char ch) {
    return ch == '+' || ch == '-';
}

typedef std::pair<double, double> pdd;

pdd quad_equation(double a, double b, double c);

int main() {
    string input; cin >> input;
    //cout << to_num("-a");
    double coefficients[3]{};
    std::vector<size_t> indecies;

    if(input[0] != '+' && input[0] != '-') { input = '+' + input; }

    for(size_t i = 0; i != input.size(); ++i) {
        if(is_op(input[i])) {
            indecies.push_back(i);
        }
    }

    if(indecies.size() == 1) {
        coefficients[0] = to_num(input);
    }

    for(size_t i = 1; i != indecies.size() + 1; ++i) {
        string tmp = input.substr(indecies[i - 1], indecies[i] - indecies[i - 1]);
        size_t index;
        if(tmp.back() == 'a') {
            index = 0;
        } else if(tmp.back() == 'b') {
            index = 1;
        } else {
            index = 2;
        }

        coefficients[index] = to_num(tmp);
    }

    auto res = quad_equation(coefficients[0], coefficients[1], coefficients[2]);
    cout << std::fixed << std::setprecision(3) << res.first << " " << res.second;
}

pdd quad_equation(double a, double b, double c) {
    if(a == 0) {
        if (b == 0) throw std::domain_error("Do you even have an equation?");
        else return std::make_pair(-c / b, -c / b);
    }

    double D = b * b - 4 * a * c;

    if(D < 0)       throw std::domain_error("Discriminant is less than 0!");
    else if(D == 0) return std::make_pair(-b/(2*a), -b/(2*a));
    else {
        double x1 = (-b + sqrt(D)) / (2 * a), x2 = (-b - sqrt(D)) / (2 * a);
        return std::make_pair(std::min(x1, x2), std::max(x1, x2));
    }
}
