#include<stdio.h>
#include<stdlib.h>

typedef struct{
    int x, y, z;
} PONTO;

int digitaPontos(){
    int num=0;
    printf("\n\nDigite a quantidade de pontos: ");
    scanf("%d", &num); //fazer o teste de consistencia num>0 e se num é inteiro
    return num;
}

void preencherPontos(PONTO *p, int qtde_pontos){

    for(int i=0; i<qtde_pontos; i++){
        p[i].x=i;
        p[i].y=i+1;
        p[i].z=i+2;
    }

}

int main(void){
    int qtde_pontos=0;

    PONTO *p=NULL;

    qtde_pontos = digitaPontos();
    
    p = (PONTO*) malloc(qtde_pontos * sizeof(int));

    preencherPontos( p, qtde_pontos);


    for(int i=0; i<qtde_pontos; i++){
        printf("\n\tPonto: %d [Coordenadas: x=%d |y=%d | z=%d]", i+1,p[i].x, p[i].y, p[i].z);
    }



    free(p);
    return 0;
}