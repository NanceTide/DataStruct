#include <iostream>
#include <stdlib.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASIBLE -1
#define OVERFLOW -2
#define MAX_STR_SIZE 255
typedef int Status;

struct SString {
    char ch[MAX_STR_SIZE + 1];
    int length;
};

Status DestroyString(SString &s) {
    s.ch[0] = '\0';
    s.length = 0;
    return OK;
}

Status StrAssign(SString &s, char *ch) {
    DestroyString(s);
    if(!ch)
        return ERROR;
    s.ch[0] = '\0';
    int len, i;
    for(len = 0; ch[len] != '\0'; len++);
    for(i = 0; i < len && i < MAX_STR_SIZE; i++)
        s.ch[i] = ch[i];
    s.ch[i] = '\0';
    s.length = i;
    return OK;
}

Status Prt(SString s) {
    if(!s.ch)
        return ERROR;
    cout << s.ch << '\n' << s.length << '\n';
    return OK;
}

SString SubString(SString txt, int index, int chLen) {
    char ch[MAX_STR_SIZE + 1];
    int chCnt;
    for(chCnt = 0; chCnt < chLen && index + chCnt < txt.length; chCnt++)
        ch[chCnt] = txt.ch[chCnt + index];
    ch[chCnt] = '\0';
    SString ans;
    StrAssign(ans, ch);
    return ans;
}

Status ConCat(SString &s0, SString s1, SString s2) {
    int index, tmp;
    for(index = 0; index < s1.length; index++)
        s0.ch[index] = s1.ch[index];
    for(tmp = 0; tmp < s2.length && index + tmp < MAX_STR_SIZE; tmp++)
        s0.ch[index + tmp] = s2.ch[tmp];
    s0.ch[index + tmp] = '\0';
    s0.length = index + tmp;
    if(index + tmp == MAX_STR_SIZE)
        return false;
    else
        return true;
}

int IndexBF(SString s0, SString s1) {
    int i = 0, j = 0;
    while(i < s0.length && j < s1.length) {
        if(s0.ch[i] == s1.ch[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }
    if(j >= s1.length)
        return i - s1.length;
    else
        return -1;
}
void getNext(SString txt, int *&next) {
    next = (int*) malloc (sizeof(int) * txt.length);
    next[0] = -1;
    if(txt.length == 1)
        return;
    next[1] = 0;
    if(txt.length == 2)
        return;

    for(int index = 2; index < txt.length; index++) {
        char newChar = txt.ch[index - 1];
        if(newChar == txt.ch[next[index - 1]])
            next[index] = next[index - 1] + 1;
        else {
            int cur = next[index- 1];
            while(newChar != next[cur]) {
                cur = next[cur];
                if(cur == -1)
                    break;
            }
            next[index] = cur + 1;
        }
    }
}

void getNextval(SString txt, int *next, int *&nextval) {
    nextval = (int*) malloc (sizeof(int) * txt.length);
    nextval[0] = -1;
    if(txt.length == 1)
        return;
    for(int index = 1; index < txt.length; index++) {
        nextval[index] = txt.ch[next[index]] == txt.ch[index] ? next[next[index]] : next[index];
    }
}

int IndexKMP(SString txt, SString pat) {
    int *next, *nextval;
    getNext(pat, next);
    getNextval(pat, next, nextval);
    int i = 0, j = 0;

    while(i < txt.length && j < pat.length) {
        if(txt.ch[i] == pat.ch[j]) {
            i++;
            j++;
        } else {
            j = nextval[j];
            if(j == -1) {
                j = 0;
                i++;
            }
        }
    }

    free(next);
    free(nextval);
    if(j >= pat.length)
        return i - pat.length;
    else
        return -1;
}

Status StrCopy(SString &to, SString from) {
    to.length = from.length;
    to.ch[0] = from.ch[0];
    for(int i = 1; from.ch[i - 1] != '\0'; i++)
        to.ch[i] = from.ch[i];
    return OK;
}

int StrCountSub(SString txt, SString pat) {
    int cnt = 0, index;
    SString tmp;
    StrCopy(tmp, txt);
    while((index = IndexKMP(tmp, pat)) != -1) {
        cnt++;
        tmp = SubString(tmp, pat.length + index, tmp.length - index - pat.length);
    }
    return cnt;
}

int Replace(SString &txt, SString from, SString to) {
    int cnt = 0, index;
    SString left, right, ans;
    StrCopy(right, txt);
    DestroyString(txt);
    while((index = IndexKMP(right, from)) != -1) {
        left = SubString(right, 0, index);
        right = SubString(right, index + from.length, right.length - index - from.length);
        ConCat(txt, txt, left);
        ConCat(txt, txt, to);
        cnt++;
    }
    ConCat(txt, txt, right);
    return cnt;
}

int main() {

    SString str0, str1, str2;
    char s0[] = "helloworldhelloworldhello";
    char s1[] = "hello";
    char s2[] = "hello!";
    StrAssign(str0, s0);
    StrAssign(str1, s1);
    StrAssign(str2, s2);
    cout << Replace(str0, str1, str2) << '\n';
    Prt(str0);

    return 0;

}