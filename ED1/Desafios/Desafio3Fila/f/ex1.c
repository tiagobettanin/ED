#include<stdlib.h>
#include<stdio.h>
#include<string.h>

#define M 10

typedef struct{
    int id;
    char nome[100];
    char endereco[100];
    int numCasa;
}   CASA;

typedef struct{
    int inicial;
    int fim;
    int qtd_elementos;
    CASA *casa[M];
}   FILA_ESTATICA;



void lerArquivo(FILE *arq, FILA_ESTATICA *f) {
    for (int i = 0; i < M; i++) {
        // Lê uma linha do arquivo no formato esperado e armazena os dados na estrutura
        fscanf(arq, " { %d ; %99[^;] ; %99[^;] ; %d } ", &f->casa[i]->id, f->casa[i]->nome, f->casa[i]->endereco, &f->casa[i]->numCasa);
    }
}

void inicializaFila(FILE *arq, FILA_ESTATICA *f){
    f->qtd_elementos = f->inicial = f->fim = 0;
    lerArquivo( arq, &f);
}

int main(void){
    FILE* arq = fopen("visita.txt", "r");
    if(arq == NULL){
        printf("Não foi possivel abiri o arq. ");
        return EXIT_FAILURE;
    }
    FILA_ESTATICA f;
    
    inicializaFila( arq, &f);
    

    for(int i=0; i<M; i++){
        printf("{ %d; %s; %s; %d }\n", f.casa[i]->id, f.casa[i]->nome, f.casa[i]->endereco, f.casa[i]->numCasa);
    }  


    fclose(arq);
    return 0;
}