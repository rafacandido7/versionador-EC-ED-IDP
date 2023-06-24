#ifndef LIST_FILE_H
#define LIST_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>

typedef struct _archive Archive;

typedef struct _fileListNode FileListNode;

typedef struct _fileList FileList;

FileList* createList(void);
int push(FileList* list, FILE* file, const char* fileName); // Insere e retorna o tamanho da lista
int unshift(FileList* list, FILE* file, const char* fileName); // Insere e retorna o elemento na primeira posição
Archive* pop(FileList* list); // Remove e retorna o último elemento
Archive* shift(FileList* list); // Remove e retorna o elemento na primeira posição
FileListNode* getLastElement(FileListNode* node); // Procura pelo último elemento da lista
int length(FileList* list); // Retorna o tamanho da lista
bool isEmpty(FileList* list); // Retorna se a lista está vazia
void freeList(FileList* list); // Desaloca a lista

// File Handling
bool addFilesIteration(FileList* list, const char* path); // Itera sobre os arquivos de um diretório e os insere na lista
void printFilesNames(FileList* list); // Imprime os nomes dos arquivos da lista

#endif
