#include<stdio.h>
char OPTion[4] = {'+', '-', '*', '/'};

int Calculate(int A, int B, int op){
    switch (op)
    {
    case 1:
        return A + B;
    case 2:
        return A - B;
    case 3:
        return A * B;
    case 4:
        if(B == 0)
            return 100000;
        if(A % B != 0)
            return 100000;
        return A / B;
    }
}

int CalculateWay(int A[], int OP[]){
    int op = 1, Num;
    while(op < 6){
        switch (op)
        {
        case 1:
            Num =  Calculate(Calculate(Calculate(A[0], A[1],OP[0]),A[2], OP[1]), A[3], OP[2]);
            break;
        case 2:
            Num =  Calculate(Calculate(A[0], A[1],OP[0]),Calculate(A[2], A[3], OP[2]), OP[1]);
            break;
        case 3:
            Num = Calculate(Calculate(A[0], Calculate(A[1], A[2], OP[1]), OP[0]), A[3], OP[2]);
            break;
        case 4:
            Num = Calculate(A[0], Calculate(Calculate(A[1], A[2], OP[1]), A[3], OP[2]), OP[0]);
            break;
        case 5:
            Num =  Calculate(A[0], Calculate(A[1], Calculate(A[2], A[3], OP[2]), OP[1]), OP[0]);
            break;
        }
        if(Num == 24){
            switch (op)
            {
            case 1:
                printf("((%d%c%d)%c%d)%c%d", A[0], OPTion[OP[0]-1], A[1], OPTion[OP[1]-1], A[2], OPTion[OP[2]-1], A[3]);
                return 1;
            case 2:
                printf("(%d%c%d)%c(%d%c%d)", A[0], OPTion[OP[0]-1], A[1], OPTion[OP[1]-1], A[2], OPTion[OP[2]-1], A[3]);
                return 1;
            case 3:
                printf("(%d%c(%d%c%d))%c%d", A[0], OPTion[OP[0]-1], A[1], OPTion[OP[1]-1], A[2], OPTion[OP[2]-1], A[3]);
                return 1;
            case 4:
                printf("%d%c((%d%c%d)%c%d)", A[0], OPTion[OP[0]-1], A[1], OPTion[OP[1]-1], A[2], OPTion[OP[2]-1], A[3]);
                return 1;
            case 5:
                printf("%d%c(%d%c(%d%c%d))", A[0], OPTion[OP[0]-1], A[1], OPTion[OP[1]-1], A[2], OPTion[OP[2]-1], A[3]);
                return 1;
            default:
                break;
            }
        }
        op++;
    }
    return 0;
}

int Output(int A[], int Input[]){
    int i,j,k,l, flag = 0;
    for(i = 0 ; i < 4; i++){
        Input[0] = i + 1;
        for(j = 0 ; j < 4; j++){
            Input[1] = j + 1;
            for(k = 0 ; k < 4; k++){
                Input[2] = k + 1;
                flag = CalculateWay(A, Input);
                if(flag == 1)
                    return flag;
            }
        }
    }
    return 0;
} 
int main(){
    int A[4], i, j, k, l,Input[4], flag;
    int OP[4];
    for(i = 0; i < 4; i++){
        scanf("%d" ,&A[i]);
    }
    for(i = 0 ; i < 4; i++){
        Input[0] = A[i];
        for(j = 0 ; j < 4; j++){
            if(j == i)
                continue;
            Input[1] = A[j];
            for(k = 0 ; k < 4; k++){
                if(k == i || k == j)
                    continue;
                Input[2] = A[k];
                for(l = 0 ; l < 4; l++){
                    if(l==i||l==k||l==j)
                        continue; 
                    Input[3] = A[l];
                    flag = Output(Input, OP);
                    if(flag == 1)
                        return 0;
                }
            }
        }
    }
    if(flag == 0)
        printf("%d", -1);
}