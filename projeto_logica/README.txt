================================================================================
         PROJETO FINAL - LOGICA DE PROGRAMACAO E ALGORITMOS (C)
================================================================================

1. TEMA DO PROJETO
--------------------------------------------------------------------------------
Sistema de Gerenciamento de Clube e Campeonato de Xadrez (com Tabuleiro
Interativo de Xadrez integrado no console).

O sistema gerencia o cadastro completo de enxadristas do clube em memoria
alocada dinamicamente (malloc/realloc/free), persiste todos os registros no
arquivo "dados.txt", emite relatorios estatisticos formatados na tela e em
"relatorio.txt", e ainda conta com um modulo interativo para disputar partidas
de xadrez no proprio terminal.


2. INTEGRANTES DA EQUIPE E DIVISAO DOS MODULOS (ROTEIRO DO VIDEO DE 5 MIN)
--------------------------------------------------------------------------------
* Integrante 1 (0:00 a 1:00): Eduardo [Preencher Sobrenome]
  - Modulo 1: Apresentacao do tema, definicao da struct Jogador (5 campos),
    alocacao dinamica inicial (malloc), expansao (realloc), liberacao (free)
    e laco principal do menu (do-while / switch na funcao main).

* Integrante 2 (1:00 a 2:00): [Nome do Integrante 2]
  - Modulo 2: Funcoes de Cadastro (cadastrarJogador) com validacao de codigo
    repetido e crescimento automatico com realloc, e Listagem em tabela
    alinhada (listarJogadores).

* Integrante 3 (2:00 a 3:00): [Nome do Integrante 3]
  - Modulo 3: Funcoes de Busca por Codigo e por Nome (buscarJogador),
    Alteracao de registro existente (alterarJogador) e Exclusao com pedido
    de confirmacao S/N (excluirJogador).

* Integrante 4 (3:00 a 4:00): [Nome do Integrante 4]
  - Modulo 4: Persistencia em arquivo texto "dados.txt" separado por ';'
    (carregarDadosArquivo no modo "r" ao abrir o programa e salvarDadosArquivo
    no modo "w" apos alteracoes e ao sair).

* Integrante 5 (4:00 a 5:00): [Nome do Integrante 5]
  - Modulo 5: Geracao do Relatorio Estatistico na tela e no arquivo
    "relatorio.txt" (gerarRelatorio - total de registros, soma/media e
    maior/menor rating) e validacoes de entrada (lerInteiroValido /
    lerFloatValido).


3. COMO COMPILAR E EXECUTAR
--------------------------------------------------------------------------------
Pre-requisito: Compilador GCC (MinGW-w64 / MSYS2) no Windows.

No terminal (PowerShell ou CMD), dentro da pasta "projeto_logica", execute:

  gcc -Wall -Wextra xadrez.c -o xadrez.exe

Para executar o programa:

  .\xadrez.exe


4. FORMATO DO ARQUIVO DE DADOS (dados.txt)
--------------------------------------------------------------------------------
O arquivo "dados.txt" e um arquivo de texto puro onde cada linha representa um
jogador cadastrado, com os 5 campos separados por ponto-e-virgula (;):

  codigo;nome;categoria;vitorias;rating

Tipos dos campos na struct Jogador:
  - codigo    (int)    : Codigo unico do jogador (inteiro positivo)
  - nome      (char[]) : Nome do jogador (ate 49 caracteres)
  - categoria (char[]) : Categoria no clube (Iniciante, Intermediario, Avancado, Mestre)
  - vitorias  (int)    : Numero de vitorias acumuladas (inteiro >= 0)
  - rating    (float)  : Pontuacao/Rating do jogador (real >= 0.0)

Exemplo de linha no arquivo "dados.txt":
  101;Eduardo Almeida;Mestre;28;2150.50


5. LINK DO VIDEO DE APRESENTACAO (ATE 5 MINUTOS)
--------------------------------------------------------------------------------
Link do video (YouTube Nao Listado / Google Drive):
[INSERIR LINK DO VIDEO AQUI ANTES DE ENVIAR NO AVA]
================================================================================

