//
// Created by tiago on 11/05/2024.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int chave;
    struct no *Fesq;
    struct no *Fdir;
    struct no *pai;
}no;

typedef struct arvore{
    struct no *sentinela;
    int numElementos;
}arvore;

arvore *criaArvore(){
    arvore *arv;
    arv = (arvore*)malloc(sizeof(arvore));
    if (!arv)
        return NULL;
    arv->sentinela = (no*)malloc(sizeof(no));
    arv->sentinela->chave=-1000;
    arv->sentinela->Fdir = NULL;
    arv->sentinela->Fesq = NULL;
    arv->sentinela->pai = NULL;
    arv->numElementos=0;
    return arv;
}

int insereNo(arvore *arv, int valor){
    no *n,*aux,*ant;
    n = (no*)malloc(sizeof(no));
    if(!n)
        return 0;
    n->chave = valor;
    n->Fdir = NULL;
    n->Fesq = NULL;
    n->pai = NULL;
    if(!arv->sentinela->Fdir){
        arv->sentinela->Fdir = n;
        n->pai = arv->sentinela;
        arv->numElementos++;
        return 1;
    }
    aux = arv->sentinela->Fdir;
    while(aux){
        ant = aux;
        if(aux->chave<=n->chave)
            aux = aux->Fdir;
        else
            aux = aux->Fesq;
    }
    if(ant->chave <= n->chave)
        ant->Fdir = n;
    else
        ant->Fesq = n;
    n->pai = ant;
    arv->numElementos++;
    return 1;
}

int removeNo(arvore *arv, int valor){
    no *aux,*sucessor;
    int troca;
    aux = arv->sentinela->Fdir;
    if(!aux)
        return 0;
    while(aux && aux->chave != valor){
        if(aux->chave<=valor)
            aux = aux->Fdir;
        else
            aux = aux->Fesq;
    }
    if(!aux)
        return -1;
    arv->numElementos--;
    if(!aux->Fdir && !aux->Fesq){
        if(aux->pai->chave < valor)
            aux->pai->Fdir = NULL;
        else
            aux->pai->Fesq = NULL;
        free(aux);
        return 1;
    }
    if(!aux->Fdir){
        if(aux->pai->chave < valor)
            aux->pai->Fdir = aux->Fesq;
        else
            aux->pai->Fesq = aux->Fesq;
        aux -> Fesq ->pai = aux->pai;
        free(aux);
        return 1;
    }
    if(!aux->Fesq){
        if(aux->pai->chave < valor)
            aux->pai->Fdir = aux->Fdir;
        else
            aux->pai->Fesq = aux->Fdir;
        aux -> Fdir -> pai = aux->pai;
        free(aux);
        return 1;
    }
    sucessor = aux->Fdir;
    while (sucessor->Fesq)
    {
        sucessor = sucessor->Fesq;
    }

    troca = aux->chave;
    aux->chave = sucessor->chave;
    sucessor->chave = troca;

    if (sucessor->pai != aux)
    {
        sucessor->pai->Fesq = sucessor->Fdir;
        if (sucessor->Fdir)
        {
            sucessor->Fdir->pai = sucessor->pai;
        }
        free(sucessor);
        return 1;
    }

    if (sucessor->Fdir)
    {
        sucessor->pai->Fdir = sucessor->Fdir;
        sucessor->Fdir->pai = aux;
        free (sucessor);
        return 1;
    }
    aux->Fdir = NULL;
    free (sucessor);
    return 1;
}

void imprimeOrdem(no *raiz){
    if (raiz){
        imprimeOrdem(raiz->Fesq);
        printf("%d - %d\n",raiz->chave, raiz->pai->chave);
        imprimeOrdem(raiz->Fdir);
    }
}

void imprimePreOrdem(no *raiz){
    if (raiz){
        printf("%d - %d\n",raiz->chave, raiz->pai->chave);
        imprimePreOrdem(raiz->Fesq);
        imprimePreOrdem(raiz->Fdir);
    }
}

no *getRaiz(arvore *arv){
    return arv->sentinela->Fdir;
}

int getNumElementos(arvore *arv){
    return arv->numElementos;
}

void processaCarga(arvore *arv, char *nomeArquivo){
    FILE *arq;
    int aux;
    arq = fopen(nomeArquivo,"r");
    if(!arq)
        return;
    while(!feof(arq)){
        if(fscanf(arq,"%d",&aux)<1){
            printf("Erro\n");
            return;
        }else{
            if (!insereNo(arv, aux)) {
                printf("Erro\n");
                return;
            }
        }
    }
}