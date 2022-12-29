#include <set>
#include <map>
#include <cmath>
#include <stack>
#include <vector>
#include <string>
#include <cctype>
#include <numeric>
#include <iostream>
#include <algorithm>
using namespace std;

set<char> AlphaSet(string expe) { //取得表达式中的原子变元，并整理到AlphaSet

    set<char> alphaSet;
    for(auto c : expe)
        if(isalpha(c) && !alphaSet.count(c))
            alphaSet.insert(c);
    return alphaSet;

}

string AssignExpe(string expe, set<char> alphaSet, int alphaCnt) { //为表达式分配真值

    auto setPtr = alphaSet.rbegin();
    for(int i = 0; setPtr != alphaSet.rend(); setPtr++, i++)
        for(auto &c : expe)
            if(c == *setPtr)
                c = '0' + ((alphaCnt >> i) & 1); //取得alphaCnt二进制的第i位，并赋给c
    return expe;

}

int Operate(int a, char b, int c) { //计算表达式的函数，一元运算符!不在其中
    switch(b) {
        case '|':
            return a | c;
        case '&':
            return a & c;
        case '^':
            return a ^ c;
        case '-':
            return !a | c;
        case '<':
            return a == c;
    }
    return -1;
}

int PriorityOperate(char a) { //给出运算符的优先级
    switch(a) {
        case '!':
            return 5;
        case '&':
            return 4;
        case '^':
            return 3;
        case '|':
            return 2;
        case '-':
            return 1;
        case '<':
            return 0;
    }
    return -1;
}

char PriorityCmp(char a, char b) { //比较栈顶运算符与待入栈运算符的优先级 详见压缩包内的表格
    if(a == '(' && b == ')' || a == '#' && b == '#' || a == '!' && b == '!')
        return '=';
    else if(a == '(' || b == '(' || a == '#' || PriorityOperate(a) < PriorityOperate(b))
        return '<';
    else
        return '>';
}

int Jump(char a) { //运算符的长度
    switch(a) {
        case '!':
            return 1;
        case '&':
            return 1;
        case '^':
            return 1;
        case '|':
            return 1;
        case '-':
            return 2;
        case '<':
            return 3;
        default:
            return 1;
    }
    return -1;
}

int main()
{

    cout << "请使用()表示括号，!表示非，&表示合取，^表示异或，|代表析取，->表示条件，<=>表示双条件，键入合法的表达式。\n";
    cout << "优先级：!, &, ^, |, ->, <=>\n";

    string expe; //命题公式
    string expeTmp; //命题公式的指派
    set<char> alphaSet; //命题公式的原子变元
    vector<int> boolArr; //命题公式的小项
    vector<int> nboolArr; //命题公式的大项

    cin >> expe;
    alphaSet = AlphaSet(expe); //命题公式的原子变元
    int numTmp = 0;
    int numL;
    int numR;
    char operTmp;

    for(auto c : alphaSet) //输出原子变元
        cout << c << ' ';
    cout << '\t' << expe << '\n';

    for(int alphaNow = 0; alphaNow < pow(2, alphaSet.size()); alphaNow++) {
        stack<int> opnd; //数字栈
        stack<char> optr; //符号栈
        expeTmp = AssignExpe(expe, alphaSet, alphaNow); //为命题公式进行指派
        optr.push('#');
        expeTmp = expeTmp + "#";

        for(int i = 0; !(expeTmp[i] == '#' && optr.top() == '#'); ){
            if(isdigit(expeTmp[i])){ //进数字栈
                opnd.push(expeTmp[i] - '0');
                i++;
            }
            else {
                operTmp = expeTmp[i];
                switch(PriorityCmp(optr.top(), operTmp)) { //比较栈顶元素与待入栈元素的优先级
                case '<': //栈顶元素优先级低
                    optr.push(operTmp);
                    i += Jump(operTmp);
                    break;
                case '>': //栈顶元素优先级高
                    if(optr.top() != '!') { //!运算以外的运算
                        numR = opnd.top();
                        opnd.pop();
                        numL = opnd.top();
                        opnd.pop();
                        operTmp = optr.top();
                        optr.pop();
                        opnd.push(Operate(numL, operTmp, numR));
                    }
                    else { //!运算
                        numL = opnd.top();
                        opnd.pop();
                        optr.pop();
                        opnd.push(!numL);
                    }
                    break;
                case '=': //栈顶元素与待定元素优先级相同
                    optr.pop();
                    i++;
                    break;
                }
            }
        }

        for(int i = alphaSet.size() - 1; i >= 0; i--) {
            cout << ((alphaNow >> i) & 1) << ' ';
        }
        cout << '\t' << opnd.top()<< '\n';
        if(opnd.top())
            boolArr.push_back(alphaNow);
        else
            nboolArr.push_back(alphaNow);
    }

    //输出
    if(!boolArr.size())
        cout << "永假公式\n";
    else if(!nboolArr.size())
        cout << "永真公式\n";
    else
        cout << "可满足公式\n";

    if(alphaSet.size()) { //当命题不是常量时，输出主析取范式和主合取范式
        cout << "主析取范式：";
        auto alphaSetPtr = alphaSet.begin();
        for(auto c : boolArr) { //遍历命题公式的小项
            alphaSetPtr = alphaSet.begin(); //当前输出的原子变元
            cout << '(';
            for(int i = alphaSet.size() - 1; i >= 0; i--) { //从最高位向后遍历
                if(!((c >> i) & 1)) //根据小项的二进制编码决定是否输出!，其中i为位数
                    cout << '!';
                cout << *(alphaSetPtr++); //输出当前的原子变元
                if(i) //如果不是最后一项，输出&
                    cout << '&';
            }
            cout << ')';
            if(c != *(boolArr.end() - 1)) //如果不是最后一项，输出|
                cout << "|";
        }
        if(!boolArr.size()) //如果命题永假，输出0
            cout << 0;
        cout << '\n';

        cout << "主合取范式：";
        for(auto c : nboolArr) { //遍历命题公式的大项
            alphaSetPtr = alphaSet.begin(); //当前输出的原子变元
            cout << '(';
            for(int i = alphaSet.size() - 1; i >= 0; i--) { //从最高位向后遍历
                if(((c >> i) & 1)) //根据小项的二进制编码决定是否输出!，其中i为位数
                    cout << '!';
                cout << *(alphaSetPtr++); //输出当前的原子变元
                if(i) //如果不是最后一项，输出|
                    cout << '|';
            }
            cout << ')';
            if(c != *(nboolArr.end() - 1)) //如果不是最后一项，输出&
                cout << "&";
        }
        if(!nboolArr.size()) //如果命题永真，输出0
            cout << 0;
        cout << '\n';
    }

    return 0;
    
}