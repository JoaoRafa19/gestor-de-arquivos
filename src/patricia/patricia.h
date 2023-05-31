//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689
#ifndef patricia_h
#define patricia_h

#include "../lista/lista.h"


typedef char *String;
typedef enum
{
  interno,
  externo
} NodeType;

typedef struct TipoNo *Apontador;
typedef struct TipoNo
{
  NodeType tipo;
  int nDocumentos;
  union Node
  {
    struct
    {
      int indiceDif;
      Apontador esq, dir;
      char compare;
    } Ninterno;
    struct
    {
      Celula ocorrencias;
      String string;
      Celula *_lista;
    } Nexterno;

  } no;
} TipoNo;

typedef TipoNo *PATRICIA;

int pesquisa(String chave, PATRICIA P, Apontador *result);
Apontador insere(String word, PATRICIA *tree, int idDoc);

void imprime(PATRICIA P);

void buscaDoc(String termos, int nTermos, PATRICIA tree, String vet[], String* returnVet);

#endif