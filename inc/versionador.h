#ifndef VERSIONADOR_H
#define VERSIONADOR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "helpers.h"

void start(int argc, const char* argv[]);
void options(int argc, const char* argv[]);
void inciar(void);
void adiciona(int argc, const char* argv[]);
void registrar(const char* text);
void log(void);
void mostrar(void);
void mudar(void);

#endif
