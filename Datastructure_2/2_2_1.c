#include<stdio.h>
#define MAXSIZE 100

int main(){
    int Maxitem = 0, item;
    int a3 = 0, A2 = 0, A3 = 0;
    int N;
    scanf("%d", &N);
    for(int i = 0; i < N; i++){
        scanf("%d", &item);
        if(item % 3 == 0){
            if(item > Maxitem)
                Maxitem = item;
        }
        else if(item % 3 == 1)
            A2++;
        else if(item % 3 == 2){
            a3++;
            A3 += item;
        }

    }
    
    if(Maxitem == 0)
        printf("NONE ");
    else 
        printf("%d ", Maxitem);
    if(A2 == 0)
        printf("NONE ");
    else
        printf("%d ", A2);
    if(a3 == 0)
        printf("NONE");
    else
        printf("%.1f", (float)A3 / a3);
}