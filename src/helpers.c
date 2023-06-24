#include "../inc/helpers.h"
#include "../inc/fileHandler.h"
#include "../inc/list.h"
#include <dirent.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

extern int errno;

#define RED "\x1B[31m"
#define GRN "\x1B[32m"
#define YEL "\x1B[33m"
#define BLU "\x1B[34m"
#define MAG "\x1B[35m"
#define CYN "\x1B[36m"
#define WHT "\x1B[37m"
#define RESET "\x1B[0m"

void print(char *text, char *color) {
  if (strIsEqual(color, "success")) {
    printf("%s%s%s\n", GRN, text, RESET);
  } else if (strIsEqual(color, "error")) {
    printf("%s%s%s\n", RED, text, RESET);
  } else if (strIsEqual(color, "red")) {
    printf("%s%s%s\n", RED, text, RESET);
  } else if (strIsEqual(color, "green")) {
    printf("%s%s%s\n", GRN, text, RESET);
  } else if (strIsEqual(color, "yellow")) {
    printf("%s%s%s\n", YEL, text, RESET);
  } else if (strIsEqual(color, "blue")) {
    printf("%s%s%s\n", BLU, text, RESET);
  } else if (strIsEqual(color, "magenta")) {
    printf("%s%s%s\n", MAG, text, RESET);
  } else if (strIsEqual(color, "cyan")) {
    printf("%s%s%s\n", CYN, text, RESET);
  } else if (strIsEqual(color, "white")) {
    printf("%s%s%s\n", WHT, text, RESET);
  } else {
    printf("%s\n", text);
  }
  printf("\n");
  return;
}

// Verifies
void verifyAllocation(void *pointer) {
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
  DIR *folder;
  struct dirent *entry;
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

bool strIsEqual(const char *str1, const char *str2) {
  bool res = strcmp(str1, str2) == 0 ? true : false;
  return res;
}

bool verifyVersionadorFolder(void) {
  bool res = verifyDirectory(".versionador") ? true : false;
  return res;
}
// Creates
void createFolder(char *folderName, char *newFolderName) {
  char completePath[100];
  snprintf(completePath, sizeof(completePath), "%s/%s", folderName,
           newFolderName);

  mkdir(completePath, 0777);
  return;
}

void createLogFolder(const char *folderPath) {
  const char *folderName = "logs";
  createFolder(folderPath, folderName);

  char newPath[100];
  snprintf(newPath, sizeof(newPath), "%s/%s", folderPath, folderName);

  createTxtFile(newPath, "log.txt", "Versionador Log");

  snprintf(newPath, sizeof(newPath), "%s/%s", newPath, "log.txt");
  addTextInTxtFile(".versionador/logs/log.txt", "Snapshots Criadas:");

  return;
}

void createTxtFile(const char *path, char *fileName, char *text) {
  char newPath[100];
  snprintf(newPath, sizeof(newPath), "%s/%s", path, fileName);

  FILE *file = fopen(newPath, "w");

  if (!file) {
    print("Erro ao criar arquivo!", "error");
  }

  fprintf(file, "%s", text);
  fclose(file);
  return;
}

void createRepo(const char *folderName) {
  // Create the Versionador Folder
  mkdir(folderName, 0777);
  createTxtFile(folderName, "versionador.txt", "Projeto Versionador v0.0.2");

  // Create the Versionador Folders
  createFolder(folderName, "snapshots");
  createFolder(folderName, "snapshots_temp");
  createFolder(folderName, "temp");
  createLogFolder(folderName);
}

void createSnapshot(const char *text) {
  char *hash = generateHash(16);
  char *path = ".versionador/snapshots";

  // Create snapshot folder with hash name
  // createFolder(path, hash);

  // Create File List
  // FileList *list = createList();

  // Add snapshots_temp files into a File List
  // addSnapshotTempFilesInList(list);

  // Copy files from the File List into the snapshot folder
  // addFilesIntoSnapshotFolder(list, hash);

  // Clear File List
  // freeList(list);

  // Clear snapshot_temp folder
  clearFolder(".versionador/snapshots_temp"); // working

  // Add commit into the log.txt file
  addSnapshotTextInLog(text, hash);
  return;
};

// Generates
char generateRandomChar(void) {
  const char charr[] =
      "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz!@#$&*_+?";

  int size = sizeof(charr) - 1;

  int i = rand() % size;

  return charr[i];
}

char* generateHash(int length) {
  char hash[100];
  verifyAllocation(hash);

  for (int i = 0; i < length; i++) {
    hash[i] = generateRandomChar();
  }
  hash[length] = '\0';

  return hash;
}

// Gets
char *getFilesInFolder(const char *path) {}

const char* getTxtContentFile(const char* path) {
  FILE* file = fopen(path, "r");

  if (!verifyFile(path)) {
    print("Erro abrir o arquivo: ", "error");
    print(path, "error");
    return '\0';
  }

  // Obtém o tamanho do arquivo
  fseek(file, 0, SEEK_END);
  long file_size = ftell(file);
  fseek(file, 0, SEEK_SET);

  // Aloca memória para armazenar o conteúdo do arquivo
  char* content = (char*)malloc((file_size + 1) * sizeof(char));
  if (content == NULL) {
    printf("Erro de alocação de memória.\n");
    fclose(file);
    return NULL;
  }

  // Lê o conteúdo do arquivo
  size_t bytes_read = fread(content, sizeof(char), file_size, file);
  if (bytes_read != file_size) {
    printf("Erro ao ler o arquivo: %s\n", path);
    fclose(file);
    free(content);
    return NULL;
  }

  // Termina a string com um caractere nulo
  content[file_size] = '\0';

  fclose(file);
  return content;
}

char** getFoldersInDirectory(const char* directoryPath, int* numFolders) {
  DIR* dir = opendir(directoryPath);
  if (dir == NULL) {
    printf("Não foi possível abrir o diretório: %s\n", directoryPath);
    *numFolders = 0;
    return NULL;
  }

  struct dirent* entry;
  char** folders = NULL;
  int count = 0;

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_DIR && entry->d_name[0] != '.') {
      folders = realloc(folders, (count + 1) * sizeof(char*));
      folders[count] = strdup(entry->d_name);
      count++;
    }
  }

  closedir(dir);
  *numFolders = count;
  return folders;
}

