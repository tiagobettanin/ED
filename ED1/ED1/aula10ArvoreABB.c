#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct noArvore{
    int chave; 
    //demais informações que precisar para representar o objeto
    struct noArvore* esq;
    struct noArvore* dir;
}NO_ARVORE;

void inicializaABB(NO_ARVORE **raiz){
    (*raiz)=NULL;
}

bool estahVaziaABB(NO_ARVORE **raiz){
    return (*raiz)==NULL;
}

//não serah permitida a inserção de elementos repetidos
void insereABB(NO_ARVORE **no, int ch){
    if(estahVaziaABB(no)==true){
        (*no)=(NO_ARVORE*) malloc(sizeof(NO_ARVORE));
        if((*no)==NULL){ //testando se deu certo alocar espaço para o novo elemento
            printf("\nErro de alocação de memória \n\n");
            return;
        }
        (*no)->dir=(*no)->esq=NULL;
        (*no)->chave=ch;
        return;
    }
    if((*no)->chave==ch) return;
    //recursão
    if((*no)->chave > ch) insereABB(&((*no)->esq), ch); 
    else insereABB(&((*no)->dir), ch);

}

void preOrdem(NO_ARVORE** no){
    if(estahVaziaABB(no)==true) return;
    printf(" %d ", (*no)->chave);
    preOrdem(&(*no)->esq);
    preOrdem(&(*no)->dir);
}

void emOrdem(NO_ARVORE** no){
    if(estahVaziaABB(no)==true) return;
    emOrdem(&(*no)->esq);
    printf(" %d ", (*no)->chave);
    emOrdem(&(*no)->dir);
}

void posOrdem(NO_ARVORE** no){
    if(estahVaziaABB(no)==true) return;
    posOrdem(&(*no)->esq);
    posOrdem(&(*no)->dir);
    printf(" %d ", (*no)->chave);
}

void buscarElementoABB(NO_ARVORE** no, int ch){
     if(estahVaziaABB(no)==true){
        printf("\nElemento NAO encontrado: %d\n\n", ch);
        return;
     }

     if((*no)->chave == ch){
        printf("\nElemento encontrado: %d \n\n", ch);
        return;
     }
     else{
        if((*no)->chave > ch) buscarElementoABB(&(*no)->esq, ch);
        else buscarElementoABB(&(*no)->dir, ch);
     }
}

void destruirABB(NO_ARVORE** no){
    if(estahVaziaABB(no)==true){
         return;
    }
    destruirABB(&(*no)->esq);
    destruirABB(&(*no)->dir);
    free(*no);
    (*no)=NULL;
}

void deletaElementoABB(NO_ARVORE **no, int ch){
    //Caso 0: Elemento nao está na ABB
    if(estahVaziaABB(no)==true){
        printf("\n\nO elemento %d NAO estah na árvore\n\n", ch);
        return;
    }
    if((*no)->chave==ch){
        //Caso 1: Elemento a ser retirado é um nó folha
        if((*no)->esq==NULL && (*no)->dir==NULL){
            free(*no);
            (*no)=NULL;
            printf("\n\nElemento %d excluido com sucesso\n", ch);
            return;
        }

        //Caso 2A: Elemento a ser retirado tem apenas filho à esquerda
        if((*no)->esq!=NULL && (*no)->dir==NULL){
            NO_ARVORE *aux=(*no);
            (*no)=(*no)->esq;
            free(aux);
            printf("\n\nElemento %d excluido com sucesso\n", ch);
            return;
        }

        //Caso 2B: Elemento a ser retirado tem apenas filho à direita
        if((*no)->esq==NULL && (*no)->dir!=NULL){
            NO_ARVORE *aux=(*no);
            (*no)=(*no)->dir;
            free(aux);
            printf("\n\nElemento %d excluido com sucesso\n", ch);
            return;
        }

        //Caso 3: Elemento a ser retirado tem os 2 filhos
        //Opção de substituto: Maior elemento da subárvore esquerda
        if((*no)->esq!=NULL && (*no)->dir!=NULL){//obs: este if eh desnecessário. Por quê?
            NO_ARVORE *subEsq=(*no)->esq;
            while(subEsq->dir!=NULL){
                subEsq=subEsq->dir;
            }
            (*no)->chave=subEsq->chave;
            deletaElementoABB(&(*no)->esq, subEsq->chave); 
            printf("\n\nElemento %d excluido com sucesso\n", ch);
            return;
        }
    }
    else{
        if((*no)->chave > ch) deletaElementoABB(&(*no)->esq, ch);
        else deletaElementoABB(&(*no)->dir, ch);
    }
}


int main(void){
    NO_ARVORE *raiz;

    inicializaABB(&raiz);
    insereABB(&raiz, 65);
    insereABB(&raiz, 42);
    insereABB(&raiz, 51);
    insereABB(&raiz, 32);
    insereABB(&raiz, 12);
    insereABB(&raiz, 38);
    insereABB(&raiz, 80);
    insereABB(&raiz, 92);
    insereABB(&raiz, 71);
    insereABB(&raiz, 69);
    insereABB(&raiz, 60);
    insereABB(&raiz, 90);
    insereABB(&raiz, 34);

    deletaElementoABB(&raiz, 92); 
    
    //preOrdem(&raiz);
    //emOrdem(&raiz);
    //posOrdem(&raiz);

    //buscarElementoABB(&raiz, 93);

    destruirABB(&raiz);

}

/* Revisãozona de ponteiro!!!

void colocaEndereço(int *num, int **endNum){
    (*endNum)=num;
}


int main(void){  //desafio para agora
    int num=10;
    int *endNum=NULL;

    colocaEndereço(&num, &endNum);

    printf("\n\nO conteudo de endNum= %d  [end: %p == %p]  \n\n\n", *endNum, endNum, &num);

}
*/





//printf("\n\nO conteúdo é %d [end: %p == %p ]\n\n\n", *endNum, &num, endNum);