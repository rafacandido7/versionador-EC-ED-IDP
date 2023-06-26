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
void insertNode(FileList* list, const char *fileName, FILE* file);
void cleanList(FileList* list);
void printList(FileList* list);
void addFilesToList(FileList *list, const char** files, int quantity);
void createFilesInSnapshotFolder(FileList* list, const char* path);

bool isEmpty(FileList* list); // Retorna se a lista está vazia
void createTxt(const char *path, FileListNode *node);

#endif
