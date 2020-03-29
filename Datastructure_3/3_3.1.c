#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#define ERROR -1000000
int Isdigit(int C){
    if(C >= 48&& C <= 57)
        return 1;
    else
        return 0;
}


float GetOp(char S[]){
    int i, c;
    while((S[0] = c = getchar()) == ' '|| c == '\t');
    if(S[0] == EOF)
        return 0;
    S[1]= '\0';
    if(!Isdigit(c) && c != '.' && c != '-')
        return c;
    i = 0;
    if(Isdigit(c))
        while(Isdigit(S[++i] = c = getchar()));
    if(c == '.')
        while(Isdigit(S[++i] = c = getchar()));
    if(c == '-'){
        if(Isdigit(S[++i] =  getchar()))
            while(Isdigit(S[++i] = c = getchar()));
        else  
            return c;
    }

    S[i] = '\0';
    return atof(S);

}
float Calculate(char S[]){
    float c , a, b;
    c = GetOp(S);
    if(c != '+' && c != '-' && c != '*' && c != '/' || c == ERROR)
        return  c;
    switch ((int)c){
        case '+':
            a = Calculate(S);
            b = Calculate(S);
            if(a == ERROR || b == ERROR)
                return ERROR;
            return a + b;
        case '-':
            a = Calculate(S);
            b = Calculate(S);
            if(a == ERROR || b == ERROR)
                return ERROR;
            return a - b;
        case '*':
            a = Calculate(S);
            b = Calculate(S);
            if(a == ERROR || c == ERROR)
                return ERROR;
            return a * b;
        case '/':
            a = Calculate(S);
            b = Calculate(S);
            if(b == 0)
                return ERROR;
            return a / b;
    }
}
int main(){
    char test[100];
    float flag;
    //printf("%.1f", );
    flag = Calculate(test);
    if(flag == ERROR)
        printf("ERROR");
    else 
        printf("%.1f", flag);
    //if(GetOp(Test))
    //printf("%f", GetOp(test));
}