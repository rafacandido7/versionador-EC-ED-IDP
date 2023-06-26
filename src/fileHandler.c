#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <dirent.h>
#include <unistd.h>
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
  FILE* file = fopen(path, "a");

  if (!verifyFile(path)) {
    print("Erro editar o arquivo: ", "error");
    print(path, "error");
    return;
  }

  // Cheks the file size
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
  char commitName[256];
  strcpy(commitName, snapshotName);
  strcat(commitName, " - ");
  strcat(commitName, hash);

  addTextInTxtFile(".versionador/logs/log.txt", commitName);
  return;
  return;
};

void addSnapshotTempFilesInList(FileList* list) {
  const char directoryPath[] = ".versionador/snapshots_temp";

  // Get all files in actual directory
  int numFiles;
  char** files = getFilesInDirectory(directoryPath, &numFiles);

  // Copy all files to the list
  addFilesToList(list, files, numFiles);

};

void addFilesIntoSnapshotFolder(FileList* list, const char* hash) {
  // Get the files in the list and save then in snapshot folder
  const char snapshotsPath[] = ".versionador/snapshots/";
  char snapshotPath[256];

  strcpy(snapshotPath, snapshotsPath);
  strcat(snapshotPath, hash);

  createFilesInSnapshotFolder(list, snapshotPath);

  if (verifyDirectory(snapshotPath)) {
    return;
  } else {
    print("Erro ao adicionar os arquivos na pasta: ", "error");
    print(snapshotPath, "error");
    return;
  };
}

void copyFilesTo(const char** files, int length, const char *path) {
  if (files != NULL) {
    for (int i = 0; i < length; i++) {
      if (strcmp(files[i], "versionador") == 0) {
        continue;
      } else {
        copyFile(files[i], path);
      }
    }
  }
};

void copyFilesToTemp(const char** files, int length) {
  if (files != NULL) {
    for (int i = 0; i < length; i++) {
      if (strcmp(files[i], "versionador") == 0) {
        continue;
      } else {
        copyFile(files[i], ".versionador/temp");
      }
    }
  }
};

void copyFilesToWorkspace(const char** files, int length) {
  copyFilesTo(files, length, "./");
}

void moveFilesTo(const char* from, const char* to) {
  // Get all files in actual directory
  int numFiles;
  char** files = getFilesInDirectory(from, &numFiles);

  // copy to temp folder
  copyFilesTo(files, numFiles, to);
}

void moveFilesToTemp(const char *from) {
  const tempDirectoryPath = ".versionador/temp";
  moveFilesTo(from, tempDirectoryPath);
}

