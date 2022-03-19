#include <iostream>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <iomanip>

using std::cin, std::cout, std::string;

bool is_op(char ch) { return ch == '+' || ch == '-' || ch == '*' || ch == '/'; }
bool is_op(string const &op) { return op == "+" || op == "-" || op == "*" || op == "/"; }
int priority(char ch) { return ch == '+' || ch == '-' ? 1 : 2; }

long long div_(long long a, long long b) {
    return (long long) std::floor((double) a / (double) b);
}

double div_(double a, double b) {
    return a / b;
}

template<typename T>
T calculate(std::queue<string> input);
template<typename T>
void infix_input(std::queue<string> &output);
void postfix_output(std::queue<string> output);
void postfix_input(std::queue<string> &input);

int main() {
    std::queue<string> output;

    postfix_input(output);
    cout << calculate<long long>(output);
}

void postfix_input(std::queue<string> &input) {
    char peek;
    while((peek = (char) cin.peek()) != '\n') {
        if(peek == ' ') {
            cin.get();
            continue;
        } else {
            string in; cin >> in;
            input.push(in);
        }
    }
}

void postfix_output(std::queue<string> output) {
    while(!output.empty()) {
        cout << output.front() << " ";
        output.pop();
    }
    cout << "\n";
}

template <typename T>
T calculate(std::queue<string> input) {
    std::stack<T> stack;
    while(!input.empty()) {
        if(std::isdigit(input.front()[0])) {
            stack.push(std::stod(input.front()));
            input.pop();
        } else if(is_op(input.front())) {
            if(stack.size() < 2) {
                cout << "ERROR\n";
                std::exit(0);
            }
            T a2 = stack.top(); stack.pop();
            T a1 = stack.top(); stack.pop();
            switch(input.front()[0]) {
                case '+': stack.push(a1 + a2); break;
                case '-': stack.push(a1 - a2); break;
                case '*': stack.push(a1 * a2); break;
                case '/': stack.push(div_(a1, a2)); break;
            }
            input.pop();
        } else {
            if(stack.empty()) {
                cout << "ERROR\n";
                std::exit(0);
            }
            T a = stack.top(); stack.pop();
            switch(input.front()[1]) {
                case 'i': stack.push(std::sin(a)); break;
                case 'o': stack.push(std::cos(a)); break;
                case 'b': stack.push(std::abs(a)); break;
                case 'q': stack.push(std::sqrt(a)); break;
            }
            input.pop();
        }
    }

    if(stack.size() > 1) {
        cout << "ERROR\n";
        std::exit(0);
    }

    return stack.top();
}

template<typename T>
void infix_input(std::queue<string> &output) {
    std::stack<string> stack;

    char peek;
    while((peek = (char) cin.peek()) != '\n') {
        if(peek == ' ') {
            cin.get();
            continue;
        } else if(std::isdigit(peek)) {
            T n; cin >> n;
            output.push(std::to_string(n));
        } else if(std::isalpha(peek)) {
            cin.get();
            switch ((char) cin.peek()) {
                case 'i': stack.push("sin"); cin.get(); cin.get(); break;
                case 'o': stack.push("cos"); cin.get(); cin.get(); break;
                case 'b': stack.push("abs"); cin.get(); cin.get(); break;
                case 'q': stack.push("sqrt"); cin.get(); cin.get(); break;
            }
        } else if(is_op(peek)) {
            cin.get();
            while(!stack.empty() && is_op(stack.top()) && (priority(stack.top()[0]) >= priority(peek))) {
                output.push(stack.top());
                stack.pop();
            }
            string tmp = " "; tmp[0] = peek;
            stack.push(tmp);
        } else if(peek == '(') {
            cin.get();
            stack.push("(");
        } else if(peek == ')') {
            cin.get();;
            while(stack.top() != "(") {
                output.push(stack.top());
                stack.pop();
            }
            stack.pop();
            if(!stack.empty() && stack.top().size() > 1) {
                output.push(stack.top());
                stack.pop();
            }
        }
    }

    while(!stack.empty() && is_op(stack.top())) {
        output.push(stack.top());
        stack.pop();
    }
}
