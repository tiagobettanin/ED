#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct objeto{
    int CPF;
    char nome[30];
    int idade;
    //demais infos
    struct objeto *prox;
} OBJETO;

typedef struct {
    OBJETO *inicio;
    OBJETO *fim;
    int tamanho;
} FILA_DINAMICA;

void inicializaFila(FILA_DINAMICA *fila){
    fila->fim = NULL;
    fila->inicio = NULL;
    fila->tamanho = 0;
}

bool estahVazia(FILA_DINAMICA *fila){
    return fila->tamanho == 0;
}

int tamanhoFila(FILA_DINAMICA *fila){
    return fila->tamanho;
}

void insereFila(FILA_DINAMICA *fila, int cpf, char nome[], int idade){
    OBJETO *novo= (OBJETO*) malloc(sizeof(OBJETO));
    if(novo==NULL){
        printf("\n\nErro ao alocar memória para o novo elemento");
        return;
    }
    novo->CPF = cpf;
    novo->idade = idade;
    strcpy(novo->nome, nome);
    novo->prox = NULL;

    if(estahVazia(fila)==true){
        fila->inicio = novo;
    }
    else{
        fila->fim->prox=novo;
    }

    fila->tamanho++;
    fila->fim=novo;


}

void imprimePrimeiro(FILA_DINAMICA *fila){
    if(estahVazia(fila)==true){
        printf("\nFila Vazia!");
        return;
    }
    printf("\n\n==========================");
    printf("\nO primeiro elemento eh: CPF=%d Nome=%s ", fila->inicio->CPF, fila->inicio->nome);
    printf("\n==========================\n");
}

void excluiElemento(FILA_DINAMICA *fila){
   OBJETO *aux=fila->inicio;
   if(estahVazia(fila)==true){
        printf("\n\nFila vazia, impossivel excluir elemento");
        return;
   }

   fila->inicio=aux->prox;
   //caso precise, imprima as informações do elemento que vai sair: aux
   fila->tamanho--;
   free(aux);
   if(fila->inicio==NULL)  fila->fim=NULL; // Por que este passo eh necessário??? 
}

void destroiFila(FILA_DINAMICA *fila){
    while(estahVazia(fila)==false){
        excluiElemento(fila);
    }
    inicializaFila(fila);
}

int main(){
    FILA_DINAMICA fila;

    inicializaFila(&fila);
    insereFila(&fila, 12345, "Maria do Carmo", 50);
    insereFila(&fila, 54321, "Joao Jose", 38);

    excluiElemento(&fila);

    imprimePrimeiro(&fila);
    //fazer imprimeUltimo
    //Desafio: imprimir todos os elementos da fila na ordem que estao 
    destroiFila(&fila);
    return EXIT_SUCCESS;
}