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

int push(FileList* list, FILE* file, const char* fileName) {
  FileListNode* node = (FileListNode*)malloc(sizeof(FileListNode));
  printf("%s", fileName);

  if (node == NULL) {
    print("Erro de alocação de memória!", 'error');
    return -1;
  }

  Archive* archive = (Archive*)malloc(sizeof(Archive));
  if (archive == NULL) {
    print("Erro de alocação de memória!", 'error');
    return -1;
  }

  archive->fileName = fileName;
  archive->file = file;

  node->info = archive;
  node->next = NULL;

  if (isEmpty(list)) {
    list->first = node;
  } else {
    FileListNode* aux = list->first;

    while (aux->next != NULL) {
      aux = aux->next;
    }

    aux->next = node;
  }

  list->length++;
  return length(list);
}

int unshift(FileList* list, FILE* file, const char* fileName) {
  FileListNode* node = (FileListNode*)malloc(sizeof(FileListNode));

  if (node == NULL) {
    print("Erro de alocação de memória!", 'error');
  }

  Archive* archive = (Archive*)malloc(sizeof(Archive));
  archive->fileName = fileName;
  archive->file = file;

  node->info = archive;
  node->next = list->first;

  list->first = node;

  list->length++;

  return length(list);
}

Archive* pop(FileList* list) {
  if(isEmpty(list)) {
    return NULL;
  }

  FileListNode* aux = list->first;
  FileListNode* prev = NULL;

  // Go to the last element
  while (aux->next != NULL) {
    prev = aux;
    aux = aux->next;
  }

  // Verifiy if node is the first to be removed
  if (prev == NULL) {
    list->first = NULL;
  } else {
    prev->next = NULL;
  }


  FILE* removed = aux->info->file;
  free(aux);

  // Verify if prev node is not null, if its, free it
  if (prev != NULL) {
    free(prev);
  }

  // Decrement list length
  list->length--;

  return removed;
}

Archive* shift(FileList* list) {
  if (isEmpty(list)) {
    return NULL;
  }

  // Create aux node to store the first node
  FileListNode* aux = list->first;
  // Set the first node to the next node
  list->first = aux->next;

  FILE* removed = aux->info->file;
  free(aux);

  // Decrement list length
  list->length--;

  return removed;
}

FileListNode* getLastElement(FileListNode* node) {
  while (node->next != NULL) {
    node = node->next;
  }
  return node;
}

int length(FileList* list) {
  return list->length;
}

bool isEmpty(FileList* list) {
  return list->first == NULL ? true : false;
}

void freeList(FileList* list) {
  while (!isEmpty(list)) {
    FILE* file = pop(list)->file;
    if (file != NULL) {
      fclose(file);
    }
  }

  free(list);
}

bool addFilesIteration(FileList* list, const char* path) {
  int fileLength = length(list);
  FileListNode* node = list->first;

  for (int i = 0; i < fileLength; i++) {
    char filePath[100];
    const char* fileName = node->info->fileName;

    // Creates the file path
    snprintf(filePath, sizeof(filePath), "%s/%s", path, fileName);
    FILE* file = fopen(filePath, "w");

    if (!verifyFile(filePath)) {
      print("Erro ao abrir o arquivo: ", "error");
      print(filePath, "error");
      return false;
    }

    char buffer;
    FILE* fileToCopy = node->info->file;

    // Copy the file
    while ((buffer = fgetc(fileToCopy)) != EOF) {
      fputc(buffer, file);
    }

    fclose(file);
    node = node->next;
  }

  printFilesNames(list);

  if (list->length > 0) {
    return true;
  } else {
    return false;
  }
}

void printFilesNames(FileList* list) {
  FileListNode* node = list->first;

  while (node != NULL) {
    print(node->info->fileName, 'info');
    node = node->next;
  }
}
