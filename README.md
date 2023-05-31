# Tp_AEDSII

TP de AEDS

## Tipos de dados

### String

 Abstracao de uma string, para facilitar a manipulacao de strings em C.

```c
typedef char* String;
```

### Lista

## Métodos auxiliares

### Função para limpar caracteres especiais da entrada

adaptada do site [geeksforgeeks](https://www.geeksforgeeks.org/c-program-to-trim-leading-white-spaces-from-string/)

```c
void strip(String string){
    unsigned int i = 2;
    unsigned int x = 2;
    char c;
    while((c = string[i++]) != '\0')
    {
        if(isalnum(c) || c =='.' )
        {
            string[x++] = c;
        }
    }
    string[x]='\0';
}
```

### Função para contar caracteres adaptada do site [tutorialspoint](https://www.tutorialspoint.com)
```c
int countChars(char *s, char c)
{
    return *s == '\0' ? 0 : countChars(s + 1, c) + (*s == c);
}
```




## Compilando o projeto

![CMake](
https://img.shields.io/badge/CMake-3.16.3-blue
)
![GTK](
    https://img.shields.io/badge/GTK-3.0-blue
)

Para compilar todos os arquivos do projeto execute o comando do cmake e makefile

```shell
cd src && make
```

## Instalation Guide

### Linux

#### Install build-essential

```bash
sudo apt-get install build-essential
```

#### Install clang

```bash
sudo apt-get install clang

```

#### Install g++

```bash
sudo apt-get install g++
```

### Install Pkg-Config

```bash
sudo apt-get install pkg-config
```

#### Install CMake

```bash
sudo apt-get install cmake
```

#### Install Gtk

```bash
sudo apt-get install libgtk-3-dev
```

#### Install
