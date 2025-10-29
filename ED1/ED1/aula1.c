#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

void converta(int milhas, int *km, int *metros){
    *km = milhas * 1.609;
    *metros = (*km * 1000)/3600;


}

int main(void){
    int m, k;

    converta(100, &k, &m);

    printf("%i, %i\n", k, m);

    return 0;
}
