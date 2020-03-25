#include<stdio.h>

const int maxn = 1e6 + 5;

int num[maxn];

void adjust(int s, int m) {
    int temp = num[s];
    for(int j = s * 2; j <= m; j *= 2) {
        if(j < m && num[j] > num[j + 1]) ++j;
        if(temp <= num[j]) break;
        num[s] = num[j];
        s = j;
    }
    num[s] = temp;
}

void heapSort(int n) {
    int temp;
    for(int i = n / 2; i > 0; --i)
        adjust(i, n);
    for(int i = n; i > 1; --i) {
        temp = num[1];
        num[1] = num[i];
        num[i] = temp;
        adjust(1, i - 1);
    }
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);
    for(int i = 1; i <= n; ++i) 
        scanf("%d", &num[i]);
    heapSort(n);
    for(int i = 1; i <= m && i <= n; ++i) {
        printf("%d%c", num[i], (i == m || i == n) ? '\n' : ' ');
    }
    return 0;
}