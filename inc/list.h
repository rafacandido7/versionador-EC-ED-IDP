#ifndef LIST_FILE_H
#define LIST_FILE_H

#include <stdlib.h>
#include <stdio.h>
#include "../inc/list.h"
#include "../inc/helpers.h"

typedef struct _listFileNode ListFileNode;
typedef struct _listFile ListFile;

ListFile* createList(void);
int push(ListFile* list, FILE* file); // Insere e retorna na última posição
int unshift(ListFile* list, FILE* file); // Insere e retorna o elemento na primeira posição
FILE* pop(ListFile* list); // Remove e retorna o último elemento
FILE* shift(ListFile* list); // Remove e retorna o elemento na primeira posição
void getLastElement(ListFileNode* node); // Procura pelo último elemento da lista
int length(ListFile* list); // Retorna o tamanho da lista
int isEmpty(ListFile* list);
void freeList(ListFile* list); // Desaloca a lista

#endif /* LIST_FILE_H */
