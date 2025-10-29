#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#define M 10 

typedef struct{
    int CPF;
    char nome[30];
    int idade;
    //outras infos
} OBJETO;

typedef struct{
    int topo;
    OBJETO elementos[M];
    int qtde_elementos;
} PILHA_ESTATICA;

void inicializaPilha(PILHA_ESTATICA *pilha){
    pilha->qtde_elementos=0;
    pilha->topo=0;
}

bool estaVazia(PILHA_ESTATICA *pilha){
    return pilha->qtde_elementos == 0;
}

bool estaCheia(PILHA_ESTATICA *pilha){
    return pilha->qtde_elementos == M;
}

int tamanhoPilha(PILHA_ESTATICA *pilha){
    return pilha->qtde_elementos;
}

void inserePilha(PILHA_ESTATICA *pilha, int cpf, char nome[], int idade){
    if(estaCheia(pilha)==true){
        printf("\nPilha cheia -> insercao nao concluida");
        return;
    }
    
    pilha->elementos[pilha->topo].CPF=cpf;
    pilha->elementos[pilha->topo].idade=idade;
    strcpy(pilha->elementos[pilha->topo].nome, nome);

    pilha->qtde_elementos++;
    pilha->topo++;
}

OBJETO topoPilha(PILHA_ESTATICA *pilha){
    if(estaVazia(pilha)==true){
        printf("\nPilha Vazia: não há topo");
        return pilha->elementos[pilha->topo];
    }

    return pilha->elementos[pilha->topo -1];
}

void imprimeTopo(PILHA_ESTATICA *pilha){
    OBJETO p =topoPilha(pilha);
    if(estaVazia(pilha)==true){
        printf("\n\nNão eh possivel imprimir pois a pilha esta vazia");
    }

    printf("\n========================\n");
    printf("\n Obejto topo CPF=%d | NOme=%s | idade=%d\n", p.CPF, p.nome, p.idade);
    printf("\n========================\n");

}

void desempilha(PILHA_ESTATICA *pilha){
    if(estaVazia(pilha)== true){
        printf("\nA pilha já esta vazia\n");
        return ;
    }

    pilha->topo--;
    pilha->qtde_elementos--;
}

int main(void){

    PILHA_ESTATICA p;

    inicializaPilha(&p);

    //inserePilha(&p, 12345, "Maira do Carmo", 50);

    //inserePilha(&p, 54321, "Joao Jose", 45);
    
    desempilha(&p);

    imprimeTopo(&p);



    return EXIT_SUCCESS;
}