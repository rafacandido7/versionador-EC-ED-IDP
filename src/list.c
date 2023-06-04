#include <stdlib.h>
#include <stdio.h>
#include "../inc/list.h"
#include "../inc/helpers.h"

struct _listFileNode {
  FILE *info;
  ListFileNode *next;
};

struct _listFile {
  ListFileNode *first;
  int length;
};

ListFile* createList(void) {
  ListFile* list = (ListFile*)malloc(sizeof(ListFile));

  verifyAllocation(list);

  list->first = NULL;
  list->length = 0;

  return list;
}

int push(ListFile* list, FILE* file) {
  ListFileNode* node = (ListFileNode*)malloc(sizeof(ListFileNode));

  verifyAllocation(node);

  node->info = file;
  node->next = NULL;

  if (isEmpty(list)) {
    list->first = node;
  } else {
    ListFileNode* aux = list->first;

    while (aux->next != NULL) {
      aux = aux->next;
    }

    aux->next = node;
  }

  list->length++;
  return length(list);
}

int unshift(ListFile* list, FILE* file) {
  ListFileNode* node = (ListFileNode*)malloc(sizeof(ListFileNode));

  verifyAllocation(node);

  node->info = file;
  node->next = list->first;

  list->first = node;

  list->length++;

  return length(list);
}

FILE* pop(ListFile* list) {
  if(isEmpty(list)) {
    return NULL;
  }

  ListFileNode* aux = list->first;
  ListFileNode* prev = NULL;

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


  FILE* removed = aux->info;
  free(aux);

  // Verify if prev node is not null, if its, free it
  if (prev != NULL) {
    free(prev);
  }

  // Decrement list length
  list->length--;

  return removed;
}

FILE* shift(ListFile* list) {
  if (isEmpty(list)) {
    return NULL;
  }

  // Create aux node to store the first node
  ListFileNode* aux = list->first;
  // Set the first node to the next node
  list->first = aux->next;

  FILE* removed = aux->info;
  free(aux);

  // Decrement list length
  list->length--;

  return removed;
}

void getLastElement(ListFileNode* node) {
  while (node->next != NULL) {
    node = node->next;
  }
}

int length(ListFile* list) {
  return list->length;
}

int isEmpty(ListFile* list) {
  return (list->first == NULL);
}

void freeList(ListFile* list) {
  while (!isEmpty(list)) {
    FILE* file = pop(list);
    if (file != NULL) {
      fclose(file);
    }
  }

  free(list);
}
