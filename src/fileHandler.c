#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include "../inc/helpers.h"
#include "../inc/fileHandler.h"

bool copyFilesToSnapshotTemp(int argc, const char* argv[]) {
  for (int i = 2; i < argc; i++) {
    if (verifyFile(argv[i])) {
      copyFile(argv[i], ".versionador/snapshots_temp");
    } else {
      print("Arquivo não encontrado: ", "error");
      print(argv[i], "error");
      return false;
    }
  }
  return true;
};

void copyFile(const char* fromPath, const char* destinyPath) {
  if (!verifyFile(fromPath)) {
    print("Erro ao encontar o arquivo", "error");
    print(fromPath, "error");
    return;
  }

  FILE* file = fopen(fromPath, "r");

  char filePath[100];
  snprintf(filePath, sizeof(filePath), "%s/%s", destinyPath, fromPath);

  FILE* destinyFile = fopen(filePath, "w");
  char buffer;

  if (!verifyFile(destinyPath)) {
    print("Erro ao criar o arquivo", "error");
    print(destinyPath, "error");
    return;
  }

  while ((buffer = fgetc(file)) != EOF) {
    fputc(buffer, destinyFile);
  }

  fclose(file);
  fclose(destinyFile);
  return;
};

void addTextInTxtFile(const char* path, const char* text) {
  // print(path, "blue");
  if (!verifyFile(path)) {
    print("Erro editar o arquivo: ", "error");
    print(path, "error");
    return;
  }

  FILE* file = fopen(path, "a");

  // Checks the file size
  fseek(file, 0, SEEK_END);
  long int fileSize = ftell(file);

  // Verify if the file is empty
  if (fileSize == 0) {
    fprintf(file, text);
  } else {
    // Apoints to the beggining of the last line
    fseek(file, -1, SEEK_END);

    // Verify if the last line ends with \n
    int lastChar = fgetc(file);
    if (lastChar != '\n') {
      fprintf(file, "\n");
    }

    fprintf(file, text);
  }

  fclose(file);
  return;
};

void addSnapshotTextInLog(const char* snapshotName, const char* hash) {
  char commitName[100];
  snprintf(commitName, sizeof(commitName), "%s %s", hash, snapshotName);

  addTextInTxtFile(".versionador/logs/log.txt", commitName);
  return;
};

void addSnapshotTempFilesInList(FileList* list) {
  DIR* dir;
  struct dirent* entity;
  char* path = ".versionador/snapshots_temp";
  dir = opendir(path);

  if (!verifyDirectory(path)) {
    print("Erro ao abrir o diretório: ", "error");
    print(path, "error");
    return;
  }

  while ((entity = readdir(dir)) != NULL) {
    char filePath[100];
    snprintf(filePath, sizeof(filePath), "%s/%s", path, entity->d_name);
    FILE* file = fopen(filePath, "r");

    if (!verifyFile(filePath)) {
      print("Erro ao abrir o arquivo: ", "error");
      print(filePath, "error");
      return;
    }

    push(list, file, entity->d_name);
  }

  closedir(dir);
  return;
};

void addFilesIntoSnapshotFolder(FileList* list, const char* hash) {
  char snapshotPath[100];
  snprintf(snapshotPath, sizeof(snapshotPath), ".versionador/snapshots/%s", hash);

  bool resultAddFiles = addFilesIteration(list, snapshotPath);
  if (resultAddFiles) {
    return;
  } else {
    print("Erro ao adicionar os arquivos na pasta: ", "error");
    print(snapshotPath, "error");
    return;
  };
}