// Versionador helpers
bool addFiles(int argc, const char *argv[]) {
  bool process = copyFilesToSnapshotTemp(argc, argv);
  return process;
};

// Test Functions
void printArgv(int argc, const char *argv[]) {
  print("Argumentos passados: ", "blue");
  print("______________________________", "blue");
  for (int i = 0; i < argc; i++) {
    printf("%d: %s\n", i, argv[i]);
  }
  print("______________________________", "blue");
  return;
};

// Deletes
bool clearFolder(const char *folderPath) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(folderPath);
  if (dir == NULL) {
    printf("Erro ao abrir a pasta.\n");
    return false;
  }

  chdir(folderPath);

  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG) {
      remove(entry->d_name);
    }
  }

  chdir("..");
  closedir(dir);
  return true;
};

// Show

void showLog(void) {
  char *path = ".versionador/logs/log.txt";
  char *content = getTxtContentFile(path);

  if (content != NULL) {
    print(content, "blue");
    free(content);
  }

  return;
}

void showLogsContent(void) {
  int foldersQuantity;
  char** foldersNames = getFoldersInDirectory(".versionador/snapshots", &foldersQuantity);

  if (foldersQuantity == 0) {
    print("Não há snapshots para mostrar.", "error");
    return;
  }

  if (foldersNames != NULL) {
    print("Snapshots", "magenta");
    print("--------------------------------", "magenta");
    for (int i = 0; i < foldersQuantity; i++) {
      char title[256];
      strcpy(title, "Conteúdo da snapshot: ");
      strcat(title, foldersNames[i]);
      print(title, "green");

      char path[] = ".versionador/snapshots/";
      char folderPath[256];

      strcpy(folderPath, path);
      strcat(folderPath, foldersNames[i]);

      printTxtFilesContent(folderPath);

      print("--------------------------------", "green");
    }
    freeFolders(foldersNames, foldersQuantity);
  }

  //Mostrar o conteudo de cada pasta individualmente

}

void showSnapshotContent(const char* snapshotName) {
  char path[] = ".versionador/snapshots/";
  char folderPath[256];

  strcpy(folderPath, path);
  strcat(folderPath, snapshotName);

  char title[256];
  strcpy(title, "Conteúdo da snapshot: ");
  strcat(title, snapshotName);

  print(title, "green");
  print("--------------------------------", "green");

  printTxtFilesContent(folderPath);

  print("--------------------------------", "green");
}
// Frees
void freeFolders(char** folders, int numFolders) {
  for (int i = 0; i < numFolders; i++) {
    free(folders[i]);
  }
  free(folders);
}

// Prints
void printTxtFilesContent(const char* directoryPath) {
  DIR* dir = opendir(directoryPath);
  if (dir == NULL) {
    print("Não foi possível abrir o diretório:", "error");
    print(directoryPath, "error");
    return;
  }

  struct dirent* entry;
  while ((entry = readdir(dir)) != NULL) {
    if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt") != NULL) {
      char filePath[256];
      snprintf(filePath, sizeof(filePath), "%s/%s", directoryPath, entry->d_name);

      FILE* file = fopen(filePath, "r");
      if (file != NULL) {
        printf("Conteúdo de %s:\n", entry->d_name);
        char line[256];
        while (fgets(line, sizeof(line), file) != NULL) {
          printf("%s", line);
        }
        printf("\n");
        fclose(file);
      }
    }
  }

  closedir(dir);
}
