#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <stdbool.h>
#include "helpers.h"
#include "list.h"

bool copyFilesToSnapshotTemp(int argc, const char* argv[]); // Copia os arquivos para a pasta .versionador/snapshots_temp para preparar para a snapshot
void copyFile(const char* fromPath, const char* destinyPath); // Copia o arquivo de um caminho para outro
void addTextInTxtFile(const char* path, const char* text); // Adiciona texto em um arquivo .txt
void addSnapshotTextInLog (const char* snapshotName, const char* hash); // Adiciona o nome da snapshot no arquivo .versionador/logs/log.txt
void addSnapshotTempFilesInList(FileList* list); // Adiciona os arquivos da pasta .versionador/snapshots_temp na lista de arquivos
void addFilesIntoSnapshotFolder(FileList* list, const char* hash); // Adiciona os arquivos da lista na pasta correspondente ao snapshot com o nome do hash
void addFileToList(FileList* list);
#endif
