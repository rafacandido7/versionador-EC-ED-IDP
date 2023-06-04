#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>
#include <dirent.h>
#include "../inc/helpers.h"

extern int errno;

#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

void print(char* text, char* color) {
  if (strcmp(color, "success") == 0) {
    printf("%s%s%s\n", GRN, text, RESET);
  } else if (strcmp(color, "error") == 0) {
    printf("%s%s%s\n", RED, text, RESET);
  } else if (strcmp(color, "red") == 0) {
    printf("%s%s%s\n", RED, text, RESET);
  } else if (strcmp(color, "green") == 0) {
    printf("%s%s%s\n", GRN, text, RESET);
  } else if (strcmp(color, "yellow") == 0) {
    printf("%s%s%s\n", YEL, text, RESET);
  } else if (strcmp(color, "blue") == 0) {
    printf("%s%s%s\n", BLU, text, RESET);
  } else if (strcmp(color, "magenta") == 0) {
    printf("%s%s%s\n", MAG, text, RESET);
  } else if (strcmp(color, "cyan") == 0) {
    printf("%s%s%s\n", CYN, text, RESET);
  } else if (strcmp(color, "white") == 0) {
    printf("%s%s%s\n", WHT, text, RESET);
  } else {
    printf("%s\n", text);
  }
  return;
}

// Verifies

void verifyAllocation (void* pointer) {
  if (pointer == NULL) {
    print("Erro de alocação de memória!", RED);
  }
  return;
}

bool verifyFile(const char *fileName) {
  FILE* file = fopen(fileName, "r");

  if (file == NULL) {
    return false;
  } else {
    fclose(file);
    return true;
  }
}

bool verifyDirectory(const char *folderPath) {
  DIR* folder;
  struct dirent* entry;
  int folderFiles = 0;

  // Open the folder
  folder = opendir(folderPath);

  // Check if folder exists
  if (folder == NULL) {
    return false;
  }

  // Count the files in the folder
  while ((entry = readdir(folder)) != NULL) {
    if (entry->d_type == DT_REG) {
      folderFiles++;
    }
  }

  // Close the folder
  closedir(folder);

  // If there are no files in the folder, return false, else return true
  if (folderFiles == 0) {
    return false;
  } else {
    return true;
  }
}

// Creates

void createFolder (char* folderName, char* newFolderName) {
  char completePath[100];
  snprintf(completePath, sizeof(completePath), "%s/%s", folderName, newFolderName);

  mkdir(completePath, 0777);
  return;
}

void createLogFolder(const char* folderPath) {
  createFolder(folderPath, "/logs");

  char newPath[100];
  snprintf(newPath, sizeof(newPath), "%s/%s", folderPath, "logs");

  createTxtFile(newPath, "log.txt" ,"Log file created!");

  return;
}

void createTxtFile(const char* path, char* fileName, char* text) {
  char newPath[100];
  snprintf(newPath, sizeof(newPath), "%s/%s", path, fileName);

  FILE* file = fopen(newPath, "w");

  if (!file) {
    print("Erro ao criar arquivo!", "error");
  }

  fprintf(file, "%s", text);
  fclose(file);
  return;
}

void createRepo(const char* folderName) {
  // Create the Versionador Folder
    mkdir(folderName, 0777);
    createTxtFile(folderName, "versionador.txt" ,"Projeto Versionador v0.0.1");

    // Create the Versionador Folders
    createFolder(folderName, "snapshots");
    createFolder(folderName, "temp");
    createLogFolder(folderName);
}
// Generates

char generateRandomChar(void) {
  const char charr[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$&*_+?";

  int size = sizeof(charr) - 1;

  int i = rand() % size;

  return charr[i];
}

char* generateHash(int length) {
  char* hash = malloc((length + 1) * sizeof(char));
  verifyAllocation(hash);

  for (int i = 0; i < length; i++) {
    hash[i] = generateRandomChar();
  }
  hash[length] = '\0';

  return hash;
}

// Gests

char* getCompletePath(const char* beginPath, const char* endPath) {
  char completePath[100];
  snprintf(completePath, sizeof(completePath), "%s/%s", beginPath, endPath);

  return completePath;
}
