//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689

#ifndef lista
#define lista

#include<stdlib.h>  
#include <stdio.h>
#include <string.h>
#include <ctype.h>

typedef struct tCelula* Pointer;


typedef struct tCelula {
    int nOcorrencias;
    int indiceDoc;
    Pointer prox;
} Celula;


Celula* adicionaOcorrencia(int idDoc, Celula* _lista);
void imprimeLista(Celula * _lista);
int nDocs (Celula* l);
int ocorrenciasPorDocumento(Celula* _lista, int idDoc);

#endif