//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689
#include "lista.h"

Celula * criaCelula( int idDoc){
    Pointer pagina = (Pointer) malloc(sizeof(struct tCelula));
    if(pagina == NULL){
        printf("Erro ao alocar memória");
    }
    pagina->indiceDoc = idDoc ;
    pagina->nOcorrencias = 1;
    pagina->prox = NULL;
    return pagina;
}   

/// @brief dj = número de documentos na coleção que contém o
/// termo tj
/// @param l 
/// @return 
int nDocs (Celula* l){
    int n= 0;
    Celula * aux = l;
    for(aux=l;aux != NULL; aux=aux->prox) n++;
    return n;
}

/// @brief fj,i = número de ocorrências do termo tj no documento i
/// @param _lista 
/// @param idDoc 
/// @return 
int ocorrenciasPorDocumento(Celula* _lista, int idDoc)
{
    Celula * aux;
    aux = _lista;
    
    if(aux == NULL)
    {
        return 0;
    }
    
    while(aux != NULL){
        if(aux->indiceDoc == idDoc){
            return aux->nOcorrencias;
        }
        aux = aux->prox;
    }
    return 0;
}

Celula* adicionaOcorrencia(int idDoc, Celula* _lista){
    Celula * aux;
    aux = _lista;
    if(aux == NULL){
        return criaCelula(idDoc);
    }
    while(aux->prox != NULL){
        if(aux->indiceDoc == idDoc){
            aux->nOcorrencias++;
            return _lista;
        }
        aux = aux->prox;
    }
    if(aux->indiceDoc == idDoc){
        aux->nOcorrencias++;
        return _lista;
    }
    aux->prox = criaCelula(idDoc);
    return _lista;
}


void imprimeLista(Celula * _lista){
    Celula * aux;
    aux = _lista;
    while(aux != NULL){
        printf("Documento: %d\t", aux->indiceDoc);
        printf("Ocorrencias: %d\n", aux->nOcorrencias);
        aux = aux->prox;
    }
}