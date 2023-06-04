#ifndef VERSIONADOR_H_
#define VERSIONADOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/versionador.h"
#include "../inc/list.h"
#include "../inc/helpers.h"

void start(int argc, const char* argv[]);
void options(int argc, const char* argv[], ListFile* list);
void inciar(void);


#endif
