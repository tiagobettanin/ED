#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct objeto{
    int CPF;
    char nome[30];
    int idade;
    struct objeto *prox;
} OBJETO;

typedef struct{
    int tamanho;
    OBJETO *inicio;
}   LISTA_DINAMICA;

void inicializaLista(LISTA_DINAMICA *lista){
    lista->tamanho = 0;
    lista->inicio = NULL;
}

int tamanho(LISTA_DINAMICA *lista){
    return lista->tamanho;
}

bool estaVazia(LISTA_DINAMICA *lista){
    return lista->tamanho == 0;
}

void insereFila(LISTA_DINAMICA *lista, int cpf, char nome[], int idade){
    OBJETO *novo = (OBJETO*) malloc(sizeof(OBJETO));
    if(novo == NULL){
        printf("\nNão foi possivel alocar memoria.\n");
        return;
    }
    novo->CPF=cpf;
    novo->idade=idade;
    strcpy(novo->nome, nome);
    novo->prox=NULL;

    if(estaVazia(lista)==true){
        lista->inicio = novo;
    }else{
        if(lista->inicio->idade > idade){
            novo->prox = lista->inicio;
            lista->inicio = novo;
        }else{
            OBJETO *aux = lista->inicio;
            while(aux->prox != NULL &&  aux->prox->idade < idade){
                aux = aux->prox;
            }
            
            //fazer o resto
        }
    }

    lista->tamanho++;

}

int main(void){
    LISTA_DINAMICA lista;

    inicializaLista(&lista);

    insereFila(&lista, 12345, "Maria do Carmo", 50);
    insereFila(&lista, 54321, "Joao Jose", 45);
    insereFila(&lista, 45123, "Luana da Silva", 35);
    insereFila(&lista, 32145, "Maria Maria", 25);
    insereFila(&lista, 98765, "Jose Jose", 5);
    

    return EXIT_SUCCESS;
}
