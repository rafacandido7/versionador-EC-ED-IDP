#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include "../inc/versionador.h"
#include "../inc/helpers.h"
#include "../inc/list.h"
#include "../inc/fileHandler.h"

void copyFilesToSnapshotTemp(int argc, const char* argv[]) {
  for (int i = 2; i < argc; i++) {
    if (verifyFile(argv[i])) {
      copyFile(argv[i], ".versionador/snapshots_temp");
    } else {
      print("Arquivo não encontrado: ", "error");
      print(argv[i], "error");
    }
  }
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

