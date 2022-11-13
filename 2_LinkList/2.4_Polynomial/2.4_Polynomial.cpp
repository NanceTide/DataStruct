#include <iostream> // 头文件
#include <stdlib.h>
#include <cmath>
using namespace std;

struct LinkNode { // 链表定义
    int exp;
    double coef;
    LinkNode *next;
};
typedef LinkNode *LinkList;

LinkList AddPolynomial(LinkList a, LinkList b) { // 多项式相加函数

    LinkList c = (LinkList) malloc (sizeof(LinkNode)); // 和多项式
    LinkList pc = c->next, lc = c; // pc 指向和多项式首节点，lc 指向和多项式头节点
    LinkList pa = a->next, pb = b->next; // pa pb 分别指向两参数多项式的首节点

    while(pa || pb) { // 当 pa pb 都判空时退出循环
        LinkList tmp = (LinkList) malloc (sizeof(LinkNode));
        tmp -> next = NULL; // tmp 是和多项式的项
        if(pa && pb) { // pa pb 都不空
            if(pa->exp < pb->exp) { // pa 的指数小于 pb 的指数，则将 pa 作为待添加的项
                tmp->exp = pa->exp;
                tmp->coef = pa->coef;
                lc->next = tmp;
                lc = tmp;
                pa = pa->next;
            }
            else if(pa->exp > pb->exp) { // pa 的指数大于 pb 的指数，则将 pb 作为待添加的项
                tmp->exp = pb->exp;
                tmp->coef = pb->coef;
                lc->next = tmp;
                lc = tmp;
                pb = pb->next;
            }
            else { // pa pb 指数相同
                if(fabs(pa->coef + pb->coef) < 1e-8) { // pa、pb值相加系数为 0，该项不添加
                    if(pa->exp == 0) {
                        tmp->exp = 0;
                        tmp->coef = 0;
                        lc->next = tmp;
                        lc = tmp;
                    }
                    pa = pa->next;
                    pb = pb->next;
                }
                else { // 相加系数不为 0，添加该项
                    tmp->exp = pa->exp;
                    tmp->coef = pa->coef + pb->coef;
                    lc->next = tmp;
                    lc = tmp;
                    pb = pb->next;
                    pa = pa->next;
                }
            }
        }
        else if(pa && !pb) { // pb 判空，pa 不空
            tmp->exp = pa->exp;
            tmp->coef = pa->coef;
            lc->next = tmp;
            lc = tmp;
            pa = pa->next;
        }
        else if(!pa && pb){ // pa 判空，pb 不空
            tmp->exp = pb->exp;
            tmp->coef = pb->coef;
            lc->next = tmp;
            lc = tmp;
            pb = pb->next;
        }
    }
    return c;

}

LinkList InitPolynomial() { // 创建一个多项式

	int expTmp = 0;
	double coefTmp = 0;
	LinkList a = (LinkList) malloc (sizeof(LinkNode));
	a->next = NULL;
	LinkList la = a;
    la->next = NULL;

    int num;
    cout << "Enter the number of terms of the polynomial.\n";
    cin >> num;
	for (int i = 1; i <= num; i++)
	{
		cout << "Enter the coefficient and exponent of the " << i;
        if(i % 10 == 1)
            cout << "st";
        else if(i % 10 == 2)
            cout << "nd";
        else if(i % 10 == 3)
            cout << "rd";
        else
            cout << "th";
        cout << " term.\n";
		cin >> coefTmp >> expTmp;
		LinkList tmp = (LinkList) malloc(sizeof(LinkNode));
		tmp->exp = expTmp;
		tmp->coef = coefTmp;
		la->next = tmp;
		la = tmp;
	}
	la->next = NULL;
	return a; 

}

void PrtPolynomial(LinkList a) { // 打印一个多项式
    LinkList pa = a->next;
    bool firstFlag = 0;
    while(pa) {
        if(pa->exp == 0)
            printf("%.1lf", pa->coef);
        else if(pa->exp) {
            if(firstFlag && pa->coef > 0)
                printf("+");
            printf("%.1lfx^%d", pa->coef, pa->exp);
        }
        firstFlag = 1;
        pa = pa->next;
    }
    cout << '\n';
}

int main() {

    LinkList a = InitPolynomial();
    LinkList b = InitPolynomial();
    LinkList c = AddPolynomial(a, b);

    PrtPolynomial(a);
    PrtPolynomial(b);
    PrtPolynomial(c);

    return 0;

}