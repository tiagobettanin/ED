#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define M 5

typedef struct{
    int id;
}   OBJETO;

typedef struct{
    int inicio;
    int fim;
    int tamanho;
    OBJETO objeto[M];
}   FILA_ESTATICA;

void inicilisaFila(FILA_ESTATICA *fila){
    fila->tamanho = 0;
    fila->inicio = fila->fim = -1;
}

bool estaVazia(FILA_ESTATICA *fila){
    return fila->tamanho == 0;
}

bool estaCheia(FILA_ESTATICA *fila){
    return fila->tamanho == M;
}

void insereElemento(FILA_ESTATICA *fila, int id){
    if(estaCheia(fila)){
        printf("Não é possivel adicionar pois a pilha esta cheia.\n");
        return;
    }

    if(estaVazia(fila)){
        fila->inicio++;
    }

    fila->fim = (fila->fim + 1) % M;

    fila->objeto[fila->fim].id = id;

    fila->tamanho++;

}

OBJETO retornaInicil(FILA_ESTATICA *fila){
    return fila->objeto[fila->inicio];
}

OBJETO retornaFim(FILA_ESTATICA *fila){
    return fila->objeto[fila->fim];
}

void retiraElemento(FILA_ESTATICA *fila){
    if(estaVazia(fila)){
        printf("Não a elemento para retornar pois a fila esta vazia.\n");
        return;
    }

    fila->tamanho--;
    if(estaVazia(fila)){
        inicilisaFila(fila);
        return;
    }

    fila->inicio = (fila->inicio + 1) % M;

}

int main(void){
    FILA_ESTATICA fila;

    inicilisaFila(&fila);

    return 0;
}