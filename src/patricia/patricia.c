// João Pedro - 3899
// Gabriel Ferreira - 4705
// Gabriel Ryan - 4688
// Lucas Borges - 4689
#include "patricia.h"
#include "../arquivo/arquivo.h"
#include <stdlib.h>
#include <math.h>
#include <gtk/gtk.h>

#pragma region private functions
Apontador insereInterno(String word, PATRICIA *P, int index, char diff, int idDoc);
Apontador insereExterno(String word, PATRICIA *P, int idDoc);
short verificaInterno(Apontador Node);
short verificaExterno(Apontador Node);
Apontador criaNoInterno(Apontador *esq, Apontador *dir, int index, char compare, int idDoc);
Apontador criaNoExterno(String palavra, PATRICIA *P, int idDoc);

void swap(char **str1, char **str2, double *relevance1, double *relevance2)
{
    char *temp_str = *str1;
    *str1 = *str2;
    *str2 = temp_str;

    double temp_rel = *relevance1;
    *relevance1 = *relevance2;
    *relevance2 = temp_rel;
}

int partition(char **strings, double *relevance, int low, int high)
{
    double pivot = relevance[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++)
    {
        if (relevance[j] > pivot)
        {
            i++;
            swap(&strings[i], &strings[j], &relevance[i], &relevance[j]);
        }
    }
    swap(&strings[i + 1], &strings[high], &relevance[i + 1], &relevance[high]);
    return (i + 1);
}

void quicksort(char **strings, double *relevance, int low, int high)
{
    if (low < high)
    {
        int pi = partition(strings, relevance, low, high);
        quicksort(strings, relevance, low, pi - 1);
        quicksort(strings, relevance, pi + 1, high);
    }
}

void sortStringsByRelevance(char **strings, double *relevance, int size)
{
    quicksort(strings, relevance, 0, size - 1);
}

#pragma endregion

///@brief Verifica o tipo do nó
short verificaExterno(Apontador Node)
{
    return (Node->tipo == externo);
}
///@brief Verifica o tipo do nó
short verificaInterno(Apontador Node)
{
    return (Node->tipo == interno);
}

/// @brief Cria no interno da arvore
/// @param esq
/// @param dir
/// @param index
/// @param compare
Apontador criaNoInterno(Apontador *esq, Apontador *dir, int index, char compare, int idDoc)
{
    Apontador P;
    P = (Apontador)malloc(sizeof(TipoNo));
    P->tipo = interno;
    P->no.Ninterno.esq = *esq;
    P->no.Ninterno.dir = *dir;
    P->no.Ninterno.indiceDif = index;
    P->no.Ninterno.compare = compare;

    return P;
}

/// @brief Cria no externo da arvore
/// @param palavra
/// @param P
Apontador criaNoExterno(String palavra, PATRICIA *P, int idDoc)
{
    *P = (Apontador)malloc(sizeof(TipoNo));
    (*P)->tipo = externo;
    (*P)->no.Nexterno.string = (char *)malloc(sizeof(char) * strlen(palavra));
    (*P)->no.Nexterno.string = (char *)malloc(sizeof palavra * (strlen(palavra) + 1));
    if (!(*P)->no.Nexterno.string)
    {
        printf("Erro ao alocar\n");
    }
    else
    {
        strcpy((*P)->no.Nexterno.string, palavra);
    }
    (*P)->no.Nexterno._lista = NULL;
    (*P)->no.Nexterno._lista = adicionaOcorrencia(idDoc, (*P)->no.Nexterno._lista);
    return *P;
}

