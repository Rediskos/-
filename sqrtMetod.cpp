#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

double tabA[100][100];
double tabU[100][100];
double tabUTr[100][100];
int n;

double equalPileAndStr(int I, int J) {
    double res = tabA[I][I];
    
    for(int k = 0; k < I; k++) {
        res -= tabU[k][I];
    }
    
    return sqrt(res);
}

double notEqualPileAndStr(int I, int J) {
    double res = tabA[I][J];
    
    for(int k = 0; k < I; k++) {
        res -= tabU[k][I]*tabU[k][J];
    }
    
    return res / tabU[I][I];
}

double solve(int I, int J) {
    return I == J ? equalPileAndStr(I, J) : notEqualPileAndStr(I, J);
}

void findeU(){
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            tabU[i][j] =  solve(i, j);
        }
    }
}

void printfTab(double Tab[][100]) {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            printf("%3.3lf ", Tab[i][j]);
        }
        printf("\n");
    }
}

double* forward(double Tab[][100]) {
    double *ans = new double(n);
    
    for(int z = 0; z < n; z++) {
        double tmp = tabA[z][n];
        for(int j = 0; j < z; j++) {
            tmp -= tabUTr[z][j] * ans[j];
        }
        ans[z] = tmp / tabUTr[z][z];
    }
    
    return ans;
}

void tabTr() {
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            tabUTr[j][i] = tabU[i][j];
        }
    }
}

double* backward(double *y) {
    double *ans = new double(n);
    
    for(int z = n - 2; z >= 0; z--) {
        double tmp = y[z];
        for(int j = n - 2; j > z; j--) {
            tmp -= tabU[z][j] * ans[j];
        }
        ans[z] = tmp / tabU[z][z];
    }
    
    return ans;
}

int main(int argc, char** argv) {
    
    ifstream cin ("input.txt");
    
    cin >> n;
    
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n + 1; j++) {
            cin >> tabA[i][j];
        }
    }
    
    findeU();
    
    printf("Матрица U\n");
    printfTab(tabU);
    
    tabTr();
    printf("\n");
    
    printf("Матрица U транспортировая\n");
    printfTab(tabUTr);
    printf("\n");
    
    
    double* y = forward(tabUTr);
    
    double* x = backward(y);
    
    for(int i = 0; i < n; i++) {
        printf("x%d = %.3lf ",i + 1, x[i]);
    }
    
    printf("\n");
    
    for(int i = 0; i < n; i++) {
        double tmp = 0;
        
        for(int j = 0; j < n; j++) {
            tmp += x[j]*tabA[i][j];
        }
        printf("%.3lf\t%.3lf\n", tmp, tabA[i][n]);
    }
    
    return 0;
}

