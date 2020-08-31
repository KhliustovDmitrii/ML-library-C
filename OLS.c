#include <stdio.h>
#include <stdlib.h>
#define eps 0.00001
double * ols_exact(double * param_x, double * param_y,  int num_param, int num_observ);//The exact solution of optimization problem, given by (X^t X)^(-1) X^t Y
double * matrix_multiply(double * x, double * y, int n, int m, int k);
int matrix_inverse(double * x, int n);
double * matrix_transponse(double * x, int n, int m);
void swap_rows(double * x, int n, int i, int j);
void elementary_map(double*x, int n, int i, int j, double y);
int main(){
double * y, * x;
double * result;
FILE * o, * r;
int i;
o = fopen("observ.txt", "r");
r = fopen("response.txt", "r");
printf("files opened \n");
y = (double *)malloc(8*sizeof(double));
x = (double *)malloc(16*sizeof(double));
i = 0;
while(fscanf(o, "%f", &x[i])==1){
    i++;
}
i = 0;
while(fscanf(r, "%f", &y[i])==1){
    i++;
}
result = ols_exact(x, y, 2, 8);
printf("%f, %f", result[0], result[1]);
fclose(o);
fclose(r);
free(y);
free(x);
free(result);
return 0;
}

double * ols_exact(double * param_x, double * param_y, int num_param, int num_observ){
    double * xxt, * xt;
    printf("ols started \n");
    xt = matrix_transponse(param_x, num_param, num_observ);
    printf("transponse done \n");
    xxt = matrix_multiply(xt, param_x, num_observ, num_param, num_observ);
    printf("multiplied xxt \n");
    matrix_inverse(xxt, num_param);
    printf("inverted \n");
    return matrix_multiply(xxt, matrix_multiply(xt, param_y, num_observ, num_param, num_observ), num_param, num_param, num_param);
}
double * matrix_multiply(double * x, double * y, int n, int m, int k){
double * result;
int i, j, s;
result = (double *)malloc(n*k*sizeof(double));
for(i = 0; i < n; i++){
    for(j = 0; j < k; j++){
        result[i*n+j] = 0;
        for(s = 0; s < m; s++){
            result[i*n+j]+=x[i*n+j]*y[s*m+j];
        }
    }
}
}

int matrix_inverse(double * x, int n){
double * result;
double s;
int i, j;
result = (double *)malloc(n*n*sizeof(double));
for(i = 0; i < n; i++){
    for(j = 0; j < n; j ++){
            if(i==j){
                result[i*n+j] = 1;
            } else{
                result[i*n+j] = 0;
            }
    }
}
for(i = 0; i < n; i++){//Forward step of Gauss
        printf("forward step %d \n", i);
    if(x[i*n+i]<(-1)*eps||x[i*n+i]>eps){
        printf("accounted if on fs %d", i);
        printf("em started %d \n", i);
        elementary_map(x, n, i, i, (1/x[i*n+i] - 1));
        printf("em done %d \n", i);
        for(j=i+1;j<n;j++){
            s = x[j*n+i];
            elementary_map(x, n, j, i, s);
            elementary_map(result, n, j, i, s);
        }
    } else{
        printf("accounted else on fs %d", i);
        j = i;
        while(x[j*n+i]<eps&&x[j*n+i]>(-1)*eps&&j<n){
            j++;
            printf("%d", j);
        if(j==n){
            printf("Matrix is not invertible");
            return -1;
        }
        }
        swap_rows(x, n, i, j);
        swap_rows(result, n, i, j);
    }
    printf("forward step %d done \n", i);
}
for(i = n-1; i > -1; i--){//Backward step of Gauss
    printf("backward step %d \n", n-1-i);
    for(j = i; j > -1; j--){
        s = (-1)*x[j*n+i];
        elementary_map(x, n, j, i, s);
        elementary_map(result, n, j, i, s);
    }
}
for(i = 0; i < n*n; i++){
    x[i] = result[i];
}
free(result);
return 1;
}

double * matrix_transponse(double * x, int n, int m){
double * result;
int i, j;
result = (double *)malloc(m*n*sizeof(double));
for(i=0;i<m;i++){
    for(j=0;j<n;j++){
        result[i*n+j] = x[j*m+i];
    }
}
return result;
}
void swap_rows(double * x, int n, int i, int j){//Changes two rows of the matrix
int k;
for(k = 0; k < n; k++){
    x[i*n+k]+=x[j*n+k];
    x[j*n+k] = x[i*n+k]-x[j*n+k];
    x[i*n+k]-=x[j*n+k];
}
}
void elementary_map(double*x, int n, int i, int j, double y){//Adds to row i row j times y
int k;
for(k = 0; k < n; k++){
    x[i*n+k]+=x[j*n+k]*y;
}
}
