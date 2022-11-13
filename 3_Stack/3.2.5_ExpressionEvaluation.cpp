#include <stack>
#include <string>
#include <iostream>
using namespace std;

char PriorityCmp(char a, char b) {
    if(a == '(' && b == ')' || a == '#' && b == '#')
        return '=';
    else if(((a == '+' || a == '-') && (b == '*' || b == '/')) || a == '(' || b == '(' || a == '#')
        return '<';
    else
        return '>';
}

double Operate(double a, char b, double c) {
    switch(b) {
        case '+':
            return a + c;
        case '*':
            return a * c;
        case '/':
            return a / c;
        case '-':
            return a - c;
    }
    return -1;
}

int main() {

    string expe;
    stack<double> opnd;
    stack<char> optr;
    cin >> expe;

    double numTmp = 0;
    double numL;
    double numR;
    char operTmp;
    expe = expe + "#";
    optr.push('#');

    for(int i = 0; !(expe[i] == '#' && optr.top() == '#'); ) {
        if(isdigit(expe[i])) {
            numTmp *= 10;
            numTmp += expe[i] - '0';
            i++;
        }
        else {
            if(numTmp) {
                opnd.push(numTmp);
                numTmp = 0;
            }
            operTmp = expe[i];
            switch(PriorityCmp(optr.top(), operTmp)) {
                case '<':
                    optr.push(operTmp);
                    i++;
                    break;
                case '>':
                    numR = opnd.top();
                    opnd.pop();
                    numL = opnd.top();
                    opnd.pop();
                    operTmp = optr.top();
                    optr.pop();
                    opnd.push(Operate(numL, operTmp, numR));
                    break;
                case '=':
                    optr.pop();
                    i++;
                    break;
            }
        }
    }

    cout << opnd.top();
    return 0;

}