#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

#define M 5

typedef struct objeto{
    int CPF;
    char nome[30];
    int idade;
    struct objeto *prox;
} OBJETO;

typedef struct{
    int tamanho;
    OBJETO *inicio;
    OBJETO *fim;
}   FILA_DINAMICA;

void inicializaFila(FILA_DINAMICA *f){
    f->tamanho = 0;
    f->inicio = NULL;
    f->fim = NULL;
}

bool estaVazia(FILA_DINAMICA *f){
    return f->tamanho == 0;
}

int tamanho(FILA_DINAMICA *f){
    return f->tamanho;
}

void insereFila(FILA_DINAMICA *f, int cpf, char nome[], int idade){
    OBJETO *novo = (OBJETO*) malloc(sizeof(OBJETO));
    if(novo == NULL){
        printf("\nErro ao alocar memoria\n");
        return;
    }

    novo->CPF = cpf;
    novo->idade = idade;
    strcpy(novo->nome, nome);
    novo->prox=NULL;

    if(estaVazia(f) == true){
        f->inicio = novo;
    }else{
        f->fim->prox=novo;
    }

    f->tamanho++;
    f->fim = novo;

}

void imprimePrimeiro(FILA_DINAMICA *f){
    if(estaVazia(f) == true){
        printf("\nA fila esta vazia\n");
        return;
    }
    printf("\n------------Primeiro-Elementos-----------\n");
    printf("Nome = %s | Idade = %d | CPF = %d", f->inicio->nome, f->inicio->idade, f->inicio->CPF);
    printf("\n-----------------------\n");
}

void imprimeUltimo(FILA_DINAMICA *f){
    if(estaVazia(f) == true){
        printf("\nA fila esta vazia\n");
        return;
    }
    printf("\n------------Ultimo-Elementos-----------\n");
    printf("Nome = %s | Idade = %d | CPF = %d", f->fim->nome, f->fim->idade, f->fim->CPF);
    printf("\n-----------------------\n");
}

void excluiElementos(FILA_DINAMICA *f){
    if(estaVazia(f) == true){
        printf("\nA fila esta vazia\n");
        return;
    }

    OBJETO *auxiliar;
    auxiliar = f->inicio;
    //f->inicio = auxiliar->prox;
    f->inicio = f->inicio->prox;
    free(auxiliar);
    f->tamanho--;
}

void destroiFila(FILA_DINAMICA *f){
    while(estaVazia(f) == false){
        excluiElementos(f);
    }
    inicializaFila(f);
}

int main(void){
    FILA_DINAMICA fila;

    inicializaFila(&fila);

    insereFila(&fila, 12345, "Maria do Carmo", 50);
    insereFila(&fila, 54321, "Joao Jose", 45);
    insereFila(&fila, 45123, "Luana da Silva", 35);
    insereFila(&fila, 32145, "Maria Maria", 25);
    insereFila(&fila, 98765, "Jose Jose", 5);

    imprimePrimeiro(&fila);
    imprimeUltimo(&fila);

    excluiElementos(&fila);

    destroiFila(&fila);

    return EXIT_SUCCESS;
}

//Desafio: imprimir todos os eslementos da fila na ordem que estão