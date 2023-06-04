# Estudo de Caso - Versionador Pit

* Repositório destinado ao Estudo de Caso: Versionador de Arquivos.

---
* Esse trabalho terá base no funcionamento do Git.

* Boa parte do que foi aplicado aqui foi fruto dos ensinamentos do Professor Nilson e de um canal no youtube chamado ***Portfolio Courses*** ([Link para o canal](https://www.youtube.com/@PortfolioCourses)), que instruiu a criação de diretorios e tratamentos de erros.

---
* ***Database***
> Foi escolhido o tipo de arquivo .txt para poder servir como banco de dados para adicionar as snapshots, alterações, branches(feature futura) e etc. ...
---

* Foi utilizada as seguintes bibliotecas:
  * `stdio.h` [Link para a documentação!]()
  * `stdlib.h` [Link para a documentação!]()
  * `string.h` para tratativas de *strings*. [Link para a documentação!](), [Error Codes](https://www.gnu.org/software/libc/manual/html_node/Error-Codes.html)
  * `errno.h` para o tratamento de erros. [Link para a documentação!]()
  * `sys/stat.h` para a criação de pastas. (*.versionador*, *snapshots*, *logs*). [Link para a documentação!](https://pubs.opengroup.org/onlinepubs/7908799/xsh/sysstat.h.html)

---
### ***v1.0.0***

*Versão alpha do projeto*

Nessa versão o Versionador terá 4 funções basicas sendo elas:

* `versionador.exe iniciar`: será a função responsável por poder criar todos os arquivos necessários para começar a acompanhar os arquivos da pasta em que foi executado. [`git init`]
* `versionador.exe adiciona <arquivo_1>, <arquivo_2>, ..., <arquivo_n>`: Ao executar esse comando, o usuário irá selecionar os arquivos que serão adicionados a proxíma snapshot de versão. [`git add 'files'`]
* `versionador.exe registra “Texto”`: Ao executar esse comando, o texto digitdo será o nome da snapshot dos arquivos adicionados anteriormente no processo da função acima e adicionar essa snapshot ao banco de dados de versões. [`git commit 'text'`]
* `versionador.exe log`: Ao executar esse comando, o programa deverá listar todos os snapshots já feitos que se encontram no banco de dados, com os respectivos textos. [`git log`]
* `versionador.exe log --conteudo`: Ao executar esse comando,


## Funções

***`errno.h`***:
> * `perror("Error")`: detalhará o erro que está acontecendo na função.
