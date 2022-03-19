#include <iostream>
#include <string>
#include <queue>
#include <stack>

using std::cin, std::cout, std::string;

bool is_op(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool is_op(string const &op) {
    return op == "+" || op == "-" || op == "*" || op == "/";
}

int priority(char ch) {
    return ch == '+' || ch == '-' ? 1 : 2;
}

int main() {
    std::queue<string> output;
    std::stack<string> stack;

    char peek;
    while((peek = (char) cin.peek()) != '\n') {
        if(std::isdigit(peek)) {
            int n; cin >> n;
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
                //string tmp = " "; tmp[0] = peek;
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

    while(!output.empty()) {
        cout << output.front() << " ";
        output.pop();
    }
}