#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

typedef struct objeto{
    int id;
    struct objeto *prox;
}   OBJETO;

typedef struct{
    OBJETO *inicio;    
    OBJETO *fim;    
    int tamanho;
}   FILA_DINAMICA;

void inicializaFila(FILA_DINAMICA *fila){
    int tamanho = 0;
    fila->fim = fila->inicio = NULL;
}

bool estaVazia(FILA_DINAMICA *fila){
    return fila->tamanho == 0;
}

void inserirElemento(FILA_DINAMICA *fila, int id){
    OBJETO *aux = (OBJETO*) malloc(sizeof(OBJETO));
    if(aux == NULL){
        printf("Não foi possivel alocar memoria para o novo item.\n");
        return;
    }

    aux->id = id;
    aux->prox = NULL;

    if(estaVazia(fila)){
        fila->inicio = aux;
    }else{
        fila->fim->prox = aux;
    }

    fila->fim = aux;
    fila->tamanho++;

}

void destroiFila(FILA_DINAMICA *fila){
    while(!estaVazia(fila)){
        deletarElemento(fila);
    }
    inicializaFila(fila);
}

void inserirElemento1(FILA_DINAMICA *fila, int id){
    OBJETO *aux = (OBJETO*) malloc(sizeof(OBJETO));
    if(aux == NULL){
        printf("Não foi possivel alocar memoria.");
        return;
    }

    aux->id = id;
    aux->prox = NULL;


    if(estaVazia(fila)){
        fila->inicio = aux;
    }else{
        fila->fim->prox = aux;
    }

    fila->fim = aux;
    fila->tamanho++;
}

void deletarElemtneo(FILA_DINAMICA *fila){
    if(estaVazia(fila)){
        printf("A fila esta Vazia.\n");
        return;
    }

    OBJETO *aux = fila->inicio;
    if(aux == NULL){
        printf("Não foi possivel alocar memroia.\n");
        return;
    }

    fila->inicio = aux->prox;
    free(aux);
    fila->tamanho--;

    if(fila->inicio == NULL) fila->fim = NULL;
}

void deletarElemento(FILA_DINAMICA * fila){
    if(estaVazia(fila)){
        printf("A fila esta vazia.\n");
        return;
    }

    OBJETO *aux = fila->inicio;
    if(aux == NULL){
        printf("Não foi possivel alocar memoria para remover.\n");
        return;
    }

    fila->inicio = fila->inicio->prox;
    fila->tamanho--;
    free(aux);
    
    if(fila->inicio == NULL) fila->fim = NULL;

}

int main(void){


    return 0;
}