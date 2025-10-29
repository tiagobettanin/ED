#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

int fatorial(int n){
    int fat;
    if(n <= 1){
        return 1;
    }else{
        fat =  n * fatorial(n-1);
        return fat;
    }
    
    
    

    

}

int main(void){
    int n;
    printf("Informe o valor de n: ");
    scanf("%d", &n);

    int resultado = fatorial(n);

    printf("O fatorail de n eh: %d\n", resultado);

    
    return 0;
}
