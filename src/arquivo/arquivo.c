//João Pedro - 3899
//Gabriel Ferreira - 4705
//Gabriel Ryan - 4688
//Lucas Borges - 4689
#include "arquivo.h"

void strip(String string, char *args);
void stripFile(String string, char *args);

/// @brief Lê o arquivo principal de entrada com os nomes dos outros arquivos
/// que serão lidos pelo método `readDoc`
/// @param patricia
/// @param filename
void leArquivo(PATRICIA *patricia, String filename)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        puts("arquivo nao pode ser lido.");
        printf("Verifique o arquivo %s", filename);
        return;
    }

    char *contents = NULL;
    int line = 0;
    size_t len = 0;
    while (getline(&contents, &len, file) != EOF)
    {
        if (line == 0)
        {
            // numero de arquivos
            int nFiles = atoi(contents);
        }
        else
        {
            leDocumento(patricia, contents, line);
        }
        line++;
    }
    fclose(file);
    free(contents);
    return;
}


/// @brief Busca o numero de arquivos
/// @param patricia
/// @param filename
String getFiles( String filename, String* filenames, int* nFiles)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        puts("arquivo nao pode ser lido.");
        printf("Verifique o arquivo %s", filename);
        return 0;
    }
    char* files = malloc(sizeof(char));
    strcpy(files, "");
    int numberOfFiles = 0;
    char *contents = NULL;
    int line = 0;
    size_t len = 0;
    while (getline(&contents, &len, file) != EOF)
    {
        if (line == 0)
        {
            // numero de arquivos
            numberOfFiles = atoi(contents); 
            files = (String) malloc( 20*sizeof(char));
            strcpy(files,"");
            
        }
        else
        {  
            stripFile(contents, "");
            char* files2 = (String) malloc((strlen(contents)*sizeof(char)) + (3*sizeof(char)) + (strlen(files)*sizeof(char)));
            strcpy(files2, files);
            strcat(files2, contents);
            files = files2;

            strcat(files, "\n");
        }
            line++;
    }
    fclose(file);
    free(contents);
    if(filenames != NULL){
        int size = strlen(files);
        (*filenames) = (String) malloc(strlen(files)*sizeof(char));
        strcpy((*filenames), files);
    }
    if(nFiles != NULL){
        *nFiles = numberOfFiles;
    }
    return files;
}

/// @brief Lê o conteúdo dos arquivos dos doscumentos e armazena na arvore de busca com o numero do arquivos que foi lido
/// @param patricia
/// @param filename
/// @param fileNumber
void leDocumento(PATRICIA *patricia, String filename, int fileNumber)
{
    stripFile(filename, "");
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Verifique o arquivo %s\n", filename);
        puts("documento nao pode ser lido.");
        return;
    }
    char *contents = NULL;
    int line = 1;
    size_t len = 0;
    while (getline(&contents, &len, file) != EOF)
    {
        String word = strtok(contents, " ");
        while (word != NULL)
        {
            strip(word, "");
            if (strlen(word) > 0)
            {
                *patricia = insere(word, patricia, fileNumber);
            }
            word = strtok(NULL, " ");
        }
        line++;
    }
    fclose(file);
    free(contents);
    return;
}

/// @brief Remove caracteres especiais da string
/// @param string
void strip(String string, char *args)
{
    unsigned int i = 0;
    unsigned int x = 0;
    char c;
    while ((c = string[i++]) != '\0' )
    {
        if ( isalnum(c) )
        {
            string[x++] = c;
        }
    }
    string[x] = '\0';
}


/// @brief Remove caracteres especiais da string
/// @param string
void stripFile(String string, char *args)
{
    unsigned int i = 2;
    unsigned int x = 2;
    char c;
    while ((c = string[i++]) != '\0' )
    {
        if (isalnum(c) || c == '.' ||c==',' )
        {
            string[x++] = c;
        }
    }
    string[x] = '\0';
}