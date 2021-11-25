// String Calculator
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <typeinfo>

using namespace std;

// Strategy 패턴 사용
class Strategy {
public:
    virtual double doOperation(double num1, double num2) = 0;
};


class OperationAdd : public Strategy {
public:
    double doOperation(double num1, double num2) override {
        return num1 + num2;
    }
};

class OperationSubstract : public Strategy {
public:
    double doOperation(double num1, double num2) override {
        return num1 - num2;
    }
};

class OperationMultiply : public Strategy {
public:
    double doOperation(double num1, double num2) override {
        return num1 * num2;
    }
};

class OperationDivide : public Strategy {
public:
    double doOperation(double num1, double num2) override {
        return num1 / num2;
    }
};

class Context {
private:
    Strategy* strategy;
public:
    Context(Strategy* strategy) {
        this->strategy = strategy;
    }
    double executeStrategy(double num1, double num2) {
        return strategy->doOperation(num1, num2);
    }
};

struct oper {
    int p; // 연산자 우선순위
    string o; // 연산자
};

stack<double> num; // 숫자 스택
stack<oper> op; // 연산자 스택

void calc() {
    Context* context;
    double a, b;
    double result;

    b = num.top();
    num.pop();
    a = num.top();
    num.pop();
    string oper = op.top().o;
    op.pop();

    if (oper == "*") {
        context = new Context(new OperationMultiply);
        result = context->executeStrategy(a, b);
    }
    else if (oper == "/") {
        context = new Context(new OperationDivide);
        result = context->executeStrategy(a, b);
    }
    else if (oper == "+") {
        context = new Context(new OperationAdd);
        result = context->executeStrategy(a, b);
    }
    else if (oper == "-") {
        context = new Context(new OperationSubstract);
        result = context->executeStrategy(a, b);
    }
    // 결과 값 스택에 다시 저장
    num.push(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string input;
    while (1) {


        getline(cin, input);

        // 0을 입력받으면 종료
        if (input == "0") {
            break;
        }
        // 공백제거
        input.erase(remove(input.begin(), input.end(), ' '), input.end());

        string str = "";
        string temp = "";
        for (int i = 0; i < input.length(); i++) {

            // 연산자라면 이전까지 temp에 저장된 문자열을 str에 append
            if (input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '(' || input[i] == ')') {
                str.append(temp);
                str.append(" ");
                temp = "";
                string s(1, input[i]); // char타입을 string으로 변환
                str.append(s);
                str.append(" ");
            }
            // 연산자가 아니라면 temp에 append
            else {
                string s(1, input[i]);
                temp.append(s);
            }

        }
        // 가장 마지막 피연산자를 str에 append
        str.append(temp);

        stringstream ss(str);
        int count = 0;

        // 연산자 우선순위에 따라 스택에 push
        // 0 : ( )
        // 1 : + -
        // 2 : * /
        string tok;

        // check가 1이면 정상적인 입력이므로 남은 연산자를 계산
        // check가 0이면 입력값이 정상적이지 않으므로 프로그램 종료
        int check = 1;

        // 닫힘괄호가 먼저 나오는지 판별하기 위함
        int closedFirst = 0;
        // 나누기 기호 바로 뒤에 0이 오는지 확인하기 위함
        int division = 0;
        // 연산자가 두개 연속으로 나오는지 확인
        int operatorCount = 0;
        // 숫자가 나오기 전에 연산자 먼저 나오는 경우 확인
        int operatorFirst = 1;
        // 연산자가 식의 마지막인지 확인
        int operatorLast = 0;

        while (ss >> tok) {

            count = 0;

            // ( 는 무조건 연산자 스택에 push
            if (tok == "(") {
                op.push({ 0, tok });
                closedFirst = 1;
            }
            else if (tok == ")" && closedFirst == 0) {
                cout << "닫는 괄호가 먼저 입력되었습니다." << endl;
                check = 0;
                break;
            } // ) 가 나오면 ( 가 나올 때 까지 계산
            else if (tok == ")") {
                closedFirst = 0;
                while (op.top().o != "(")
                    calc();
                op.pop();
            }
            else if (tok == "*" || tok == "/" || tok == "+" || tok == "-") {
                // 피연산자보다 연산자가 먼저 나올 경우
                if (operatorFirst == 1) {
                    // -라면 음수이므로 에러
                    if (tok == "-") {
                        cout << "음수는 입력할 수 없습니다." << endl;
                    }
                    else
                        cout << "피연산자를 입력해 주세요." << endl;
                    check = 0;
                    break;
                }
                operatorCount++;
                operatorLast = 1;
                if (operatorCount == 2) {
                    cout << "연산자가 2개 연속으로 입력되었습니다." << endl;
                    check = 0;
                    break;
                }
                int prior; // 연산자 우선순위
                if (tok == "*") {
                    division = 0;
                    prior = 2;
                }
                else if (tok == "/") {
                    division = 1;
                    prior = 2;
                }
                else if (tok == "+") {
                    division = 0;
                    prior = 1;
                }
                else if (tok == "-") {
                    division = 0;
                    prior = 1;
                }

                // 연산자 우선 순위 낮은게 top으로 올 때까지 계산
                while (!op.empty() && prior <= op.top().p)
                    calc();
                // 스택에 연산자 push
                op.push({ prior, tok });
            }
            // 연산자가 아닌 경우
            else {

                operatorFirst = 0;
                operatorCount = 0;
                operatorLast = 0;

                char x = 'x';
                char b = 'b';

                if (atoi(tok.c_str()) < 0) {
                    cout << "음수는 입력할 수 없습니다." << endl;
                    check = 0;
                    break;
                }
                if (division) {
                    if (tok == "0") {
                        cout << "0으로 나눌 수 없습니다." << endl;
                        check = 0;
                        break;
                    }

                }

                // 입력값이 숫자일 때
                if (atoi(tok.c_str())) {

                    num.push(stoi(tok));
                }
                // 입력값이 16진수일 때
                else if (tok[1] == x) {
                    int a = (int)strtol(tok.c_str(), NULL, 16);
                    string key = tok.substr(2);

                    if (a == 0) {

                        int isZero = 0;
                        for (int i = 2; i < tok.length(); i++) {
                            if (tok[i] != '0') {
                                isZero = 1;
                                break;
                            }
                        }
                        if (isZero) {
                            cout << "16진수 입력이 잘못되었습니다." << endl;
                            check = 0;
                            break;
                        }
                    }

                    if (division && a == 0) {
                        cout << "0으로 나눌 수 없습니다." << endl;
                        check = 0;
                        break;
                    }
                    num.push(a);


                }
                // 입력값이 2진수일 때
                else if (tok[1] == b) {
                    string key = tok.substr(2);
                    int a = (int)strtol(key.c_str(), NULL, 2);

                    if (a == 0) {

                        int isZero = 0;

                        for (int i = 2; i < tok.length(); i++) {
                            if (tok[i] != '0') {
                                isZero = 1;
                                break;
                            }
                        }

                        if (isZero) {
                            cout << "2진수 입력이 잘못되었습니다." << endl;
                            check = 0;
                            break;
                        }
                    }

                    if (division && a == 0) {
                        cout << "0으로 나눌 수 없습니다." << endl;
                        check = 0;
                        break;
                    }
                    num.push(a);
                }
                // 문자나 다른 값을 입력받았을 때
                else {
                    if (tok == "0") {
                        num.push(0);
                    }
                    else {
                        cout << "잘못된 입력입니다." << endl;
                        check = 0;
                        break;
                    }

                }
            }
        }

        // 괄호가 닫히지 않았을 때
        if (closedFirst == 1) {
            if (check) {
                cout << "괄호가 올바르지 않습니다." << endl;
                check = 0;
            }

        }

        // check가 1일 때만 ( 오류가 없을 때만 ) 계산 진행
        if (check) {

            // 연산자가 마지막일 때
            if (operatorLast) {
                cout << "피연산자가 없습니다." << endl;
                check = 0;
            }
            if (check) {
                // 남은 연산자 계산
                while (!op.empty())
                    calc();

                cout << num.top() << endl;
            }


        }
    }

    return 0;
}