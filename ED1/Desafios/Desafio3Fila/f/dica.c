
//================================================================================================
// Esta implementação tem o intuito de auxiliar os alunos que tiveram dificuldade em manipular 
// o arquivo e extrair as informações necessárias para resolução da atividade. 
// --------->>>>>  Reforço: esta implementação NÃO resolve a atividade AP2
//================================================================================================



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 10

typedef  struct objeto {
    int id;
    char nome[100];
    char endereco[100];
    int numCasa;
}Objeto;

typedef struct filaEstat{
    Objeto casa[N];
    int qtdeElem;
    int ini;
    int fim;
} FilaEstatica;



void lerArquivo(FILE *fp, Objeto *obj){ //lê uma linha a cada chamada
    char linha[100];
    char* palavra;
    static int i=0;

   
   if (!feof(fp) && !fgets(linha, 100, fp))  {      //Se não for final de arquivo e a leitura da linha foi feita com sucesso
        printf("\n\nNao foi possível ler a linha");
        return;
    }
    
    //----- id
    palavra= strtok(linha,"{}; "); //como separador de informação temos os caracteres: {};\n
    obj->id = atol (palavra);

    //----- nome
    palavra= strtok(NULL,"{};\n"); //como separador de informação temos os caracteres: {};\n
    strcpy(obj->nome, palavra);

    //----- endereco
    palavra= strtok(NULL,"{};\n");  //como separador de informação temos os caracteres: {};\n
    strcpy(obj->endereco, palavra);

    //----- numero da casa
    palavra= strtok(linha,"{}; ");  //como separador de informação temos os caracteres: {};\n
    obj->numCasa = atol (palavra);    
}

void inicializaFila(FILE *fp, FilaEstatica *f){
    Objeto obj;
    f->ini=0;
    f->fim=0;
    while(f->fim<N){
        lerArquivo(fp, &obj);             //faz a leitura das linhas do arquivo colocando as informações em obj
        f->casa[f->fim++]=obj;
    }
    f->qtdeElem=N;
    f->fim=N-1;
}

void imprimeFilaEstatica(FilaEstatica *f){
    for(int cont=0; cont<f->qtdeElem; cont++){
        int i= (f->ini + cont) %N;
        printf("\n{ %d; %s; %s; %d }", f->casa[i].id, f->casa[i].nome, f->casa[i].endereco, f->casa[i].numCasa); 
    }
}

int menu(void){
    int num;
    printf("\n Digite 1:>> ");
    scanf("%d", &num);
    return num;
}

int main(int argc, char* argv[]){
    int sair=0;
    FilaEstatica fila;
    FILE *fp=fopen("visita.txt", "r"); //abrir utilizando argumento: fopen(argv[1], "r");
    if(fp==NULL) return 1;             //erro na abertura do arquivo

    inicializaFila(fp, &fila);         //coloca 10 casas na fila estática
    imprimeFilaEstatica(&fila);

    fclose(fp);
    return 0;
}