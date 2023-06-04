#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/versionador.h"
#include "../inc/list.h"
#include "../inc/helpers.h"

void start(int argc, const char* argv[]) {
  ListFile* list = createList();
  options(argc, argv, list);
}

void options(int argc, const char* argv[], ListFile* list) {
    if (strcmp(argv[1], "iniciar") == 0) {
        inciar();
    }
    // if (strcmp(argv[1], "adiciona") == 0) {
    //     // git add . (lista de arquivos)
    // }
    // if (strcmp(argv[1], "registra") == 0) {
    //     // verificar fila de arquivos, se tiver, se não exibir alerta
    //     if (length(list) > 0) {
    //         if (argv[2]) {
    //             // git commit -m "mensagem"
    //         }
    //     } else {
    //         print("Não há arquivos para serem commitados!", "error");
    //     }
    //     // verificar se tem arquivos pendentes para commitar, se sim inserir commit
    // }
    // if (strcmp(argv[1], "log") == 0) {
    //     //printa os snapshots(commits) já feitos
    //     if (argv[2] && strcmp(argv[2], "--conteudo") == 0) {
    //         // printar log
    //     }
    // }
    // if (strcmp(argv[1], "mostrar") == 0) {
    //     if (argv[2] == NULL) {
    //         // retornar erro ao usar a função
    //     }
    //     const char* commit = argv[2];
    // }
    // if (strcmp(argv[1], "mudar") == 0) {
    //     // verificar se não já está na atual
    //     if (argv[2] && strcmp(argv[2], "--atual") == 0) {
    //     }
    // }
    // if (strcmp(argv[1], "--ajuda") == 0) {
    //     // printar as funções já existentes e disponíveis
    // }
}

void inciar() {
  const char* folderName = ".versionador";
  if (verifyDirectory(folderName)) {
    print("O versionador já foi inicializado!", "error");
    print("Para mais informções digite 'versionador.exe status'!\n", "blue");
    return;
  } else {
    print("Inicializando o versionador...", "green");

    // Create the repository
    createRepo(folderName);

    // Verify if the Versionador was created
    if (verifyDirectory(folderName)) {
      print("Versionador inicializado com sucesso!", "success");
    } else {
      print("Erro ao inicializar o versionador!", "error");
    }
  }
}

