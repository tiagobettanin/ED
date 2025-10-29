#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef struct objeto{
    int id;
    struct objeto *prox;
}   OBJETO;

typedef struct{
    int tamanho;
    OBJETO *inicio;
}  LISTA_DINAMICA;

void inicializaLista(LISTA_DINAMICA *lista){
    lista->tamanho = 0;
    lista->inicio = NULL;
}

bool estaVazia(LISTA_DINAMICA *lista){
    return lista->tamanho == 0;
}

void inserirElemento(LISTA_DINAMICA *lista, int id){
    OBJETO *novo = (OBJETO*) malloc(sizeof(OBJETO));
    if(novo == NULL){
        printf("Não foi possivel alocar memoria.\n");
        return;
    }

    novo->id = id;
    novo->prox = NULL;

    if( estaVazia(lista) == true){
        lista->inicio = novo;

    }else{  
        if( lista->inicio->id > novo->id){
            novo->prox = lista->inicio;
            lista->inicio = novo;
        }else{
            OBJETO  *aux = lista->inicio;

            while( aux->prox != NULL &&  aux->prox->id < novo->id){
                aux = aux->prox;
            }

            novo->prox = aux->prox;
            aux->prox = novo;

            //free(aux);
        }

    }

    lista->tamanho++;
}

void destroiLista(LISTA_DINAMICA *lista){
    if(estaVazia(lista) == true){
        printf("A lista esta vazia");
        return;
    }

    OBJETO *aux = NULL;
    while(lista->inicio != NULL){
        aux = lista->inicio;
        lista->inicio = aux->prox;
        free(aux);
    }

    inicializaLista(lista);

}

void deletaElemento(LISTA_DINAMICA *lista, int id){
    if(estaVazia(lista)){
        printf("A lista esta vazia.\n");
        return;
    }

    if( lista->inicio->id < id){
        printf("O elemento não esta na lista %d\n", id);
        return;
    }

    if(lista->inicio->id == id){
        OBJETO *aux = lista->inicio;
        lista->inicio = aux->prox;
        free(aux);
        printf("Elemetno %d removido.\n", id);
        return;
    }

    OBJETO *aux = lista->inicio;

    while( aux->prox != NULL && aux->prox->id < id){
        aux = aux->prox;
    }

    if( aux->prox->id != id){
        printf("O elemento não esta na lista %d\n", id);
        return;
    }else{
        OBJETO *fim = aux->prox;
        aux->prox = fim->prox;
        free(fim);
        lista->tamanho--;
        printf("Elemetno %d removido.\n", id);
    }




}

void imprimeElementos(LISTA_DINAMICA *lista){
    if(estaVazia(lista) == true){
        printf("\nA lista esta vazia\n");
        return ;
    }
    
    OBJETO *aux = lista->inicio; 
    printf("\n-----------------------\n");

    while (aux != NULL){
        
        printf(" %i ", aux->id);


        aux = aux->prox;
    }
    printf("\n-----------------------\n");

    free(aux);
}

int main(void){
    LISTA_DINAMICA lista;

    inicializaLista(&lista);

    //inserirElemento(&lista, 10);
    inserirElemento(&lista, 1);
    inserirElemento(&lista, 2);
    inserirElemento(&lista, 3);
    inserirElemento(&lista, 4);
    inserirElemento(&lista, 5);
    inserirElemento(&lista, 6);
    inserirElemento(&lista, 7);
    inserirElemento(&lista, 8);
    inserirElemento(&lista, 9);
    inserirElemento(&lista, 10);

    deletaElemento(&lista, 1);
    deletaElemento(&lista, 5);
    deletaElemento(&lista, 10);

    imprimeElementos(&lista);

    destroiLista(&lista);

    return 0;
}