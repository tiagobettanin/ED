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
    (*raiz) = NULL;
}
//como funciona
bool estaVazia(NO_ARVORE **raiz){
    return (*raiz)==NULL;
}

//Não sera perditido a insesar de elementos repetidos
void insereABB(NO_ARVORE **no, int chave){
    if(estaVazia(no)==true){
        (*no) = (NO_ARVORE*) malloc(sizeof(NO_ARVORE));
        if((*no) == NULL){
            printf("Erro de alocaçaõd e momoria: ");
            return;
        }
        (*no)->esq = (*no)->dir = NULL;
        (*no)->chave = chave;
        return;
    }

    if((*no)->chave == chave)return;
    if((*no)->chave >chave) insereABB( &((*no)->esq),chave);//enderço no filho a esquerda por isso o e
    else insereABB( &((*no)->dir), chave);

}

void preOrdem(NO_ARVORE **no){
    if(estaVazia(no)==true) return;

    printf("%d ", (*no)->chave);

    preOrdem(&((*no)->esq));
    preOrdem(&((*no)->dir));
}

void emOrdem(NO_ARVORE **no){
    if(estaVazia(no)==true) return;

    emOrdem(&((*no)->esq));
    printf("%d ", (*no)->chave);
    emOrdem(&((*no)->dir));

}

void emOrdem2(NO_ARVORE **no){
    if(estaVazia(no)==true) return;

    emOrdem2(&((*no)->dir));
    printf("%d ", (*no)->chave);
    emOrdem2(&((*no)->esq));
}

void posOrdem(NO_ARVORE **no){
    if(estaVazia(no)==true) return;

    posOrdem(&((*no)->esq)); 
    posOrdem(&((*no)->dir));
    
    printf("%d ", (*no)->chave);
}

void buscarElemento(NO_ARVORE **no, int chave){
    if(estaVazia(no)==true){
        printf("\nElemtno não encontrado\n");
        return;
    } 

    if((*no)->chave == chave){
        printf("\nO elemtento existe %d\n", (*no)->chave);
        return;
    }else{
        if((*no)->chave >chave){
            buscarElemento( &((*no)->esq), chave);
        } else {
            buscarElemento( &((*no)->dir), chave);
        }
    }
    
}

void destroiABB(NO_ARVORE **no){
    if(estaVazia(no)==true) return;

    destroiABB(&((*no)->esq));
    destroiABB(&((*no)->dir));
    free(*no);
    (*no)=NULL;
}

void deletaElemento(NO_ARVORE **no, int chave){
    if(estaVazia(no)==true){
        printf("\nO elemtneo nao esta naarvore\n");
        return ;
    }

    if((*no)->chave==chave){
        if((*no)->esq == NULL && (*no)->dir == NULL){
            free(*no);
            (*no)=NULL;
            printf("\nElemetno excluido com sucesso\n");
            return;
        }

        if((*no)->esq != NULL && (*no)->dir == NULL){
            NO_ARVORE *aux = (*no);
            (*no)= (*no)->esq;
            free(aux);
            aux=NULL;
            printf("\nElemetno excluido com sucesso\n");
            return;
        }

        if((*no)->esq == NULL && (*no)->dir != NULL){
            NO_ARVORE *aux = (*no);
            (*no)= (*no)->esq;
            free(aux);
            aux=NULL;
             printf("\nElemetno excluido com sucesso\n");
            return;
        }
            //pegar o maior elemento da subarvore da esquerda(Quem esta mais a esquerda?) ou o maior da subarvore da diretoa(Quem esta mais adireita?) em relação ao elemtneo que quer excluir
        //este if é denecessario 
        if((*no)->esq != NULL && (*no)->dir != NULL){
            NO_ARVORE *subEsquerda = (*no)->esq;
            while(subEsquerda->dir != NULL){
                subEsquerda = subEsquerda->dir;
            }

            (*no)->chave = subEsquerda->chave;
            deletaElemento(&(*no)->esq, subEsquerda->chave);
            
            return;
        }

    }else{
        if((*no)->chave > chave) deletaElemento( &((*no)->esq), chave);
        else deletaElemento( &((*no)->dir), chave);
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
    insereABB(&raiz, 90);


    preOrdem(&raiz);
    printf("\n");

    emOrdem(&raiz);
    printf("\n");

    emOrdem2(&raiz);
    printf("\n");

    posOrdem(&raiz);
    printf("\n");

    buscarElemento(&raiz, 38);
    buscarElemento(&raiz, 1);

    deletaElemento(&raiz, 71);
 
    deletaElemento(&raiz, 51);
  
    deletaElemento(&raiz, 42);

    posOrdem(&raiz);
    printf("\n");

    destroiABB(&raiz);

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