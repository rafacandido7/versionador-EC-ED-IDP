#ifndef VERSIONADOR_H_
#define VERSIONADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/versionador.h"
#include "../inc/helpers.h"
#include "../inc/list.h"
#include "../inc/fileHandler.h"

void start(int argc, const char* argv[]);
void options(int argc, const char* argv[]);
void inciar(void);
void adiciona(int argc, const char* argv[]);
void registrar(const char* text);
void log(void);
void mostrar(void);
void mudar(void);

#endif
