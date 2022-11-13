#include <iostream>
#include <stdlib.h>
#include <cmath>
using namespace std;

struct LinkNode {
    int exp;
    double coef;
    LinkNode *next;
};
typedef LinkNode *LinkList;

LinkList AddPolynomial(LinkList a, LinkList b) {

    LinkList c = (LinkList) malloc (sizeof(LinkNode));
    LinkList pc = c->next, lc = c;
    LinkList pa = a->next, pb = b->next;

    while(pa || pb) {
        LinkList tmp = (LinkList) malloc (sizeof(LinkNode));
        tmp -> next = NULL;
        if(pa && pb) {
            if(pa->exp < pb->exp) {
                tmp->exp = pa->exp;
                tmp->coef = pa->coef;
                lc->next = tmp;
                lc = tmp;
                pa = pa->next;
            }
            else if(pa->exp > pb->exp) {
                tmp->exp = pb->exp;
                tmp->coef = pb->coef;
                lc->next = tmp;
                lc = tmp;
                pb = pb->next;
            }
            else {
                if(fabs(pa->coef + pb->coef) < 1e-8) {
                    pa = pa->next;
                    pb = pb->next;
                }
                else {
                    tmp->exp = pa->exp;
                    tmp->coef = pa->coef + pb->coef;
                    lc->next = tmp;
                    lc = tmp;
                    pb = pb->next;
                    pa = pa->next;
                }
            }
        }
        else if(pa && !pb) {
            tmp->exp = pa->exp;
            tmp->coef = pa->coef;
            lc->next = tmp;
            lc = tmp;
            pa = pa->next;
        }
        else if(!pa && pb){
            tmp->exp = pb->exp;
            tmp->coef = pb->coef;
            lc->next = tmp;
            lc = tmp;
            pb = pb->next;
        }
    }
    return c;

}

LinkList InitPolynomial() {

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
		cout << "Enter the " << i;
        if(i % 10 == 1)
            cout << "st";
        else if(i % 10 == 2)
            cout << "nd";
        else if(i % 10 == 3)
            cout << "rd";
        else
            cout << "th";
        cout << " coefficient and exponent of the term.\n";
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

void PrtPolynomial(LinkList a) {
    LinkList pa = a->next;
    bool firstFlag = 0;
    while(pa) {
        if(pa->exp == 0)
            printf("%lf", pa->coef);
        else if(pa->exp) {
            if(firstFlag && pa->coef > 0)
                printf("+");
            printf("%lfx^%d", pa->coef, pa->exp);
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