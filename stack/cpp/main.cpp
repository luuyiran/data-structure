#include <iostream>
#include <vector>
#include <string>

using namespace std; 

#include "arrayStack.hpp"
#include "linkStack.hpp"


template <typename T>
class Stack {
    T stk;
public:
    template <typename B>
    void push(B a) { stk.push(a);};
    void pop() { stk.pop();};
    auto top() { return stk.top();};
    bool empty(){ return stk.empty(); }
};

// LeetCode 20. Valid Parentheses
//  symbol   (   )    [   ]   {    }
//   ASCII  40  41   91  93  123  125
bool isOpen(char c)  { return ('{' == c || '[' == c || '(' == c); }
bool isClose(char c) { return ('}' == c || ']' == c || ')' == c); }
bool paired(char lc, char rc) { return (rc - lc == 1) || (rc - lc == 2); }
template <typename T>
bool isBalance(const string s, Stack<T> stk) {
    while (!stk.empty()) stk.pop();
    for (char c : s) {
        if (isOpen(c)) {
            stk.push(c);
        } else if (isClose(c)) {
            if (stk.empty()) return false;
            if (!paired(stk.top(), c)) return false;
            stk.pop();
        }
    }
    return stk.empty();
}


// LeetCode 150. Evaluate Reverse Polish Notation
bool isOperator(const string& op) {
    return op.size() == 1 && string("+-*/").find(op) != string::npos;
}
bool isNumber(string& token) {
    return !(token == "+" || token == "-" || token == "*" || token == "/");
}
template <typename T>
int evalRPN(vector<string>& tokens, Stack<T> stk) {
    while (!stk.empty()) stk.pop();
    for (auto str : tokens) {
        if (!isOperator(str)) {
            stk.push(stoi(str));
        } else {
            int b = stk.top();
            stk.pop();
            int a = stk.top();
            stk.pop();
            switch (str[0]) {
                case '+':
                    stk.push(a + b);
                    break;
                case '-':
                    stk.push(a - b);
                    break;
                case '*':
                    stk.push(a * b);
                    break;
                case '/':
                    stk.push(a / b);
                    break;
                default:
                    printf("input error!\n");
                    break;
            }
        }
    }
    return stk.top();
}



int main() {
    vector<string> s = {"()", "()[]{}", "(]", "([)]", "{[]}", "{[()({[]})]}", "{[(()(]})]}"};
    // ((10 * (6 / ((9 + 3) * -11))) + 17) + 5 = 22
    vector<string> token1 = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
    vector<string> token2 = {"4","13","5","/","+"};  // (4 + (13 / 5)) = 6

    Stack<ArrayStack<char>> s1;
    Stack<LinkStack<char>>  s2;
    for (string str : s) {
        cout << str << "\t" << isBalance(str, s1) << " ArrayStack\n";
        cout << str << "\t" << isBalance(str, s2) << " LinkStack\n";
    }


    Stack<ArrayStack<int>> s3;
    Stack<LinkStack<int>>  s4;
    for (string str : token1)
        cout << str << ",";
    cout << endl;
    cout << evalRPN(token1, s3) << endl;
    cout << evalRPN(token1, s4) << endl;

    for (string str : token2)
        cout << str << ",";
    cout << endl;
    cout << evalRPN(token2, s3) << endl;
    cout << evalRPN(token2, s4) << endl;

    return 0;
}
