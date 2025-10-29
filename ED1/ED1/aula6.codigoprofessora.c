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
    int tamanho;
} LISTA_DINAMICA;

void inicializaLista(LISTA_DINAMICA *lista){
    lista->inicio = NULL;
    lista->tamanho = 0;
}

bool estahVazia(LISTA_DINAMICA *lista){
    return lista->tamanho == 0;
}

int tamanhoLista(LISTA_DINAMICA *lista){
    return lista->tamanho;
}

//obs: a lista estah ordenada por idade (ordem crescente)
//OBS2: como posso ter mais de um objeto com a mesma idade, pensar em como tratar isso!!!
void insereElementoLista(LISTA_DINAMICA* lista, int cpf, char nome[], int idade){
    OBJETO* novo=(OBJETO*) malloc(sizeof(OBJETO));
    if(novo==NULL){
        printf("\nNao foi possivel alocar memoria para o novo elemento");
        return ;
    } 
    novo->CPF=cpf;
    novo->idade=idade;
    strcpy(novo->nome, nome);
    novo->prox=NULL;

    if(estahVazia(lista)==true){
       lista->inicio=novo; 
    }
    else{
        if(lista->inicio->idade > idade){
            novo->prox=lista->inicio;
            lista->inicio=novo;
        }
        else{
            OBJETO *aux = lista->inicio;
            //null antesa para não dar segimentisonfoll pq ele já para lá, a ordem é importante
            while(aux->prox != NULL &&  aux->prox->idade < idade){
                aux = aux->prox;
            }
            novo->prox=aux->prox;
            aux->prox = novo;

            free(aux);
        }
    }

    lista->tamanho++;
}

void imprimeElementos(LISTA_DINAMICA *lista){
    if(estahVazia(lista) == true){
        printf("\nA lista esta vazia\n");
        return ;
    }
    
    OBJETO *aux = lista->inicio; 

    while (aux != NULL){
        printf("\n-----------------------\n");
        printf("Nome = %s | Idade = %d | CPF = %d", aux->nome, aux->idade, aux->CPF);
        printf("\n-----------------------\n");

        aux = aux->prox;
    }

    free(aux);
}

void destroiLista(LISTA_DINAMICA *lista){
    if(estahVazia(lista) == true){
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

void removeElemento(LISTA_DINAMICA *lista, int idade){
    if(estahVazia(lista)== true){
        printf("A lista esta vazia");
        return;
    }
    if(idade < lista->inicio->idade){
        printf("Este elemento não esta na lista");
        return;
    }
    if(idade == lista->inicio->idade){
        OBJETO *aux = lista->inicio;
        lista->inicio = aux->prox;
        free(aux);
        lista->tamanho--;
        printf("Elemento removido.");
        return;
    }
    OBJETO *aux = lista->inicio;
    while(aux->prox != NULL && aux->prox->idade < idade){
        aux = aux->prox;
    }

    if(aux->prox->idade != idade){
        printf("A idade não esta na lista");
        return;
    }else{
        OBJETO *tchau = aux->prox;
        aux->prox = tchau->prox;
        free(tchau);
        lista->tamanho--;
    }



}

int main(void){
    LISTA_DINAMICA lista;
    inicializaLista(&lista);

    insereElementoLista(&lista, 12345, "Maria do Carmo", 50);
    insereElementoLista(&lista, 54321, "Joao Jose", 45);
    insereElementoLista(&lista, 45123, "Luana da Silva", 35);
    insereElementoLista(&lista, 32145, "Maria Maria", 25);
    insereElementoLista(&lista, 98765, "Jose Jose", 5);
    insereElementoLista(&lista, 98885, "Jose Maria", 70);

    removeElemento(&lista, 50);


    imprimeElementos(&lista);

    destroiLista(&lista);

    imprimeElementos(&lista);


    

    return EXIT_SUCCESS;
}

//fazer pesquisar(BOOLEANO EIMPRIMRR   ), maximo, minima, peoximo eanterior