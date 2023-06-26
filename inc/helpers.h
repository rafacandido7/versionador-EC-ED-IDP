#ifndef HELPERS_H
#define HELPERS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <dirent.h>

void print(char* text, char* color);

// Generates
char* generateHash(int length); // Gera um hash aleatório com base no tamanho passado

// Creates
void createTxtFile(const char* path, char* fileName, char* text); // Cria um arquivo com o nome do arquivo e com o texto passado
void createFolder (char* folderName, char* newFolderName); // Cria uma pasta com o nome passado
void createLogFolder(const char* folderPath); // Cria a pasta de Logs do Versionador
void createRepo(const char* folderName); // Cria um repositório com o nome passado
void createSnapshot(const char* text); // Cria um snapshot com o texto passado sobre os arquivos adicionados
void createContent(const char *path, const char *text); // Cria um arquivo com o conteúdo passado

// Verifies
void verifyAllocation (void* pointer); // Verifica se a alocação de memória foi bem sucedida
bool verifyFile(const char *fileName); // Verifica se um arquivo existe
bool verifyDirectory(const char *folderPath); // verifica se uma pasta existe e se tem arquivos/diretorios lá
bool strIsEqual(const char *str1, const char *str2); // Verifica se duas strings são iguais e retorna um booleano
bool verifyVersionadorFolder(void); // Verifica se a pasta .versionador existe
bool verifySnapshot(const char *snapshot); // Verifica se um snapshot existe

// Gets
char** getFilesInDirectory(const char* directoryPath, int* numFiles); // Retorna os arquivos de uma pasta
const char* getTxtContentFile(const char* path);
char* getCurrentDirectory(); // Retorna o diretório atual (lembre-se de dar free na memória)
void getShapshot(const char *snapshot); // Retorna os arquivos de um snapshot
void getTempFiles(void); // Retorna os arquivos temporários

// File Handle Functions
bool addFiles(int argc, const char* argv[]);

// Test functions
void printArgv(int argc, const char* argv[]); // Printa os argumentos passados

// Deletes
bool clearFolder(const char* folderPath); // Limpa uma pasta

// Show
void showLog(void); // Mostra o log do versionador
void showLogsContent(void); // Mostra o log do versionador
void showSnapshotContent(const char* snapshotName); // Mostra o conteúdo de um snapshot

// Frees
void freeStringArray(char** folders, int numFolders); // Libera a memória de um vetor de strings

// Prints
void printTxtFilesContent(const char* directoryPath); // Printa o conteúdo dos arquivos .txt de uma pasta
void printTxtContent(FILE* file); // Printa o conteúdo de um arquivo .txt

#endif
