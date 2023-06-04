#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../inc/versionador.h"
#include "../inc/helpers.h"
#include "../inc/list.h"
#include "../inc/fileHandler.h"

void start(int argc, const char* argv[]) {
  print("versionador.exe v1.0.0", "blue");
  // printArgv(argc, argv);
  options(argc, argv);
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

void adiciona(int argc, const char* argv[]) {
  if (argc < 3) {
    print("É necessário informar o(s) nome(s) do arquivo(s)!", "error");
    return;
  }

  if (argc >= 3) {
    addFiles(argc, argv);
    print("Arquivo(s) adicionado(s) com sucesso!", "success");
    // print("Para registrar as mudanças, digite './versionador registra <Texto>'!\n", "magenta");
    return;
  }
}

void registrar(const char* text) {
  if (!verifyDirectory(".versionador/snapshots_temp")) {
    print("O versionador não foi inicializado!", "error");
    print("Para adicionar os arquivos, primeiro deve-se inicializar o versionador com 'versionador iniciar'!\n", "blue");
    return;
  }
};

void log(void);
void mostrar(void);
void mudar(void);

void options(int argc, const char* argv[]) {
    if (strIsEqual(argv[1], "iniciar")) {
      inciar();
      return;
    }

    if (verifyVersionadorFolder()) {
      if (strIsEqual(argv[1], "adiciona")) {
      adiciona(argc, argv);
      return;
      }

      // if (strIsEqual(argv[1], "registra")) {
      //   registrar(argv[2]);
      //     // verificar fila de arquivos, se tiver, se não exibir alerta
      //     if (verifyDirectory(".versionador/snapshots_temp")) {
      //         if (argv[2]) {

      //         }
      //     } else {
      //         print("Não há arquivos para serem registrados!", "error");
      //     }
      // }
    // if (strIsEqual(argv[1], "log")) {
    //     //printa os snapshots(commits) já feitos
    //     if (argv[2] && strIsEqual(argv[2], "--conteudo")) {
    //         // printar log
    //     }
    // }
    // if (strIsEqual(argv[1], "mostrar")) {
    //     if (argv[2] == NULL) {
    //         // retornar erro ao usar a função
    //     }
    //     const char* commit = argv[2];
    // }
    // if (strIsEqual(argv[1], "mudar")) {
    //     // verificar se não já está na atual
    //     if (argv[2] && strIsEqual(argv[2], "--atual")) {
    //     }
    // }
    // if (strIsEqual(argv[1], "--ajuda")) {
    //     // printar as funções já existentes e disponíveis
    // }
      print("Comando não encontrado!", "error");
      return;
    }


    print("Para executar qualquer função do versionador, primeiro deve-se inicializa-lo com './versionador iniciar'!", "error");
    return;
}
