#include <iostream>
#include <string>
#include <stack>
#include <sstream>

using namespace std;

class calculator {
public:
    int rank;
    string oper;
    virtual int calc(int a, int b) = 0;
    virtual int getRank() = 0;
};
class lp : public calculator {
public:
    int rank = 3;
    int calc(int a, int b) {
        return 2;
    }
    lp(string _oper) {
        oper = _oper;
    }
    int getRank() {
        return rank;
    }
    void setRank(int newrank) {
        rank = newrank;
    }
};
class rp : public calculator {
public:
    int rank = 2;
    int calc(int a, int b) {
        return 0;
    }
    rp(string _oper) {
        oper = _oper;
    }
    int getRank() {
        return 2;
    }
};
class mul : public calculator {
public:
    int rank;
    int calc(int a, int b) {
        return a * b;
    }
    mul(string _oper) {
        oper = _oper;
        rank = 1;
    }
    int getRank() {
        return 1;
    }
};
class divi : public calculator {
public:
    int rank;
    int calc(int a, int b) {
        return a / b;
    }
    divi(string _oper) {
        oper = _oper;
        rank = 1;
    }
    int getRank() {
        return 1;
    }

};
class pluss : public calculator {
public:
    int rank;
    int calc(int a, int b) {
        return a + b;
    }
    pluss(string _oper) {
        oper = _oper;
        rank = 0;
    }
    int getRank() {
        return 0;
    }
};
class minuss : public calculator {
public:
    int rank;
    int calc(int a, int b) {
        return a - b;
    }
    minuss(string _oper) {
        oper = _oper;
        rank = 0;
    }
    int getRank() {
        return 0;
    }
};

stack<int> num; // 숫자 스택
stack<calculator*> op; // 연산자 스택

int bin(string s) {

    int ret = stoi(s, nullptr, 2); //예제> stoi(1110, nullptr, 2) : 14
    return ret;
}

int dec(string s) {
    int ret = stoi(s);
    return ret;
}

int hex(string s) {
    int ret = stoi(s, nullptr, 16); //예제> stoi(0x14, nullptr, 16) : 20
    return ret;
}

int toNum(string s) {
    if (s.length() > 2) {
        if (s[1] == 'b') {
            return stoi(s.substr(2, s.length()), nullptr, 2);
        }
        else if (s[1] == 'x') {
            return stoi(s, nullptr, 16);
        }
        else {
            return stoi(s, nullptr, 10);
        }
    }
    else {
        return stoi(s, nullptr, 10);
    }
}

int main()
{
    string line;
    getline(cin, line);
    int i = 0;
    bool l = false;
    bool r = false;
    bool start = false;
    string str;
    try {
        if (line[i] == '*' || line[i] == '/' || line[i] == '+' || line[i] == '-') throw "잘못된 입력";
    }
    catch (const char* c) {
        cout << c << endl;
        exit(0);
    }
    string number = "";
    for (int i = 0; i < line.length(); i++) {
        //숫자일때
        if (line[i] != '(' && line[i] != ')' && line[i] != '*' && line[i] != '/' && line[i] != '+' && line[i] != '-') {
            number += line[i];
        }
        //연산자일때
        else if (line[i] == '*' || line[i] == '/' || line[i] == '+' || line[i] == '-') {
            try {
                if ((i != line.length() - 1) && (line[i + 1] == '*' || line[i + 1] == '/' || line[i + 1] == '+' || line[i + 1] == '-')) throw "잘못된 입력";
            }
            catch (const char* c) {
                cout << c << endl;
                exit(0);
            }


            if (number != "") {
                num.push(toNum(number));
                number = "";
            }

            calculator* c;
            if (line[i] == '*') {
                c = new mul("*");
            }
            else if (line[i] == '/') {
                c = new divi("/");
            }
            else if (line[i] == '+') {
                c = new pluss("+");
            }
            else {
                c = new minuss("-");
            }


            //연산자스택이 비었거나 top()의 우선순위보다 높을 때
            if (op.empty() || op.top()->getRank() < c->getRank()) {
                op.push(c);
            }
            else {//top()의 우선순위보다 낮을 때
                while (!op.empty() && op.top()->getRank() >= c->getRank()) {
                    int n1 = num.top(); num.pop();
                    int n2 = num.top(); num.pop();
                    int result = op.top()->calc(n2, n1); op.pop();
                    num.push(result);
                }
                op.push(c);
            }
        }
        else {//괄호
            if (number != "") {
                num.push(toNum(number));
                number = "";
            }
            if (line[i] == '(') {
                lp* lpp = new lp("(");
                op.push(lpp);
                lpp->setRank(-1);
            }
            else {
                while (!op.empty() && op.top()->oper != "(") {
                    
                    int n1 = num.top(); num.pop();
                    int n2 = num.top(); num.pop();
                    int result = op.top()->calc(n2, n1); op.pop();
                    num.push(result);
                }
                if (op.top()->oper == "(") {
                    op.pop();
                }
            }
        }
    }
    if (number != "") {
        num.push(toNum(number));
        number = "";
    }
    while (!op.empty()) {
        int n1 = num.top(); num.pop();
        int n2 = num.top(); num.pop();
        int result = op.top()->calc(n2, n1); op.pop();
        num.push(result);
    }
    std::cout << num.top() << std::endl;


}
