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
    OBJETO *topo;
    int qtde_elementos;
} PILHA_DINAMICA;

void inicializaPilha(PILHA_DINAMICA *pilha){
    pilha->qtde_elementos = 0;
    pilha->topo=NULL;
}

bool estaVazia(PILHA_DINAMICA *pilha){
    return pilha->qtde_elementos == 0;
}

int tamanhoPilha(PILHA_DINAMICA *pilha){
    return pilha->qtde_elementos;
}

void empilha(PILHA_DINAMICA * pilha, int cpf, char nome[], int idade){
    OBJETO *aux = (OBJETO*) malloc (sizeof(OBJETO));
    if(aux==NULL){
        printf("Não foi possivel alocar memoria para um novo elemento");
        return;
    }

    aux->CPF = cpf;
    aux->idade = idade;
    strcpy(aux->nome, nome);

    aux->prox=pilha->topo;
    pilha->topo=aux;

    pilha->qtde_elementos++;

    free(aux);
}

OBJETO* topoPilha(PILHA_DINAMICA *pilha){
    return pilha->topo;
}

void desempilha(PILHA_DINAMICA *pilha){
    OBJETO *aux = pilha->topo;
    if(aux==NULL){
        printf("pilha vazia");
        return;
    }

    pilha->topo=aux->prox;
    free(aux);
    pilha->qtde_elementos--;
}

void imprimeTopo(PILHA_DINAMICA *pilha){
    if(estaVazia(pilha)==true){
        printf("A pilha esta vazia");
        return;
    }

    printf("\n-----------------------\n");
    printf("Nome = %s | Idade = %d | CPF = %d", pilha->topo->nome, pilha->topo->idade, pilha->topo->CPF);
    printf("\n-----------------------\n");
}

void destruirPilha(PILHA_DINAMICA *pilha){
    while(estaVazia(pilha)==false){
        desempilha(pilha);
    }

}

int main(void){
    PILHA_DINAMICA p;

    inicializaPilha(&p);

    empilha(&p, 12345, "Maria do Carmo", 50);
    empilha(&p, 54321, "Joao Jose", 45);
    empilha(&p, 45123, "Luana da Silva", 35);

    desempilha(&p);
    
    imprimeTopo(&p);



    return EXIT_SUCCESS;
}