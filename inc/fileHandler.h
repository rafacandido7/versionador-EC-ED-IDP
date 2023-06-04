#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <stdlib.h>
#include <stdio.h>
#include "../inc/versionador.h"
#include "../inc/helpers.h"
#include "../inc/list.h"
#include "../inc/fileHandler.h"

void copyFilesToSnapshotTemp(int argc, const char* argv[]); // Copia os arquivos para a pasta .versionador/snapshots_temp para preparar para a snapshot
void copyFile(const char* fromPath, const char* destinyPath); // Copia o arquivo de um caminho para outro

#endif
