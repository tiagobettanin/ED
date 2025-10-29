#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define M 5

typedef struct{
    int CPF;
    char nome[30];
    int idade;
} OBJETO;

typedef struct{
    int tamanho;
    int inicio;
    int fim;
    OBJETO elementos[M];
}   FILA_ESTATICA;

void inicializaFila(FILA_ESTATICA *fila){
    fila->tamanho=0;
    fila->fim=fila->inicio=-1;
}

bool estaVazio(FILA_ESTATICA *fila){
    return fila->tamanho==0;
}

bool estaCheia(FILA_ESTATICA *fila){
    return fila->tamanho==M;
}

void insereElementoFila(FILA_ESTATICA *fila, int cpf, char nome[], int idade){
    if(estaCheia(fila)==true){
        printf("\nFila cheia! Nao foi possivel add o novo elemento");
        return;
    }

    if(estaVazio(fila)==true){
        fila->inicio=(fila->inicio+1)%M;
    }

    fila->fim = (fila->fim+1) % M;

    fila->tamanho++;

    fila->elementos[fila->fim].CPF = cpf;
    fila->elementos[fila->fim].idade = idade;
    strcpy( fila->elementos[fila->inicio].nome, nome);    
    
}

void excluiElementoFila(FILA_ESTATICA *fila){
    if(estaVazio(fila)==true){
        printf("\nFila está vazia, nao consigo excluir elemento");
        return;
    }

    fila->tamanho--;
    if(estaVazio(fila)==true){
        inicializaFila(fila);
        return;
    }
    fila->inicio= (fila->inicio+1)%M;



}

int tamanhoFila(FILA_ESTATICA *fila){
    return fila->tamanho;
}

void imprimePrimeiroFila(FILA_ESTATICA *fila){
    if(estaVazio(fila)==true){
        printf("\nFIla vazia");
        return;
    }

    printf("\n-----------------------\n");
    printf("Nome = %s | Idade = %d | CPF = %d", fila->elementos[fila->inicio].nome, fila->elementos[fila->inicio].idade, fila->elementos[fila->inicio].CPF);
    printf("\n-----------------------\n");

}


int main(void){
    FILA_ESTATICA fila;

    inicializaFila(&fila);

    insereElementoFila(&fila, 12345, "Maria do Carmo", 50);
    insereElementoFila(&fila, 54321, "Joao Jose", 45);
    insereElementoFila(&fila, 45123, "Luana da Silva", 35);
    insereElementoFila(&fila, 32145, "Maria Maria", 25);
    insereElementoFila(&fila, 98765, "Jose Jose", 5);

    excluiElementoFila(&fila);

    //insereElementoFila(&fila, 12345, "Maria do Carmo", 50);

    imprimePrimeiroFila(&fila);

    return EXIT_SUCCESS;
}