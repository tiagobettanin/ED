#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct noArvore{
    int chave; 
    //demais informações que precisar para representar o objeto
    struct noArvore* esq;
    struct noArvore* dir;
    int h; // altura
}NO_ARVORE;

void inicializaAVL(NO_ARVORE **raiz){
    (*raiz)=NULL;
}

bool estahVaziaAVL(NO_ARVORE **raiz){
    return (*raiz)==NULL;
}

int maxAlturaFilhos(NO_ARVORE **no){
   int hE;
   int hD;
   if((*no)->esq!=NULL) hE=(*no)->esq->h;
   else hE=-1;

   if((*no)->dir!=NULL) hD=(*no)->dir->h;
   else hD=-1;

   return hE>hD ? hE : hD;

}

int calculaFB(NO_ARVORE **no){
    int hD, hE;
    hD = (*no)->dir!=NULL ? (*no)->dir->h : -1; //altura do filho direita
    hE = (*no)->esq!=NULL ? (*no)->esq->h : -1; //altura do filho esquerda
    return (hD - hE);  //cálculo do fator de balanceamento do no
}

void rotacaoSimplesEsquerda(NO_ARVORE **no){
    NO_ARVORE *aux=(*no)->dir;
    (*no)->dir=aux->esq;
    aux->esq=(*no);
    (*no)=aux;
    (*no)->esq->h = 1 + maxAlturaFilhos(&(*no)->esq);
    (*no)->h = 1 + maxAlturaFilhos(no);
}

void rotacaoSimplesDireita(NO_ARVORE **no){
    NO_ARVORE *aux=(*no)->esq;
    (*no)->esq=aux->dir;
    aux->dir=(*no);
    (*no)=aux;
    (*no)->dir->h = 1 + maxAlturaFilhos(&(*no)->dir);
    (*no)->h = 1 + maxAlturaFilhos(no); 
}

//não serah permitida a inserção de elementos repetidos
void insereAVL(NO_ARVORE **no, int ch){
    if(estahVaziaAVL(no)==true){
        (*no)=(NO_ARVORE*) malloc(sizeof(NO_ARVORE));
        if((*no)==NULL){ //testando se deu certo alocar espaço para o novo elemento
            printf("\nErro de alocação de memória \n\n");
            return;
        }
        (*no)->dir=(*no)->esq=NULL;
        (*no)->chave=ch;
        (*no)->h = 0;
        return;
    }
    if((*no)->chave==ch) return;
    //recursão
    if((*no)->chave > ch) insereAVL(&((*no)->esq), ch);
    else insereAVL(&((*no)->dir), ch);
    (*no)->h = 1 + maxAlturaFilhos(no);
    int fb = calculaFB(no);  //cálculo do fator de balanceamento do no

    switch(fb){ //lembrar da tabela feita em aula
        case  2: //rotação à esquerda            
            switch(calculaFB(&(*no)->dir)){ //consultar o fb do filho à direita
                case  0:;
                case  1: //rotação simples à esquerda
                    rotacaoSimplesEsquerda(no);
                    break;

                case -1: //rotação dupla à esquerda
                    //Rotação 1: Rotação Simples Direita no filho à direita
                    rotacaoSimplesDireita(&(*no)->dir);
                    //Rotação 2: Rotação Simples Esquerda no nó com fb=+2
                    rotacaoSimplesEsquerda(no);
                    break;
            }            
            break;
        case -2: //rotação à direita
            switch(calculaFB(&(*no)->esq)){ //consultar o fb do filho à esquerda
                case  0:;
                case -1: //rotação simples à direita
                    rotacaoSimplesDireita(no);
                    break;

                case  1: //rotação dupla à direita
                    //Rotação 1: Rotação Simples Esquerda no filho à esquerda
                    rotacaoSimplesEsquerda(&(*no)->esq);
                    //Rotação 2: Rotação Simples Direita no nó com fb=-2
                    rotacaoSimplesDireita(no);
                    break;
            }
            break;
    }

}

void preOrdem(NO_ARVORE** no){
    if(estahVaziaAVL(no)==true) return;
    printf(" info=%d[h=%d] ", (*no)->chave, (*no)->h);
    preOrdem(&(*no)->esq);
    preOrdem(&(*no)->dir);
}