/// @brief Pesquisa uma palavra na arvore
/// @param chave
/// @param P
int pesquisa(String chave, PATRICIA P, Apontador *result)
{
    if(!(*chave)){
        return 0;
    }
    if(strcmp(chave, "") == 0){
        return 0;
    }
    int len = strlen(chave);
    int indiceDif = P->no.Ninterno.indiceDif;

    if (verificaExterno(P))
    {
        if (strcmp(chave, P->no.Nexterno.string) == 0)
        {
            if (result != NULL)
            {
                (*result) = (Apontador)malloc(sizeof(TipoNo));
                (*result) = P;
                return 1;
            }
        };
        return 0;
    }

    if (len < P->no.Ninterno.indiceDif)
        pesquisa(chave, P->no.Ninterno.esq, result);
    else if (chave[indiceDif] < P->no.Ninterno.compare)
        pesquisa(chave, P->no.Ninterno.esq, result);
    else
        pesquisa(chave, P->no.Ninterno.dir, result);
}

/// @brief Insere um novo nó interno na arvore
/// @param chave
/// @param patricia
/// @param Index
/// @param Distinct_char
/// @return
Apontador insereInterno(String chave, PATRICIA *patricia, int index, char dif, int idDoc)
{
    Apontador novoNo = NULL;

    if (verificaExterno(*patricia))
    {
        criaNoExterno(chave, &novoNo, idDoc);
        if (strcmp((*patricia)->no.Nexterno.string, chave) < 0)
        {
            return (criaNoInterno(patricia, &novoNo, index, dif, idDoc));
        }
        else if (strcmp((*patricia)->no.Nexterno.string, chave) > 0)
        {
            return (criaNoInterno(&novoNo, patricia, index, dif, idDoc));
        }
        return NULL;
    }

    else if (index < (*patricia)->no.Ninterno.indiceDif)
    {
        criaNoExterno(chave, &novoNo, idDoc);
        if (chave[index] < dif)
            return (criaNoInterno(&novoNo, patricia, index, dif, idDoc));
        else
            return (criaNoInterno(patricia, &novoNo, index, dif, idDoc));
    }
    else
    {
        int indiceDif = (*patricia)->no.Ninterno.indiceDif;
        if (chave[indiceDif] < (*patricia)->no.Ninterno.compare)
        {
            (*patricia)->no.Ninterno.esq = insereInterno(chave, &(*patricia)->no.Ninterno.esq, index, dif, idDoc);
        }
        else
        {
            (*patricia)->no.Ninterno.dir = insereInterno(chave, &(*patricia)->no.Ninterno.dir, index, dif, idDoc);
        }
        return (*patricia);
    }
}

Apontador insere(String word, PATRICIA *tree, int idDoc)
{
    if (*tree == NULL)
    {
        return criaNoExterno(word, tree, idDoc);
    }
    if (pesquisa(word, *tree, NULL) == 1)
        return *tree;
    else
    {
        PATRICIA P = *tree;
        int aux;
        char dif;
        while (!verificaExterno(P))
        {
            dif = word[P->no.Ninterno.indiceDif];

            if (dif < P->no.Ninterno.compare)
            {
                P = P->no.Ninterno.esq;
            }
            else
            {
                P = P->no.Ninterno.dir;
            }
        }
        if (strcmp(P->no.Nexterno.string, word) == 0)
        {
            P->no.Nexterno._lista = adicionaOcorrencia(idDoc, P->no.Nexterno._lista); // TODO: adicionar o numero do arquivo
            return (*tree);
        }
        else
        {
            char dif;
            int menor = (strlen(word) < strlen(P->no.Nexterno.string)) ? strlen(word) : strlen(P->no.Nexterno.string);
            aux = 0;
            while (aux <= menor)
            {
                if (word[aux] != P->no.Nexterno.string[aux])
                {
                    if (word[aux] < P->no.Nexterno.string[aux])
                    {
                        dif = P->no.Nexterno.string[aux];
                        break;
                    }
                    else
                    {
                        dif = word[aux];
                        break;
                    }
                }
                aux++;
            }
            return insereInterno(word, tree, aux, dif, idDoc);
        }
    }
}

