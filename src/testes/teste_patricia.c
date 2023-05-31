//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689

#include "../patricia/patricia.h"



int main(){
    Apontador patricia = NULL;


    patricia = insere("teste", &patricia, 1);
    patricia = insere("alo", &patricia, 1);
    patricia = insere("teta", &patricia, 1);
    patricia = insere("testiculo", &patricia, 2);

    printf("%d\n", pesquisa("teste", patricia, NULL));
    printf("%d\n",pesquisa("alo", patricia, NULL));
    printf("%d\n",pesquisa("tetas", patricia, NULL));
    printf("%d\n",pesquisa("teta", patricia, NULL));
    
    imprime(patricia);


    return 0;
}