void emOrdem(NO_ARVORE** no){
    if(estahVaziaAVL(no)==true) return;
    emOrdem(&(*no)->esq);
    printf(" %d ", (*no)->chave);
    emOrdem(&(*no)->dir);
}

void posOrdem(NO_ARVORE** no){
    if(estahVaziaAVL(no)==true) return;
    posOrdem(&(*no)->esq);
    posOrdem(&(*no)->dir);
    printf(" %d ", (*no)->chave);
}

void buscarElementoAVL(NO_ARVORE** no, int ch){
     if(estahVaziaAVL(no)==true){
        printf("\nElemento NAO encontrado: %d\n\n", ch);
        return;
     }

     if((*no)->chave == ch){
        printf("\nElemento encontrado: %d \n\n", ch);
        return;
     }
     else{
        if((*no)->chave > ch) buscarElementoAVL(&(*no)->esq, ch);
        else buscarElementoAVL(&(*no)->dir, ch);
     }
}

void destruirAVL(NO_ARVORE** no){
    if(estahVaziaAVL(no)==true){
         return;
    }
    destruirAVL(&(*no)->esq);
    destruirAVL(&(*no)->dir);
    free(*no);
    (*no)=NULL;
}

void deletaElementoAVL(NO_ARVORE **no, int ch){
    //Caso 0: Elemento nao está na AVL
    if(estahVaziaAVL(no)==true){
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
            deletaElementoAVL(&(*no)->esq, subEsq->chave); 
            printf("\n\nElemento %d excluido com sucesso\n", ch);
            return;
        }
    }
    else{
        if((*no)->chave > ch) deletaElementoAVL(&(*no)->esq, ch);
        else deletaElementoAVL(&(*no)->dir, ch);
    }
    //======================================
    (*no)->h = 1 + maxAlturaFilhos(no);
    int fb = calculaFB(no);  //cálculo do fator de balanceamento do no

    switch(fb){ //lembrar da tabela feita em aula
        case  2: //rotação à esquerda            
            switch(calculaFB(&(*no)->dir)){ //consultar o fb do filho à direita
                case  0:;
                case  1: //rotação simples à esquerda
                    rotacaoSimplesEsquerda(no);
                    break;

                case -1: //rotação dupla à esquerda
                    //Rotação 1: Rotação Simples Direita no filho à direita
                    rotacaoSimplesDireita(&(*no)->dir);
                    //Rotação 2: Rotação Simples Esquerda no nó com fb=+2
                    rotacaoSimplesEsquerda(no);
                    break;
            }            
            break;
        case -2: //rotação à direita
            switch(calculaFB(&(*no)->esq)){ //consultar o fb do filho à esquerda
                case  0:;
                case -1: //rotação simples à direita
                    rotacaoSimplesDireita(no);
                    break;

                case  1: //rotação dupla à direita
                    //Rotação 1: Rotação Simples Esquerda no filho à esquerda
                    rotacaoSimplesEsquerda(&(*no)->esq);
                    //Rotação 2: Rotação Simples Direita no nó com fb=-2
                    rotacaoSimplesDireita(no);
                    break;
            }
            break;
    }
}


int main(void){
    NO_ARVORE *raiz;

    inicializaAVL(&raiz);
    insereAVL(&raiz, 20);
    insereAVL(&raiz, 40);
    insereAVL(&raiz, 30);
    insereAVL(&raiz, 10);
    insereAVL(&raiz, 15);
    insereAVL(&raiz, 5);
    insereAVL(&raiz, 2);
    insereAVL(&raiz, 80);
    insereAVL(&raiz, 92);
    insereAVL(&raiz, 71);
    insereAVL(&raiz, 69);
    insereAVL(&raiz, 60);
    insereAVL(&raiz, 90);
    insereAVL(&raiz, 34);

    deletaElementoAVL(&raiz, 92); 
    
    preOrdem(&raiz);
    //emOrdem(&raiz);
    //posOrdem(&raiz);

    //buscarElementoAVL(&raiz, 93);

    destruirAVL(&raiz);

}