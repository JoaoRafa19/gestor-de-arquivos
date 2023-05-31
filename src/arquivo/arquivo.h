//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689
#ifndef arquivo_h
#define arquivo_h

#include "../patricia/patricia.h"


void leArquivo(PATRICIA *patricia, String filename);
void leDocumento(PATRICIA *patricia, String filename, int fileNumber);
String getFiles( String filename, char** filenames, int* nFiles);

#endif