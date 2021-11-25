// String Calculator
#include <iostream>
#include <string>
#include <stack>
#include <sstream>
#include <typeinfo>

using namespace std;

// Strategy ���� ���
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
    int p; // ������ �켱����
    string o; // ������
};

stack<double> num; // ���� ����
stack<oper> op; // ������ ����

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
    // ��� �� ���ÿ� �ٽ� ����
    num.push(result);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string input;
    while (1) {


        getline(cin, input);

        // 0�� �Է¹����� ����
        if (input == "0") {
            break;
        }
        // ��������
        input.erase(remove(input.begin(), input.end(), ' '), input.end());

        string str = "";
        string temp = "";
        for (int i = 0; i < input.length(); i++) {

            // �����ڶ�� �������� temp�� ����� ���ڿ��� str�� append
            if (input[i] == '*' || input[i] == '+' || input[i] == '-' || input[i] == '/' || input[i] == '(' || input[i] == ')') {
                str.append(temp);
                str.append(" ");
                temp = "";
                string s(1, input[i]); // charŸ���� string���� ��ȯ
                str.append(s);
                str.append(" ");
            }
            // �����ڰ� �ƴ϶�� temp�� append
            else {
                string s(1, input[i]);
                temp.append(s);
            }

        }
        // ���� ������ �ǿ����ڸ� str�� append
        str.append(temp);

        stringstream ss(str);
        int count = 0;

        // ������ �켱������ ���� ���ÿ� push
        // 0 : ( )
        // 1 : + -
        // 2 : * /
        string tok;

        // check�� 1�̸� �������� �Է��̹Ƿ� ���� �����ڸ� ���
        // check�� 0�̸� �Է°��� ���������� �����Ƿ� ���α׷� ����
        int check = 1;

        // ������ȣ�� ���� �������� �Ǻ��ϱ� ����
        int closedFirst = 0;
        // ������ ��ȣ �ٷ� �ڿ� 0�� ������ Ȯ���ϱ� ����
        int division = 0;
        // �����ڰ� �ΰ� �������� �������� Ȯ��
        int operatorCount = 0;
        // ���ڰ� ������ ���� ������ ���� ������ ��� Ȯ��
        int operatorFirst = 1;
        // �����ڰ� ���� ���������� Ȯ��
        int operatorLast = 0;

        while (ss >> tok) {

            count = 0;

            // ( �� ������ ������ ���ÿ� push
            if (tok == "(") {
                op.push({ 0, tok });
                closedFirst = 1;
            }
            else if (tok == ")" && closedFirst == 0) {
                cout << "�ݴ� ��ȣ�� ���� �ԷµǾ����ϴ�." << endl;
                check = 0;
                break;
            } // ) �� ������ ( �� ���� �� ���� ���
            else if (tok == ")") {
                closedFirst = 0;
                while (op.top().o != "(")
                    calc();
                op.pop();
            }
            else if (tok == "*" || tok == "/" || tok == "+" || tok == "-") {
                // �ǿ����ں��� �����ڰ� ���� ���� ���
                if (operatorFirst == 1) {
                    // -��� �����̹Ƿ� ����
                    if (tok == "-") {
                        cout << "������ �Է��� �� �����ϴ�." << endl;
                    }
                    else
                        cout << "�ǿ����ڸ� �Է��� �ּ���." << endl;
                    check = 0;
                    break;
                }
                operatorCount++;
                operatorLast = 1;
                if (operatorCount == 2) {
                    cout << "�����ڰ� 2�� �������� �ԷµǾ����ϴ�." << endl;
                    check = 0;
                    break;
                }
                int prior; // ������ �켱����
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

                // ������ �켱 ���� ������ top���� �� ������ ���
                while (!op.empty() && prior <= op.top().p)
                    calc();
                // ���ÿ� ������ push
                op.push({ prior, tok });
            }
            // �����ڰ� �ƴ� ���
            else {

                operatorFirst = 0;
                operatorCount = 0;
                operatorLast = 0;

                char x = 'x';
                char b = 'b';

                if (atoi(tok.c_str()) < 0) {
                    cout << "������ �Է��� �� �����ϴ�." << endl;
                    check = 0;
                    break;
                }
                if (division) {
                    if (tok == "0") {
                        cout << "0���� ���� �� �����ϴ�." << endl;
                        check = 0;
                        break;
                    }

                }

                // �Է°��� ������ ��
                if (atoi(tok.c_str())) {

                    num.push(stoi(tok));
                }
                // �Է°��� 16������ ��
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
                            cout << "16���� �Է��� �߸��Ǿ����ϴ�." << endl;
                            check = 0;
                            break;
                        }
                    }

                    if (division && a == 0) {
                        cout << "0���� ���� �� �����ϴ�." << endl;
                        check = 0;
                        break;
                    }
                    num.push(a);


                }
                // �Է°��� 2������ ��
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
                            cout << "2���� �Է��� �߸��Ǿ����ϴ�." << endl;
                            check = 0;
                            break;
                        }
                    }

                    if (division && a == 0) {
                        cout << "0���� ���� �� �����ϴ�." << endl;
                        check = 0;
                        break;
                    }
                    num.push(a);
                }
                // ���ڳ� �ٸ� ���� �Է¹޾��� ��
                else {
                    if (tok == "0") {
                        num.push(0);
                    }
                    else {
                        cout << "�߸��� �Է��Դϴ�." << endl;
                        check = 0;
                        break;
                    }

                }
            }
        }

        // ��ȣ�� ������ �ʾ��� ��
        if (closedFirst == 1) {
            if (check) {
                cout << "��ȣ�� �ùٸ��� �ʽ��ϴ�." << endl;
                check = 0;
            }

        }

        // check�� 1�� ���� ( ������ ���� ���� ) ��� ����
        if (check) {

            // �����ڰ� �������� ��
            if (operatorLast) {
                cout << "�ǿ����ڰ� �����ϴ�." << endl;
                check = 0;
            }
            if (check) {
                // ���� ������ ���
                while (!op.empty())
                    calc();

                cout << num.top() << endl;
            }


        }
    }

    return 0;
}