/// @brief Imprime a arvore
/// @param P
void imprime(PATRICIA P)
{
    if (P == NULL)
        return;
    if (verificaInterno(P))
        imprime(P->no.Ninterno.esq);

    if (verificaExterno(P))
        printf("%s\n", P->no.Nexterno.string);

    if (verificaInterno(P))
        imprime(P->no.Ninterno.dir);
}

/// @brief peso do termo tj no documento i
/// @param i id do documento
double wij(Apontador j, int N, int i)
{
    int fij = ocorrenciasPorDocumento(j->no.Nexterno._lista, i + 1);
    int dj = nDocs(j->no.Nexterno._lista);
    double w = fij * (log(N) / dj);
    return w;
}

int ni(PATRICIA P, int idDoc, int *Ntermos)
{
    if (P == NULL)
        return 0;
    if (verificaInterno(P))
        ni(P->no.Ninterno.esq, idDoc, Ntermos);

    if (verificaExterno(P))
        (*Ntermos)++;

    if (verificaInterno(P))
        ni(P->no.Ninterno.dir, idDoc, Ntermos);
}
double Ni(PATRICIA P, int idDoc)
{
    int ntermos;
    ni(P, idDoc, &ntermos);
    return ntermos;
}

int r(int i)
{
}

/// @brief Busca os documentos que contém a palavra chave e os retorna em ordem de relevância
/// @param termos (Até 10 termos)
/// @param p
/// @return
void buscaDoc(String termos, int nTermos, PATRICIA tree, String vet[], String *returnVet)
{

    TipoNo *palavras[nTermos];
    int wVet[nTermos];

    for (int i = 0; i < nTermos; i++){
        int res = pesquisa(vet[i], tree, &palavras[i]);
        printf("%d", res);
        if(res == 0){
            (*returnVet) = (String)malloc(sizeof(char) *strlen("Nao encontrado"));
            sprintf((*returnVet), "Nao encontrado" );
            return;
        }
    }

    int N;
    String files;
    files = getFiles("entrada.txt", &files, &N);
    char *fileVet[N];
    char *p = strtok(files, "\n");
    int i = 0;
    while (p != NULL)
    {
        fileVet[i] = malloc(sizeof(char) * strlen(p));
        strcpy(fileVet[i], p);
        p = strtok(NULL, "\n");
        i++;
    }

    double rel[N][nTermos];
    int sum = 0;

    for (int i = 0; i < N; i++){
        for (int j = 0; j < nTermos; j++){
            double sum = 0;
            for (int k = 0; k < nTermos; k++){
                double w = wij(palavras[k], N, i);
                sum += w;
            }
            rel[i][j] = (1 / Ni(tree, i)) * sum;
        }
    }

    double relVe[N];
    for (int i = 0; i < N; i++){
        double sum = 0;
        for (int j = 0; j < nTermos; j++){
            sum += rel[i][j];
        }
        relVe[i] = sum;
    }

    sortStringsByRelevance(fileVet, relVe, N);

    (*returnVet) = (String)malloc((sizeof(char) * strlen(fileVet[0]) + (2 * sizeof(char)) + (2 * sizeof(char))));
    strcpy((*returnVet), "1º-");
    fileVet[0][0] = ' ';
    fileVet[0][1] = ' ';
    strcat((*returnVet), fileVet[0]);
    strcat((*returnVet), "\n");
    for (int i = 1; i < N; i++){
        fileVet[i][0] = ' ';
        fileVet[i][1] = ' ';
        char *files2 = (String)malloc((strlen((*returnVet)) * sizeof(char)) + +(strlen(fileVet[i]) * sizeof(char)) + (5 * sizeof(char)));
        char pos[5];
        sprintf(pos, "%dº-", i+1);
        strcpy(files2, (*returnVet));
        strcat(files2, pos);
        strcat(files2, fileVet[i]);
        strcat(files2, "\n");
        (*returnVet) = files2;
    }
}
