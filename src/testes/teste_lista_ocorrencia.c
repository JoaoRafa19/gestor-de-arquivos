//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689

#include "../lista/lista.h"




int main(){
    Celula * _lista = NULL;
    _lista = adicionaOcorrencia(1, _lista);
    _lista = adicionaOcorrencia(1, _lista);

    _lista = adicionaOcorrencia(2, _lista);
    _lista = adicionaOcorrencia(2, _lista);
    _lista = adicionaOcorrencia(2, _lista);
    _lista = adicionaOcorrencia(2, _lista);
    _lista = adicionaOcorrencia(3, _lista);
    _lista = adicionaOcorrencia(4, _lista);
    _lista = adicionaOcorrencia(5, _lista);

   printf("%d\n", nDocs(_lista));
   printf("%d\n", ocorrenciasPorDocumento(_lista, 2));

    imprimeLista(_lista);
}