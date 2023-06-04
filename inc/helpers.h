#ifndef HELPERS_H_
#define HELPERS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <dirent.h>
#include "../inc/versionador.h"
#include "../inc/helpers.h"
#include "../inc/list.h"
#include "../inc/fileHandler.h"


void print(char* text, char* color);

// Generates
char* generateHash(int length); // Gera um hash aleatório com base no tamanho passado

// Creates
void createTxtFile(const char* path, char* fileName, char* text); // Cria um arquivo com o nome do arquivo e com o texto passado
void createFolder (char* folderName, char* newFolderName); // Cria uma pasta com o nome passado
void createLogFolder(const char* folderPath); // Cria a pasta de Logs do Versionador
void createRepo(const char* folderName); // Cria um repositório com o nome passado

// Verifies
void verifyAllocation (void* pointer); // Verifica se a alocação de memória foi bem sucedida
bool verifyFile(const char *fileName); // Verifica se um arquivo existe
bool verifyDirectory(const char *folderPath); // verifica se uma pasta existe e se tem arquivos/diretorios lá
bool strIsEqual(const char *str1, const char *str2); // Verifica se duas strings são iguais e retorna um booleano
bool verifyVersionadorFolder(void); // Verifica se a pasta .versionador existe

// Gests
char* getCompletePath(const char* beginPath, const char* endPath); // Retorna o caminho completo de um arquivo

// File Handle Functions
void addFiles(int argc, const char* argv[]);

// Test functions
void printArgv(int argc, const char* argv[]); // Printa os argumentos passados






#endif
