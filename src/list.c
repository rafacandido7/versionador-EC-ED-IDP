#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "../inc/helpers.h"
#include "../inc/list.h"

struct _archive {
  const char* fileName;
  FILE* file;
};

struct _fileListNode {
  Archive *info;
  FileListNode *next;
};

struct _fileList {
  FileListNode *first;
  int length;
};

FileList* createList(void) {
  FileList* list = (FileList*)malloc(sizeof(FileList));

  if (list == NULL) {
    return NULL;
  }

  list->first = NULL;
  list->length = 0;

  return list;
}

void insertNode(FileList* list, const char *fileName, FILE* file) {
  Archive* archive = (Archive*)malloc(sizeof(Archive));
  archive->fileName = fileName;
  archive->file = fopen(fileName, "r");

  FileListNode* node = (FileListNode*)malloc(sizeof(FileListNode));
  node->info = archive;
  node->next = NULL;

  if (isEmpty(list)) {
    list->first = node;
  } else {
    node->next = list->first;
    list->first = node;
  }

  list->length++;
}

void cleanList(FileList* list) {
  FileListNode *current = list->first;
  while (current != NULL) {
    FileListNode *tmp = current;
    current = current->next;

    fclose(tmp->info->file);

    free(tmp->info);

    free(tmp);
  }

  list->first = NULL;
  list->length = 0;
}

void printList(FileList* list) {
  FileListNode *current = list->first;
  while (current != NULL) {
    printf("File Name: %s\n", current->info->fileName);
    printTxtContent(current->info->file);
    printf("----------\n");
    current = current->next;
  }
}

void addFilesToList(FileList *list, const char** files, int quantity) {
  for (int i = 0; i < quantity; i++) {
    FILE* file = fopen(files[i], "r");
    if (file == NULL) {
      print("Erro ao abrir arquivo!", 'error');
      return;
    }

    insertNode(list, files[i], file);
  }
}

bool isEmpty(FileList* list) {
  return list->first == NULL ? true : false;
}

void createTxt(const char *path, FileListNode *node) {
  // Creates the file path
  char filePath[100];
  strcpy(filePath, path);
  strcat(filePath, "/");
  strcat(filePath, node->info->fileName);

  // Create the file
  FILE* sourceFile = node->info->file;
  if (sourceFile == NULL) {
    print("Erro ao acessar o arquivo de origem.", "error");
    return;
  }

  // Cria o arquivo de destino
  FILE* snapshotFile = fopen(filePath, "w");
  if (snapshotFile == NULL) {
    printf("Erro ao criar o arquivo de destino.\n");
    return;
  }

  // Copy the content of the source file to the snapshot file
  char buffer;
  while ((buffer = fgetc(sourceFile)) != EOF) {
    fputc(buffer, snapshotFile);
  }

  fclose(snapshotFile);
}

void createFilesInSnapshotFolder(FileList* list, const char* path) {
  FileListNode *current = list->first;
  while (current != NULL) {
    createTxt(path, current);
    current = current->next;
  }
}
