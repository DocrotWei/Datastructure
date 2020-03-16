#include <stdio.h>
#define MAX 10001
int H[MAX];
int n;
void AjudstUp(int a[],int k) {
    a[0]=a[k];
    int i=k/2;
    while(i>0&&a[i]>a[0]) {
        a[k]=a[i];
        k=i;
        i=k/2;
    }
    a[k]=a[0];
}
void AdjustDown(int a[],int k) {
    a[0]=a[k];
    int i;
    for(i=k*2; i<=n; i*=2) {
        if(i<n&&a[i]>a[i+1])
            i++;
        if(a[0]<=a[i])break;
        else {
            a[k]=a[i];
            k=i;
        }

    }
    a[k]=a[0];
}
int get(int a[]) {
    int tmp;
    tmp=a[1];
    a[1]=a[n];
    a[n]=tmp;
    int x=a[n];
    n--;
    AdjustDown(a,1);
    return x;
}
int main() {
    scanf("%d",&n);
    int i;
    int sum=0;
    for(i=1; i<=n; i++) {
        scanf("%d",&H[i]);
        AjudstUp(H,i);
    }
    while(n!=1) {
        int x=get(H);
        int y=get(H);
        n++;
        H[n]=x+y;
        sum+=H[n];
        AjudstUp(H,n);
    }
    printf("%d",sum);

}