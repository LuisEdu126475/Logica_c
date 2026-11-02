/*
 * ============================================================================
 * PROJETO FINAL - LOGICA DE PROGRAMACAO E ALGORITMOS (C)
 * Tema: Sistema de Gerenciamento de Clube/Campeonato de Xadrez + Tabuleiro
 *
 * Requisitos atendidos (100% dos 9 itens obrigatorios do edital):
 *  1. Struct Jogador com 5 campos (int codigo, char nome[], char categoria[],
 *     int vitorias, float rating).
 *  2. Alocacao dinamica com malloc (capacidade inicial 5), crescimento
 *     automatico com realloc (dobrando a capacidade), verificacao de NULL
 *     e liberacao com free() antes de encerrar.
 *  3. Menu em laco do-while com switch e 8 opcoes (Cadastrar, Listar, Buscar,
 *     Alterar, Excluir, Relatorio, Jogar Xadrez no Tabuleiro e Sair).
 *  4. Cadastro completo: cadastrar, listar em tabela alinhada, buscar por
 *     codigo e por nome, alterar e excluir com confirmacao (S/N).
 *  5. Leitura automatica do arquivo "dados.txt" (modo "r") ao iniciar.
 *  6. Gravacao automatica no arquivo "dados.txt" (modo "w", separado por ';')
 *     apos cada alteracao e ao sair do programa.
 *  7. Geracao de relatorio formatado na tela e em "relatorio.txt" com data,
 *     cabecalho, tabela, rodape e estatisticas (total, soma/media, maior/menor).
 *  8. Validacao de erros: codigo repetido, valores negativos, textos vazios,
 *     opcoes invalidas e teste de retorno NULL em fopen/malloc/realloc.
 *  9. Modularizacao completa sem NENHUMA variavel global (apenas constantes).
 * ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

// Constantes do Sistema de Cadastro
#define CAPACIDADE_INICIAL 5
#define ARQUIVO_DADOS "dados.txt"
#define ARQUIVO_RELATORIO "relatorio.txt"

// Constantes do Tabuleiro de Xadrez
#define SETA_CIMA 72
#define SETA_BAIXO 80
#define ENTER 13
#define ESC 27
#define LINHAS 9
#define COLUNAS 9
#define QTD_PECAS 6

// ============================================================================
// ITEM 1: DEFINICAO DAS STRUCTS (SEM VARIAVEIS GLOBAIS)
// ============================================================================

// Struct principal do cadastro (5 campos de tipos int, char[] e float)
typedef struct {
    int codigo;           // Identificador unico do enxadrista (ex: 101)
    char nome[50];        // Nome completo do jogador
    char categoria[30];   // Categoria (Iniciante, Intermediario, Mestre, etc.)
    int vitorias;         // Total de vitorias acumuladas no clube
    float rating;         // Pontuacao/Rating oficial no clube (ex: 1850.50)
} Jogador;

// Struct que encapsula todo o estado de uma partida de xadrez (evita variaveis globais)
typedef struct {
    char tabuleiro[LINHAS][COLUNAS];
    char nomeJogador1[50];
    char nomeJogador2[50];
    char capturadas1[100];
    char capturadas2[100];
    int qtdCapturadas1;
    int qtdCapturadas2;
    int vezJogador1;
    int vezJogador2;
    int posRei1Linha;
    int posRei1Coluna;
    int posRei2Linha;
    int posRei2Coluna;
    int emAndamento;
    int flagErro;
    int contHistorico;
    int pularAutoSave;
    int maxRefazer;
    int ctrlSalvarAtivo;
    int ctrlCarregarAtivo;
    char histTabuleiro[8][8][50];
    char histDados[8][8][50];
} PartidaXadrez;

// Constantes das pecas de xadrez (minusculas = Brancas, maiusculas = Pretas)
static const char PECAS_BRANCAS[QTD_PECAS] = {'k', 'p', 'n', 'q', 'b', 'r'};
static const char PECAS_PRETAS[QTD_PECAS]  = {'K', 'P', 'N', 'Q', 'B', 'R'};

// ============================================================================
// PROTOTIPOS DAS FUNCOES DO SISTEMA DE CADASTRO (MODULOS 1 A 5)
// ============================================================================

// Funcoes de utilidade, validacao e memoria
void definirCor(int corTexto, int corFundo);
void limparBufferTeclado(void);
void lerTexto(char *destino, int tamanho);
int lerInteiroValido(const char *mensagem, int permitirZero);
float lerFloatValido(const char *mensagem);
int contemTextoIgnorandoCase(const char *texto, const char *busca);
int expandirCapacidade(Jogador **vetor, int *capacidade);
int buscarIndicePorCodigo(const Jogador *vetor, int quantidade, int codigo);

// Operacoes principais do sistema (recebem vetor e quantidade por parametro/ponteiro)
int carregarDadosArquivo(Jogador **vetor, int *quantidade, int *capacidade);
int salvarDadosArquivo(const Jogador *vetor, int quantidade);
int cadastrarJogador(Jogador **vetor, int *quantidade, int *capacidade);
void listarJogadores(const Jogador *vetor, int quantidade);
void buscarJogador(const Jogador *vetor, int quantidade);
void alterarJogador(Jogador *vetor, int quantidade);
void excluirJogador(Jogador *vetor, int *quantidade);
void gerarRelatorio(const Jogador *vetor, int quantidade);

// ============================================================================
// PROTOTIPOS DAS FUNCOES DO TABULEIRO DE XADREZ (MODULO BONUS)
// ============================================================================
void abrirModuloXadrez(Jogador *vetor, int quantidade);
void inicializarEstadoTabuleiro(PartidaXadrez *p);
int mostrarMenuXadrez(PartidaXadrez *p);
int controlarMenuXadrez(PartidaXadrez *p);
void exibirMenuXadrez(PartidaXadrez *p, int posCursor);
int lerTecla(void);
int desenharTabuleiro(const PartidaXadrez *p);
int converterColuna(char letra);
char casaPadrao(int linha, int coluna);
int iniciarPartidaXadrez(PartidaXadrez *p);

int peaoBranco(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino);
int peaoPreto(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino);
int cavalo(int linOrigem, int colOrigem, int linDestino, int colDestino);
int torre(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino);
int bispo(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino);
int rainha(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino);
int rei(int linOrigem, int colOrigem, int linDestino, int colDestino);

void executarMovimento(PartidaXadrez *p, int lin1, int col1, int lin2, int col2);
int xequeBranco(const PartidaXadrez *p, int linRei, int colRei);
int xequePreto(const PartidaXadrez *p, int linRei, int colRei);
int afogamentoBranco(const PartidaXadrez *p, int linRei, int colRei);
int afogamentoPreto(const PartidaXadrez *p, int linRei, int colRei);
int xequeMateBranco(const PartidaXadrez *p, int linRei, int colRei);
int xequeMatePreto(const PartidaXadrez *p, int linRei, int colRei);

void salvarJogoXadrez(PartidaXadrez *p);
void carregarJogoXadrez(PartidaXadrez *p);
void salvarAutomatico(PartidaXadrez *p);
void desfazer(PartidaXadrez *p);
void refazer(PartidaXadrez *p);

// ============================================================================
// MODULO 1: FUNCAO PRINCIPAL, ALOCACAO DINAMICA E MENU EM LACO
// ============================================================================

// Funcao principal: aloca o vetor inicial com malloc, carrega o arquivo e executa o menu
int main(void) {
    SetConsoleOutputCP(437);
    SetConsoleCP(437);

    int quantidade = 0;
    int capacidade = CAPACIDADE_INICIAL;
    int opcao = -1;

    // ITEM 2: Alocacao dinamica inicial com malloc e teste de NULL
    Jogador *jogadores = (Jogador *)malloc(capacidade * sizeof(Jogador));
    if (jogadores == NULL) {
        printf("Erro critico: Falha ao alocar memoria inicial com malloc!\n");
        return 1;
    }

    // ITEM 5: Carrega os registros do arquivo ao iniciar o programa
    carregarDadosArquivo(&jogadores, &quantidade, &capacidade);

    // ITEM 3: Menu em laco do-while com switch e pelo menos 7 opcoes
    do {
        definirCor(9, 0);
        printf("\n====================================================================\n");
        printf("          SISTEMA DE GESTAO - CLUBE E TORNEIO DE XADREZ\n");
        printf("====================================================================\n");
        definirCor(7, 0);
        printf("  Registros na memoria: %d | Capacidade atual do vetor (malloc): %d\n", quantidade, capacidade);
        printf("--------------------------------------------------------------------\n");
        printf("  1 - Cadastrar novo jogador\n");
        printf("  2 - Listar todos os jogadores (Tabela)\n");
        printf("  3 - Buscar jogador (por Codigo ou por Nome)\n");
        printf("  4 - Alterar dados de um jogador\n");
        printf("  5 - Excluir jogador\n");
        printf("  6 - Gerar Relatorio Estatistico (Tela e relatorio.txt)\n");
        printf("  7 - Jogar Partida no Tabuleiro de Xadrez\n");
        printf("  0 - Sair e salvar dados\n");
        printf("====================================================================\n");

        opcao = lerInteiroValido("Escolha uma opcao: ", 1);

        switch (opcao) {
        case 1:
            cadastrarJogador(&jogadores, &quantidade, &capacidade);
            break;

        case 2:
            listarJogadores(jogadores, quantidade);
            break;

        case 3:
            buscarJogador(jogadores, quantidade);
            break;

        case 4:
            alterarJogador(jogadores, quantidade);
            break;

        case 5:
            excluirJogador(jogadores, &quantidade);
            break;

        case 6:
            gerarRelatorio(jogadores, quantidade);
            break;

        case 7:
            abrirModuloXadrez(jogadores, quantidade);
            break;

        case 0:
            // ITEM 6: Salva todos os dados no arquivo antes de fechar
            salvarDadosArquivo(jogadores, quantidade);
            definirCor(10, 0);
            printf("\nDados salvos com sucesso em '%s'. Encerrando o sistema...\n", ARQUIVO_DADOS);
            definirCor(7, 0);
            break;

        default:
            // ITEM 8: Tratamento de opcao inexistente no menu
            definirCor(4, 0);
            printf("\nErro: Opcao inexistente! Escolha uma opcao entre 0 e 7.\n");
            definirCor(7, 0);
            break;
        }

    } while (opcao != 0);

    // ITEM 2: Libera a memoria alocada dinamicamente antes de encerrar o programa
    free(jogadores);
    jogadores = NULL;

    return 0;
}

// Dobra a capacidade do vetor dinamico usando realloc quando ele enche
int expandirCapacidade(Jogador **vetor, int *capacidade) {
    int novaCapacidade = (*capacidade) * 2;
    Jogador *novoBloco = (Jogador *)realloc(*vetor, novaCapacidade * sizeof(Jogador));

    // ITEM 2: Sempre testa se o realloc retornou NULL
    if (novoBloco == NULL) {
        definirCor(4, 0);
        printf("\nErro de memoria: Nao foi possivel expandir o vetor com realloc!\n");
        definirCor(7, 0);
        return 0;
    }

    *vetor = novoBloco;
    *capacidade = novaCapacidade;
    return 1;
}

// ============================================================================
// FUNCOES AUXILIARES DE LEITURA E VALIDACAO (ITEM 8)
// ============================================================================

// Altera a cor do texto e do fundo no console do Windows
void definirCor(int corTexto, int corFundo) {
    WORD cor = ((corFundo & 0x0F) << 4) + (corTexto & 0x0F);
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), cor);
}

// Descarta caracteres restantes no buffer do teclado (stdin)
void limparBufferTeclado(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Le uma string do teclado com fgets, removendo a quebra de linha e trocando ';' por ','
void lerTexto(char *destino, int tamanho) {
    if (fgets(destino, tamanho, stdin) != NULL) {
        size_t len = strlen(destino);
        if (len > 0 && destino[len - 1] == '\n') {
            destino[len - 1] = '\0';
        } else {
            limparBufferTeclado();
        }
        // Substitui eventual ';' digitado para nao corromper o separador do arquivo
        for (size_t i = 0; destino[i] != '\0'; i++) {
            if (destino[i] == ';') {
                destino[i] = ',';
            }
        }
    } else {
        destino[0] = '\0';
    }
}

// Le e valida um numero inteiro (nao aceita letras nem numeros negativos)
int lerInteiroValido(const char *mensagem, int permitirZero) {
    int valor;
    int lido;
    while (1) {
        printf("%s", mensagem);
        lido = scanf("%d", &valor);
        limparBufferTeclado();

        if (lido != 1) {
            definirCor(4, 0);
            printf("Entrada invalida! Digite apenas numeros inteiros.\n");
            definirCor(7, 0);
        } else if ((permitirZero && valor < 0) || (!permitirZero && valor <= 0)) {
            definirCor(4, 0);
            if (permitirZero)
                printf("Erro: O valor nao pode ser negativo!\n");
            else
                printf("Erro: O valor deve ser maior que zero!\n");
            definirCor(7, 0);
        } else {
            return valor;
        }
    }
}

// Le e valida um numero real float (nao aceita letras nem valores negativos)
float lerFloatValido(const char *mensagem) {
    float valor;
    int lido;
    while (1) {
        printf("%s", mensagem);
        lido = scanf("%f", &valor);
        limparBufferTeclado();

        if (lido != 1) {
            definirCor(4, 0);
            printf("Entrada invalida! Digite um valor numerico (ex: 1500.50).\n");
            definirCor(7, 0);
        } else if (valor < 0.0f) {
            definirCor(4, 0);
            printf("Erro: O valor nao pode ser negativo!\n");
            definirCor(7, 0);
        } else {
            return valor;
        }
    }
}

// Verifica se a string 'busca' aparece dentro de 'texto' ignorando maiusculas/minusculas
int contemTextoIgnorandoCase(const char *texto, const char *busca) {
    char copiaTexto[100], copiaBusca[100];
    int i;

    for (i = 0; texto[i] != '\0' && i < 99; i++)
        copiaTexto[i] = (char)tolower((unsigned char)texto[i]);
    copiaTexto[i] = '\0';

    for (i = 0; busca[i] != '\0' && i < 99; i++)
        copiaBusca[i] = (char)tolower((unsigned char)busca[i]);
    copiaBusca[i] = '\0';

    return strstr(copiaTexto, copiaBusca) != NULL;
}

// Procura um jogador pelo codigo e retorna seu indice no vetor (ou -1 se nao encontrar)
int buscarIndicePorCodigo(const Jogador *vetor, int quantidade, int codigo) {
    for (int i = 0; i < quantidade; i++) {
        if (vetor[i].codigo == codigo) {
            return i;
        }
    }
    return -1;
}

// ============================================================================
// MODULO 2: CADASTRAR E LISTAR REGISTROS EM TABELA ALINHADA
// ============================================================================

// Cadastra um novo jogador validando codigo repetido e expandindo o vetor com realloc se cheio
int cadastrarJogador(Jogador **vetor, int *quantidade, int *capacidade) {
    printf("\n--- CADASTRAR NOVO JOGADOR ---\n");

    // ITEM 2: Se o vetor estiver cheio, dobra a capacidade usando realloc
    if (*quantidade >= *capacidade) {
        if (!expandirCapacidade(vetor, capacidade)) {
            return 0;
        }
        definirCor(10, 0);
        printf("[Memoria] Vetor cheio! Capacidade dobrada com realloc para %d registros.\n", *capacidade);
        definirCor(7, 0);
    }

    Jogador novo;

    // ITEM 8: Nao aceita codigo repetido nem menor/igual a zero
    while (1) {
        novo.codigo = lerInteiroValido("Codigo do jogador (ex: 101): ", 0);
        if (buscarIndicePorCodigo(*vetor, *quantidade, novo.codigo) != -1) {
            definirCor(4, 0);
            printf("Erro: Ja existe um jogador cadastrado com o codigo %d!\n", novo.codigo);
            definirCor(7, 0);
        } else {
            break;
        }
    }

    // Leitura e validacao do nome
    do {
        printf("Nome do jogador: ");
        lerTexto(novo.nome, sizeof(novo.nome));
        if (novo.nome[0] == '\0') {
            definirCor(4, 0);
            printf("Erro: O nome nao pode ficar em branco!\n");
            definirCor(7, 0);
        }
    } while (novo.nome[0] == '\0');

    // Leitura e validacao da categoria
    do {
        printf("Categoria (Iniciante / Intermediario / Avancado / Mestre): ");
        lerTexto(novo.categoria, sizeof(novo.categoria));
        if (novo.categoria[0] == '\0') {
            definirCor(4, 0);
            printf("Erro: A categoria nao pode ficar em branco!\n");
            definirCor(7, 0);
        }
    } while (novo.categoria[0] == '\0');

    // Leitura e validacao de vitorias (int >= 0) e rating (float >= 0)
    novo.vitorias = lerInteiroValido("Quantidade de vitorias: ", 1);
    novo.rating = lerFloatValido("Rating / Pontuacao atual (ex: 1650.50): ");

    // Armazena no vetor dinamico e incrementa a quantidade
    (*vetor)[*quantidade] = novo;
    (*quantidade)++;

    // ITEM 6: Salva no arquivo imediatamente apos o cadastro
    salvarDadosArquivo(*vetor, *quantidade);

    definirCor(10, 0);
    printf("\nJogador '%s' (Codigo %d) cadastrado e salvo com sucesso!\n", novo.nome, novo.codigo);
    definirCor(7, 0);
    return 1;
}

// Lista todos os jogadores cadastrados em formato de tabela alinhada
void listarJogadores(const Jogador *vetor, int quantidade) {
    if (quantidade == 0) {
        definirCor(6, 0);
        printf("\nNenhum jogador cadastrado no momento.\n");
        definirCor(7, 0);
        return;
    }

    printf("\n+--------+------------------------------+--------------------+----------+------------+\n");
    printf("| %-6s | %-28s | %-18s | %-8s | %-10s |\n",
           "CODIGO", "NOME DO JOGADOR", "CATEGORIA", "VITORIAS", "RATING");
    printf("+--------+------------------------------+--------------------+----------+------------+\n");

    for (int i = 0; i < quantidade; i++) {
        printf("| %-6d | %-28.28s | %-18.18s | %-8d | %10.2f |\n",
               vetor[i].codigo,
               vetor[i].nome,
               vetor[i].categoria,
               vetor[i].vitorias,
               vetor[i].rating);
    }

    printf("+--------+------------------------------+--------------------+----------+------------+\n");
    printf("Total de registros listados: %d\n", quantidade);
}

// ============================================================================
// MODULO 3: BUSCAR (POR CODIGO E POR NOME), ALTERAR E EXCLUIR
// ============================================================================

// Busca jogadores tanto por codigo exato quanto por parte do nome
void buscarJogador(const Jogador *vetor, int quantidade) {
    if (quantidade == 0) {
        definirCor(6, 0);
        printf("\nLista vazia! Nao ha jogadores para buscar.\n");
        definirCor(7, 0);
        return;
    }

    printf("\n--- BUSCAR JOGADOR ---\n");
    printf("  1 - Buscar por Codigo\n");
    printf("  2 - Buscar por Nome\n");
    int tipoBusca = lerInteiroValido("Escolha o tipo de busca: ", 0);

    if (tipoBusca == 1) {
        int codigo = lerInteiroValido("Digite o codigo do jogador: ", 0);
        int idx = buscarIndicePorCodigo(vetor, quantidade, codigo);

        if (idx == -1) {
            definirCor(4, 0);
            printf("\nNenhum jogador encontrado com o codigo %d.\n", codigo);
            definirCor(7, 0);
        } else {
            printf("\nRegistro encontrado:\n");
            printf("+--------+------------------------------+--------------------+----------+------------+\n");
            printf("| %-6s | %-28s | %-18s | %-8s | %-10s |\n",
                   "CODIGO", "NOME DO JOGADOR", "CATEGORIA", "VITORIAS", "RATING");
            printf("+--------+------------------------------+--------------------+----------+------------+\n");
            printf("| %-6d | %-28.28s | %-18.18s | %-8d | %10.2f |\n",
                   vetor[idx].codigo, vetor[idx].nome, vetor[idx].categoria,
                   vetor[idx].vitorias, vetor[idx].rating);
            printf("+--------+------------------------------+--------------------+----------+------------+\n");
        }
    } else if (tipoBusca == 2) {
        char termo[50];
        printf("Digite o nome (ou parte do nome): ");
        lerTexto(termo, sizeof(termo));

        int encontrados = 0;
        for (int i = 0; i < quantidade; i++) {
            if (contemTextoIgnorandoCase(vetor[i].nome, termo)) {
                if (encontrados == 0) {
                    printf("\nResultados encontrados:\n");
                    printf("+--------+------------------------------+--------------------+----------+------------+\n");
                    printf("| %-6s | %-28s | %-18s | %-8s | %-10s |\n",
                           "CODIGO", "NOME DO JOGADOR", "CATEGORIA", "VITORIAS", "RATING");
                    printf("+--------+------------------------------+--------------------+----------+------------+\n");
                }
                printf("| %-6d | %-28.28s | %-18.18s | %-8d | %10.2f |\n",
                       vetor[i].codigo, vetor[i].nome, vetor[i].categoria,
                       vetor[i].vitorias, vetor[i].rating);
                encontrados++;
            }
        }

        if (encontrados > 0) {
            printf("+--------+------------------------------+--------------------+----------+------------+\n");
            printf("Total encontrado: %d registro(s).\n", encontrados);
        } else {
            definirCor(4, 0);
            printf("\nNenhum jogador encontrado contendo '%s'.\n", termo);
            definirCor(7, 0);
        }
    } else {
        definirCor(4, 0);
        printf("\nOpcao de busca invalida!\n");
        definirCor(7, 0);
    }
}

// Altera os dados de um jogador existente localizado pelo seu codigo
void alterarJogador(Jogador *vetor, int quantidade) {
    if (quantidade == 0) {
        definirCor(6, 0);
        printf("\nLista vazia! Nao ha jogadores para alterar.\n");
        definirCor(7, 0);
        return;
    }

    printf("\n--- ALTERAR DADOS DE JOGADOR ---\n");
    int codigo = lerInteiroValido("Informe o codigo do jogador que deseja alterar: ", 0);
    int idx = buscarIndicePorCodigo(vetor, quantidade, codigo);

    if (idx == -1) {
        definirCor(4, 0);
        printf("\nErro: Jogador com codigo %d nao encontrado!\n", codigo);
        definirCor(7, 0);
        return;
    }

    printf("\nDados atuais -> Nome: %s | Categoria: %s | Vitorias: %d | Rating: %.2f\n",
           vetor[idx].nome, vetor[idx].categoria, vetor[idx].vitorias, vetor[idx].rating);

    do {
        printf("Novo nome: ");
        lerTexto(vetor[idx].nome, sizeof(vetor[idx].nome));
        if (vetor[idx].nome[0] == '\0') {
            printf("O nome nao pode ficar vazio!\n");
        }
    } while (vetor[idx].nome[0] == '\0');

    do {
        printf("Nova categoria: ");
        lerTexto(vetor[idx].categoria, sizeof(vetor[idx].categoria));
        if (vetor[idx].categoria[0] == '\0') {
            printf("A categoria nao pode ficar vazia!\n");
        }
    } while (vetor[idx].categoria[0] == '\0');

    vetor[idx].vitorias = lerInteiroValido("Nova quantidade de vitorias: ", 1);
    vetor[idx].rating = lerFloatValido("Novo rating: ");

    // ITEM 6: Salva no arquivo apos a alteracao
    salvarDadosArquivo(vetor, quantidade);

    definirCor(10, 0);
    printf("\nRegistro do codigo %d atualizado e salvo com sucesso!\n", codigo);
    definirCor(7, 0);
}

// Exclui um registro do vetor apos pedir confirmacao ("Tem certeza? S/N")
void excluirJogador(Jogador *vetor, int *quantidade) {
    if (*quantidade == 0) {
        definirCor(6, 0);
        printf("\nLista vazia! Nao ha jogadores para excluir.\n");
        definirCor(7, 0);
        return;
    }

    printf("\n--- EXCLUIR JOGADOR ---\n");
    int codigo = lerInteiroValido("Informe o codigo do jogador que deseja excluir: ", 0);
    int idx = buscarIndicePorCodigo(vetor, *quantidade, codigo);

    if (idx == -1) {
        definirCor(4, 0);
        printf("\nErro: Jogador com codigo %d nao encontrado!\n", codigo);
        definirCor(7, 0);
        return;
    }

    printf("\nJogador selecionado: [%d] %s - Categoria: %s - Vitorias: %d - Rating: %.2f\n",
           vetor[idx].codigo, vetor[idx].nome, vetor[idx].categoria,
           vetor[idx].vitorias, vetor[idx].rating);

    // ITEM 4: Confirmacao obrigatoria antes de excluir
    char confirmacao[10];
    printf("Tem certeza que deseja excluir este registro? (S/N): ");
    lerTexto(confirmacao, sizeof(confirmacao));

    if (confirmacao[0] == 's' || confirmacao[0] == 'S') {
        // Desloca os elementos seguintes uma posicao para a esquerda
        for (int i = idx; i < (*quantidade) - 1; i++) {
            vetor[i] = vetor[i + 1];
        }
        (*quantidade)--;

        // ITEM 6: Atualiza o arquivo imediatamente apos a exclusao
        salvarDadosArquivo(vetor, *quantidade);

        definirCor(10, 0);
        printf("\nRegistro excluido com sucesso!\n");
        definirCor(7, 0);
    } else {
        printf("\nExclusao cancelada pelo usuario.\n");
    }
}

// ============================================================================
// MODULO 4: ARQUIVOS - LEITURA AO INICIAR E GRAVACAO SEPARADA POR ';'
// ============================================================================

// Abre "dados.txt" no modo "r" e carrega todos os registros para o vetor dinamico
int carregarDadosArquivo(Jogador **vetor, int *quantidade, int *capacidade) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "r");

    // ITEM 5 e ITEM 8: Se o arquivo nao existir, avisa e comeca vazio sem travar
    if (arquivo == NULL) {
        definirCor(6, 0);
        printf("[Aviso] Arquivo '%s' nao encontrado. O sistema iniciara com cadastro vazio.\n", ARQUIVO_DADOS);
        definirCor(7, 0);
        return 0;
    }

    char linha[256];
    *quantidade = 0;

    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        // Ignora linhas em branco
        if (linha[0] == '\n' || linha[0] == '\r' || linha[0] == '\0') {
            continue;
        }

        Jogador temp;
        // Le os 5 campos separados por ponto-e-virgula (;)
        int lidos = sscanf(linha, "%d;%49[^;];%29[^;];%d;%f",
                           &temp.codigo,
                           temp.nome,
                           temp.categoria,
                           &temp.vitorias,
                           &temp.rating);

        if (lidos == 5) {
            // Se o vetor encher durante a leitura do arquivo, cresce com realloc
            if (*quantidade >= *capacidade) {
                if (!expandirCapacidade(vetor, capacidade)) {
                    break;
                }
            }
            (*vetor)[*quantidade] = temp;
            (*quantidade)++;
        }
    }

    fclose(arquivo);
    definirCor(10, 0);
    printf("[Arquivo] %d registro(s) carregado(s) com sucesso de '%s'.\n", *quantidade, ARQUIVO_DADOS);
    definirCor(7, 0);
    return 1;
}

// Grava todos os registros em "dados.txt" no modo "w" separados por ';'
int salvarDadosArquivo(const Jogador *vetor, int quantidade) {
    FILE *arquivo = fopen(ARQUIVO_DADOS, "w");

    // ITEM 8: Testa se fopen retornou NULL
    if (arquivo == NULL) {
        definirCor(4, 0);
        printf("\nErro: Nao foi possivel abrir '%s' para gravacao!\n", ARQUIVO_DADOS);
        definirCor(7, 0);
        return 0;
    }

    for (int i = 0; i < quantidade; i++) {
        fprintf(arquivo, "%d;%s;%s;%d;%.2f\n",
                vetor[i].codigo,
                vetor[i].nome,
                vetor[i].categoria,
                vetor[i].vitorias,
                vetor[i].rating);
    }

    fclose(arquivo);
    return 1;
}

// ============================================================================
// MODULO 5: RELATORIO FORMATADO NA TELA E EM ARQUIVO (relatorio.txt)
// ============================================================================

// Gera o relatorio completo com cabecalho, data, tabela, estatisticas e rodape na tela e em relatorio.txt
void gerarRelatorio(const Jogador *vetor, int quantidade) {
    FILE *arqRel = fopen(ARQUIVO_RELATORIO, "w");
    if (arqRel == NULL) {
        definirCor(4, 0);
        printf("\nErro: Nao foi possivel criar o arquivo '%s'!\n", ARQUIVO_RELATORIO);
        definirCor(7, 0);
        return;
    }

    // Obtem a data e hora atual do sistema para o cabecalho do relatorio
    time_t agora = time(NULL);
    struct tm *infoTempo = localtime(&agora);
    char dataFormatada[40];
    if (infoTempo != NULL) {
        strftime(dataFormatada, sizeof(dataFormatada), "%d/%m/%Y as %H:%M:%S", infoTempo);
    } else {
        strcpy(dataFormatada, "Data indisponivel");
    }

    // Calcula as estatisticas exigidas no Item 7 (total, soma, media, maior e menor valor)
    int somaVitorias = 0;
    float somaRating = 0.0f;
    float mediaRating = 0.0f;
    int idxMaiorRating = 0;
    int idxMenorRating = 0;

    for (int i = 0; i < quantidade; i++) {
        somaVitorias += vetor[i].vitorias;
        somaRating += vetor[i].rating;
        if (vetor[i].rating > vetor[idxMaiorRating].rating) {
            idxMaiorRating = i;
        }
        if (vetor[i].rating < vetor[idxMenorRating].rating) {
            idxMenorRating = i;
        }
    }
    if (quantidade > 0) {
        mediaRating = somaRating / (float)quantidade;
    }

    // Imprime simultaneamente na tela (stdout) e no arquivo (arqRel) usando um laco de 2 destinos
    FILE *destinos[2] = {stdout, arqRel};

    for (int d = 0; d < 2; d++) {
        FILE *out = destinos[d];

        fprintf(out, "\n========================================================================================\n");
        fprintf(out, "                 RELATORIO OFICIAL - CLUBE E CAMPEONATO DE XADREZ\n");
        fprintf(out, "                 Data de emissao: %s\n", dataFormatada);
        fprintf(out, "========================================================================================\n\n");

        if (quantidade == 0) {
            fprintf(out, "Nenhum jogador cadastrado para exibir estatisticas.\n");
        } else {
            fprintf(out, "+--------+------------------------------+--------------------+----------+------------+\n");
            fprintf(out, "| %-6s | %-28s | %-18s | %-8s | %-10s |\n",
                    "CODIGO", "NOME DO JOGADOR", "CATEGORIA", "VITORIAS", "RATING");
            fprintf(out, "+--------+------------------------------+--------------------+----------+------------+\n");

            for (int i = 0; i < quantidade; i++) {
                fprintf(out, "| %-6d | %-28.28s | %-18.18s | %-8d | %10.2f |\n",
                        vetor[i].codigo,
                        vetor[i].nome,
                        vetor[i].categoria,
                        vetor[i].vitorias,
                        vetor[i].rating);
            }

            fprintf(out, "+--------+------------------------------+--------------------+----------+------------+\n\n");
            fprintf(out, "-------------------------------- ESTATISTICAS DO CLUBE ---------------------------------\n");
            fprintf(out, "  1. Total de jogadores cadastrados : %d registro(s)\n", quantidade);
            fprintf(out, "  2. Soma total de vitorias         : %d partida(s) vencida(s)\n", somaVitorias);
            fprintf(out, "  3. Soma / Media de Rating do clube: Soma = %.2f | Media = %.2f pontos\n", somaRating, mediaRating);
            fprintf(out, "  4. Maior Rating cadastrado        : %.2f (%s - Cod. %d)\n",
                    vetor[idxMaiorRating].rating, vetor[idxMaiorRating].nome, vetor[idxMaiorRating].codigo);
            fprintf(out, "  5. Menor Rating cadastrado        : %.2f (%s - Cod. %d)\n",
                    vetor[idxMenorRating].rating, vetor[idxMenorRating].nome, vetor[idxMenorRating].codigo);
            fprintf(out, "----------------------------------------------------------------------------------------\n");
        }

        fprintf(out, "Rodape: Sistema de Gestao de Xadrez em C - Relatorio gerado automaticamente.\n");
        fprintf(out, "========================================================================================\n");
    }

    fclose(arqRel);

    definirCor(10, 0);
    printf("\nRelatorio exibido na tela e gravado com sucesso no arquivo '%s'!\n", ARQUIVO_RELATORIO);
    definirCor(7, 0);
}

// ============================================================================
// MODULO BONUS: PARTIDA DE XADREZ NO TABULEIRO (INTEGRADA AO CADASTRO)
// ============================================================================

// Prepara o estado inicial do tabuleiro 8x8 e das variaveis da partida na struct PartidaXadrez
void inicializarEstadoTabuleiro(PartidaXadrez *p) {
    memset(p, 0, sizeof(PartidaXadrez));

    const char layoutInicial[LINHAS][COLUNAS] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {0, 'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {0, (char)219, ' ', (char)219, ' ', (char)219, ' ', (char)219, ' '},
        {0, ' ', (char)219, ' ', (char)219, ' ', (char)219, ' ', (char)219},
        {0, (char)219, ' ', (char)219, ' ', (char)219, ' ', (char)219, ' '},
        {0, ' ', (char)219, ' ', (char)219, ' ', (char)219, ' ', (char)219},
        {0, 'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {0, 'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    memcpy(p->tabuleiro, layoutInicial, sizeof(layoutInicial));
    p->vezJogador1 = 1;
    p->vezJogador2 = 0;
    p->posRei1Linha = 1;
    p->posRei1Coluna = 5;
    p->posRei2Linha = 8;
    p->posRei2Coluna = 5;
    p->ctrlSalvarAtivo = 0;

    FILE *arqNomes = fopen("savename.txt", "r");
    if (arqNomes == NULL) {
        p->ctrlCarregarAtivo = 0;
    } else {
        p->ctrlCarregarAtivo = 1;
        fclose(arqNomes);
    }
}

// Abre o modulo de jogo de xadrez e permite atualizar as vitorias do vencedor cadastrado
void abrirModuloXadrez(Jogador *vetor, int quantidade) {
    PartidaXadrez partida;
    inicializarEstadoTabuleiro(&partida);

    mostrarMenuXadrez(&partida);
    system("cls");

    // Evita deixar qualquer alteracao pendente sem salvar
    if (quantidade > 0) {
        salvarDadosArquivo(vetor, quantidade);
    }
}

// Menu interativo do tabuleiro de xadrez (Novo/Continuar, Salvar, Carregar, Voltar com ESC)
int mostrarMenuXadrez(PartidaXadrez *p) {
    int opcao;

inicioMenu:
    opcao = controlarMenuXadrez(p);
    system("cls");

    switch (opcao) {
    case 0:
        if (p->emAndamento == 0) {
        lerNome1:
            definirCor(9, 0);
            printf("Nome do Jogador 1 (Brancas): ");
            definirCor(7, 0);
            lerTexto(p->nomeJogador1, sizeof(p->nomeJogador1));
            if (p->nomeJogador1[0] == '\0') {
                system("cls");
                definirCor(4, 0);
                printf("Digite um nome valido!\n");
                definirCor(7, 0);
                goto lerNome1;
            }

        lerNome2:
            definirCor(9, 0);
            printf("Nome do Jogador 2 (Pretas): ");
            definirCor(7, 0);
            lerTexto(p->nomeJogador2, sizeof(p->nomeJogador2));
            if (p->nomeJogador2[0] == '\0') {
                system("cls");
                definirCor(4, 0);
                printf("Digite um nome valido!\n");
                definirCor(7, 0);
                goto lerNome2;
            } else if (strcmp(p->nomeJogador1, p->nomeJogador2) == 0) {
                system("cls");
                definirCor(4, 0);
                printf("Esse nome ja foi escolhido!\n");
                definirCor(7, 0);
                goto lerNome2;
            }

            system("cls");
            iniciarPartidaXadrez(p);
        } else {
            return 1;
        }
        break;

    case 1:
        if (p->ctrlSalvarAtivo == 0) {
            goto inicioMenu;
        } else {
            salvarJogoXadrez(p);
            p->ctrlCarregarAtivo = 1;
            return 1;
        }
        break;

    case 2:
        if (p->ctrlCarregarAtivo == 0) {
            goto inicioMenu;
        } else {
            p->maxRefazer = 0;
            p->contHistorico = 0;
            carregarJogoXadrez(p);
            if (p->emAndamento == 0) {
                iniciarPartidaXadrez(p);
            }
        }
        break;

    case 3:
    case -1:
        return -1;
    }

    return 0;
}

// Controla as setas para cima e para baixo no menu do tabuleiro de xadrez
int controlarMenuXadrez(PartidaXadrez *p) {
    int posCursor = 0, sair = 0;

    while (!sair) {
        exibirMenuXadrez(p, posCursor);
        switch (lerTecla()) {
        case SETA_CIMA:
            if (posCursor > 0)
                posCursor--;
            else
                posCursor = 3;
            break;

        case SETA_BAIXO:
            if (posCursor < 3)
                posCursor++;
            else
                posCursor = 0;
            break;

        case ENTER:
            sair = 1;
            break;

        case ESC:
            posCursor = -1;
            sair = 1;
            break;
        }
    }

    return posCursor;
}

// Le uma tecla imediatamente usando getch() tratando teclas especiais (setas)
int lerTecla(void) {
    int tecla = getch();
    if (tecla == 0 || tecla == 224) {
        tecla = getch();
    }
    return tecla;
}

// Desenha a tela de menu do modo Tabuleiro de Xadrez
void exibirMenuXadrez(PartidaXadrez *p, int posCursor) {
    system("cls");
    int i = 0;
    const char *opcoes[4] = {"   Novo   ", "  Salvar  ", " Carregar ", "  Voltar  "};
    if (p->emAndamento == 1) {
        opcoes[0] = " Continuar";
    }

    definirCor(9, 0);
    printf("\t              88\n");
    printf("\t              88\n");
    printf("\t              88\n");
    printf("\t   ,adPPYba,  88,dPPYba,    ,adPPYba,  ,adPPYba,  ,adPPYba,\n");
    definirCor(10, 0);
    printf("\t  a8\"     \"\"  88P'    \"8a  a8P_____88  I8[    \"\"  I8[    \"\n");
    printf("\t  8b          88       88  8PP\"\"\"\"\"\"\"   `\"Y8ba,    `\"Y8ba, \n");
    printf("\t  \"8a,   ,aa  88       88  \"8b,   ,aa  aa    ]8I  aa    ]8I\n");
    definirCor(9, 0);
    printf("\t   `\"Ybbd8\"'  88       88   `\"Ybbd8\"'  `\"YbbdP\"'  `\"YbbdP\"'\n\n\n");
    definirCor(7, 0);

    definirCor(9, 0);
    printf("\t\t\t\t\xc9\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbb");
    printf("\n\t\t\t\t\xba                 \xba");
    for (i = 0; i < 4; i++) {
        printf("\n\t\t\t\t\xba   ");
        if (p->ctrlSalvarAtivo == 0 && i == 1)
            definirCor(8, 0);
        if (p->ctrlCarregarAtivo == 0 && i == 2)
            definirCor(8, 0);
        if (i == posCursor) {
            definirCor(0, 15);
            posCursor = -1;
        }
        printf("%s", opcoes[i]);
        definirCor(9, 0);
        printf("    \xba\n\t\t\t\t\xba                 \xba");
    }

    printf("\n\t\t\t\t\xc8\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xbc");
    definirCor(7, 0);
    printf("\n\n");
}

// Desenha o tabuleiro 8x8, as pecas capturadas e os atalhos na tela
int desenharTabuleiro(const PartidaXadrez *p) {
    int i = 0, j = 0, k = 0;

    definirCor(9, 0);
    printf("Pecas capturadas (Brancas): ");
    definirCor(7, 0);
    for (i = 0; i < p->qtdCapturadas1; i++) {
        printf("%c, ", p->capturadas1[i]);
    }
    printf("\n");

    definirCor(9, 0);
    printf("Pecas capturadas (Pretas) : ");
    definirCor(7, 0);
    for (i = 0; i < p->qtdCapturadas2; i++) {
        definirCor(6, 0);
        printf("%c", p->capturadas2[i]);
        definirCor(7, 0);
        printf(", ");
    }

    printf("\n\n \t\t\t");
    for (k = 65; k < 73; k++) {
        printf("%c   ", k);
    }
    printf("\n\n");

    printf("\t\t      \xc9");
    for (i = 0; i < 7; i++) {
        printf("\xcd\xcd\xcd\xd1");
    }
    printf("\xcd\xcd\xcd\xbb");

    for (i = 8; i > 0; i--) {
        printf("\n\t\t  %d   \xba ", i);
        for (j = 1; j < 9; j++) {
            if (isupper((unsigned char)p->tabuleiro[i][j])) {
                definirCor(6, 0);
                printf("%c", p->tabuleiro[i][j]);
                definirCor(7, 0);
                printf(" \xb3 ");
            } else {
                printf("%c \xb3 ", p->tabuleiro[i][j]);
            }
        }
        printf("\b\b\xba");

        definirCor(9, 0);
        if (i == 8)
            printf("   Menu     => tecla ESC");
        if (i == 7)
            printf("   Desfazer => tecla U");
        if (i == 6)
            printf("   Refazer  => tecla R");
        definirCor(7, 0);

        if (i != 1) {
            int l = 0;
            printf("\n\t\t      \xc7");
            for (l = 0; l < 8; l++) {
                printf("\xc4\xc4\xc4\xc5");
            }
            printf("\b\xb6");
        }
    }

    printf("\n\t\t      \xc8");
    for (i = 0; i < 7; i++) {
        printf("\xcd\xcd\xcd\xcf");
    }
    printf("\xcd\xcd\xcd\xbc");
    printf("\n\n");
    return 0;
}

// Converte a letra da coluna ('a'-'h' ou 'A'-'H') para indice de 1 a 8
int converterColuna(char letra) {
    if (letra >= 'a' && letra <= 'h')
        return (letra - 'a') + 1;
    if (letra >= 'A' && letra <= 'H')
        return (letra - 'A') + 1;
    return 0;
}

// Retorna o caractere padrao de uma casa vazia (219 para casa clara ou ' ' para casa escura)
char casaPadrao(int linha, int coluna) {
    if ((linha % 2 == 0 && coluna % 2 == 0) || (linha % 2 != 0 && coluna % 2 != 0))
        return (char)219;
    return ' ';
}

// Controla o loop de jogadas da partida de xadrez
int iniciarPartidaXadrez(PartidaXadrez *p) {
    int i = 0, lin1, lin2, col1, col2, avisoRei = 0, semAutoSave = 0;
    char colChar1, colChar2, peca;

repetirTurno:
    if (semAutoSave == 0 && p->pularAutoSave == 0) {
        salvarAutomatico(p);
    }
    semAutoSave = 0;
    p->pularAutoSave = 0;

    desenharTabuleiro(p);

    if (xequeMateBranco(p, p->posRei1Linha, p->posRei1Coluna) != 0) {
        printf("\t\t\t\t ");
        definirCor(9, 0);
        printf("Xeque-Mate! Vitoria das Pretas (%s)!\n", p->nomeJogador2);
        definirCor(7, 0);
        printf("\nPressione qualquer tecla para voltar ao menu do sistema...");
        getch();
        return 2;
    } else if (xequeMatePreto(p, p->posRei2Linha, p->posRei2Coluna) != 0) {
        printf("\t\t\t\t ");
        definirCor(9, 0);
        printf("Xeque-Mate! Vitoria das Brancas (%s)!\n", p->nomeJogador1);
        definirCor(7, 0);
        printf("\nPressione qualquer tecla para voltar ao menu do sistema...");
        getch();
        return 1;
    }

    if (p->flagErro == 1) {
        definirCor(4, 0);
        printf("Movimento invalido, tente novamente!\n");
        definirCor(7, 0);
    }
    if (xequeBranco(p, p->posRei1Linha, p->posRei1Coluna) != 0 && p->vezJogador1) {
        definirCor(4, 0);
        printf("Xeque! Seu rei (Brancas) esta ameacado!\n");
        definirCor(7, 0);
    }
    if (xequePreto(p, p->posRei2Linha, p->posRei2Coluna) != 0 && p->vezJogador2) {
        definirCor(4, 0);
        printf("Xeque! Seu rei (Pretas) esta ameacado!\n");
        definirCor(7, 0);
    }
    if (avisoRei == 1) {
        definirCor(4, 0);
        printf("Cuidado! Esse movimento deixa seu rei em xeque!\n");
        definirCor(7, 0);
    }

    avisoRei = 0;
    p->flagErro = 0;

    if (afogamentoBranco(p, p->posRei1Linha, p->posRei1Coluna) != 0 && p->vezJogador1) {
        if (!(p->tabuleiro[2][4] == 'p' && p->tabuleiro[2][5] == 'p' && p->tabuleiro[2][6] == 'p')) {
            definirCor(4, 0);
            printf("Atencao: Rei branco sem movimentos livres (possivel afogamento)!\n");
            definirCor(7, 0);
        }
    }
    if (afogamentoPreto(p, p->posRei2Linha, p->posRei2Coluna) != 0 && p->vezJogador2) {
        if (!(p->tabuleiro[7][4] == 'P' && p->tabuleiro[7][5] == 'P' && p->tabuleiro[7][6] == 'P')) {
            definirCor(4, 0);
            printf("Atencao: Rei preto sem movimentos livres (possivel afogamento)!\n");
            definirCor(7, 0);
        }
    }

    if (p->vezJogador1) {
        printf("Vez de %s (Brancas - ex: e2e4): ", p->nomeJogador1);
    } else {
        definirCor(6, 0);
        printf("Vez de %s (Pretas  - ex: e7e5): ", p->nomeJogador2);
        definirCor(7, 0);
    }

    colChar1 = (char)lerTecla();

    if (colChar1 == (char)ESC) {
        p->emAndamento = 1;
        p->ctrlSalvarAtivo = 1;
        int retMenu = mostrarMenuXadrez(p);
        if (retMenu == -1) {
            return 0; // Sai da partida e volta ao menu principal do sistema
        }
        p->pularAutoSave = 1;
        system("cls");
        goto repetirTurno;
    } else if (colChar1 == 'u' || colChar1 == 'U') {
        desfazer(p);
        system("cls");
        goto repetirTurno;
    } else if (colChar1 == 'r' || colChar1 == 'R') {
        refazer(p);
        system("cls");
        goto repetirTurno;
    }

    putchar(colChar1);
    lin1 = getche() - '0';
    col1 = converterColuna(colChar1);

    colChar2 = (char)getche();
    lin2 = getche() - '0';
    col2 = converterColuna(colChar2);

    if (getch() != '\r') {
        system("cls");
        p->flagErro = 1;
        p->pularAutoSave = 1;
        goto repetirTurno;
    }

    if (lin1 > 8 || lin1 < 1 || lin2 > 8 || lin2 < 1 || col1 == 0 || col2 == 0) {
        system("cls");
        p->flagErro = 1;
        p->pularAutoSave = 1;
        goto repetirTurno;
    }

    // Turno das Brancas
    if (p->vezJogador1) {
        int achou = 0;
        for (i = 0; i < QTD_PECAS; i++) {
            if (p->tabuleiro[lin1][col1] == PECAS_BRANCAS[i]) {
                peca = PECAS_BRANCAS[i];
                achou++;
                break;
            }
        }
        if (achou == 0) {
            system("cls");
            p->flagErro = 1;
            p->pularAutoSave = 1;
            goto repetirTurno;
        }

        for (i = 0; i < QTD_PECAS; i++) {
            if (p->tabuleiro[lin2][col2] == PECAS_BRANCAS[i]) {
                system("cls");
                p->flagErro = 1;
                p->pularAutoSave = 1;
                goto repetirTurno;
            }
        }

        int movValido = 0;
        if (peca == 'p' && peaoBranco(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'k' && rei(lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'q' && rainha(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'r' && torre(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'b' && bispo(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'n' && cavalo(lin1, col1, lin2, col2) == 0) movValido = 1;

        if (!movValido) {
            system("cls");
            p->flagErro = 1;
            p->pularAutoSave = 1;
            goto repetirTurno;
        }

        char orig = p->tabuleiro[lin1][col1];
        char dest = p->tabuleiro[lin2][col2];
        p->tabuleiro[lin2][col2] = orig;
        p->tabuleiro[lin1][col1] = ' ';

        int reiLinTeste = (peca == 'k') ? lin2 : p->posRei1Linha;
        int reiColTeste = (peca == 'k') ? col2 : p->posRei1Coluna;

        if (xequeBranco(p, reiLinTeste, reiColTeste) != 0) {
            p->tabuleiro[lin1][col1] = orig;
            p->tabuleiro[lin2][col2] = dest;
            system("cls");
            avisoRei = 1;
            p->pularAutoSave = 1;
            goto repetirTurno;
        }

        p->tabuleiro[lin1][col1] = orig;
        p->tabuleiro[lin2][col2] = dest;
        executarMovimento(p, lin1, col1, lin2, col2);

        if (peca == 'k') {
            p->posRei1Linha = lin2;
            p->posRei1Coluna = col2;
        } else if (peca == 'p' && lin2 == 8) {
            char promocao;
        promoverBranco:
            puts("\nPromover peao para (q/r/n/b) ===> ");
            promocao = (char)getche();
            if (promocao != 'q' && promocao != 'r' && promocao != 'n' && promocao != 'b') {
                printf("\nOpcao invalida!");
                goto promoverBranco;
            }
            p->tabuleiro[lin2][col2] = promocao;
            desenharTabuleiro(p);
        }

        p->vezJogador1 = 0;
        p->vezJogador2 = 1;
        system("cls");
        goto repetirTurno;
    }

    // Turno das Pretas
    if (p->vezJogador2) {
        int achou = 0;
        for (i = 0; i < QTD_PECAS; i++) {
            if (p->tabuleiro[lin1][col1] == PECAS_PRETAS[i]) {
                peca = PECAS_PRETAS[i];
                achou++;
                break;
            }
        }
        if (achou == 0) {
            system("cls");
            p->flagErro = 1;
            p->pularAutoSave = 1;
            goto repetirTurno;
        }

        for (i = 0; i < QTD_PECAS; i++) {
            if (p->tabuleiro[lin2][col2] == PECAS_PRETAS[i]) {
                system("cls");
                p->flagErro = 1;
                p->pularAutoSave = 1;
                goto repetirTurno;
            }
        }

        int movValido = 0;
        if (peca == 'P' && peaoPreto(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'K' && rei(lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'Q' && rainha(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'R' && torre(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'B' && bispo(p, lin1, col1, lin2, col2) == 0) movValido = 1;
        else if (peca == 'N' && cavalo(lin1, col1, lin2, col2) == 0) movValido = 1;

        if (!movValido) {
            system("cls");
            p->flagErro = 1;
            p->pularAutoSave = 1;
            goto repetirTurno;
        }

        char orig = p->tabuleiro[lin1][col1];
        char dest = p->tabuleiro[lin2][col2];
        p->tabuleiro[lin2][col2] = orig;
        p->tabuleiro[lin1][col1] = ' ';

        int reiLinTeste = (peca == 'K') ? lin2 : p->posRei2Linha;
        int reiColTeste = (peca == 'K') ? col2 : p->posRei2Coluna;

        if (xequePreto(p, reiLinTeste, reiColTeste) != 0) {
            p->tabuleiro[lin1][col1] = orig;
            p->tabuleiro[lin2][col2] = dest;
            system("cls");
            avisoRei = 1;
            p->pularAutoSave = 1;
            goto repetirTurno;
        }

        p->tabuleiro[lin1][col1] = orig;
        p->tabuleiro[lin2][col2] = dest;
        executarMovimento(p, lin1, col1, lin2, col2);

        if (peca == 'K') {
            p->posRei2Linha = lin2;
            p->posRei2Coluna = col2;
        } else if (peca == 'P' && lin2 == 1) {
            char promocao;
        promoverPreto:
            puts("\nPromover peao para (Q/R/N/B) ===> ");
            promocao = (char)getche();
            if (promocao != 'Q' && promocao != 'R' && promocao != 'N' && promocao != 'B') {
                printf("\nOpcao invalida!\n");
                goto promoverPreto;
            }
            p->tabuleiro[lin2][col2] = promocao;
            desenharTabuleiro(p);
        }

        p->vezJogador1 = 1;
        p->vezJogador2 = 0;
        system("cls");
        goto repetirTurno;
    }

    return 0;
}

// Regra de movimento do Peao Branco
int peaoBranco(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino) {
    if (linOrigem == 2) {
        if (linDestino == linOrigem + 1 && colDestino == colOrigem) {
            if (p->tabuleiro[linDestino][colDestino] == (char)219 || p->tabuleiro[linDestino][colDestino] == ' ')
                return 0;
        } else if (linDestino == linOrigem + 2 && colDestino == colOrigem) {
            if ((p->tabuleiro[linDestino][colDestino] == (char)219 || p->tabuleiro[linDestino][colDestino] == ' ') &&
                (p->tabuleiro[linDestino - 1][colDestino] == (char)219 || p->tabuleiro[linDestino - 1][colDestino] == ' '))
                return 0;
        } else if ((linDestino == linOrigem + 1 && colDestino == colOrigem + 1) ||
                   (linDestino == linOrigem + 1 && colDestino == colOrigem - 1)) {
            if (p->tabuleiro[linDestino][colDestino] != (char)219 && p->tabuleiro[linDestino][colDestino] != ' ')
                return 0;
        }
    } else {
        if (linDestino == linOrigem + 1 && colDestino == colOrigem) {
            if (p->tabuleiro[linDestino][colDestino] == (char)219 || p->tabuleiro[linDestino][colDestino] == ' ')
                return 0;
        } else if ((linDestino == linOrigem + 1 && colDestino == colOrigem + 1) ||
                   (linDestino == linOrigem + 1 && colDestino == colOrigem - 1)) {
            if (p->tabuleiro[linDestino][colDestino] != (char)219 && p->tabuleiro[linDestino][colDestino] != ' ')
                return 0;
        }
    }
    return 1;
}

// Regra de movimento do Peao Preto
int peaoPreto(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino) {
    if (linOrigem == 7) {
        if (linDestino == linOrigem - 1 && colDestino == colOrigem) {
            if (p->tabuleiro[linDestino][colDestino] == (char)219 || p->tabuleiro[linDestino][colDestino] == ' ')
                return 0;
        } else if (linDestino == linOrigem - 2 && colDestino == colOrigem) {
            if ((p->tabuleiro[linDestino][colDestino] == (char)219 || p->tabuleiro[linDestino][colDestino] == ' ') &&
                (p->tabuleiro[linDestino + 1][colDestino] == (char)219 || p->tabuleiro[linDestino + 1][colDestino] == ' '))
                return 0;
        } else if ((linDestino == linOrigem - 1 && colDestino == colOrigem + 1) ||
                   (linDestino == linOrigem - 1 && colDestino == colOrigem - 1)) {
            if (p->tabuleiro[linDestino][colDestino] != (char)219 && p->tabuleiro[linDestino][colDestino] != ' ')
                return 0;
        }
    } else {
        if (linDestino == linOrigem - 1 && colDestino == colOrigem) {
            if (p->tabuleiro[linDestino][colDestino] == (char)219 || p->tabuleiro[linDestino][colDestino] == ' ')
                return 0;
        } else if ((linDestino == linOrigem - 1 && colDestino == colOrigem + 1) ||
                   (linDestino == linOrigem - 1 && colDestino == colOrigem - 1)) {
            if (p->tabuleiro[linDestino][colDestino] != (char)219 && p->tabuleiro[linDestino][colDestino] != ' ')
                return 0;
        }
    }
    return 1;
}

// Regra de movimento do Cavalo
int cavalo(int linOrigem, int colOrigem, int linDestino, int colDestino) {
    if ((linDestino == linOrigem + 2 && colDestino == colOrigem + 1) ||
        (linDestino == linOrigem + 2 && colDestino == colOrigem - 1) ||
        (linDestino == linOrigem - 2 && colDestino == colOrigem + 1) ||
        (linDestino == linOrigem - 2 && colDestino == colOrigem - 1) ||
        (linDestino == linOrigem + 1 && colDestino == colOrigem + 2) ||
        (linDestino == linOrigem + 1 && colDestino == colOrigem - 2) ||
        (linDestino == linOrigem - 1 && colDestino == colOrigem + 2) ||
        (linDestino == linOrigem - 1 && colDestino == colOrigem - 2))
        return 0;

    return 1;
}

// Regra de movimento da Torre
int torre(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino) {
    int i;
    if (linDestino == linOrigem) {
        if (colDestino > colOrigem) {
            for (i = colOrigem + 1; i < colDestino; i++)
                if (p->tabuleiro[linOrigem][i] != (char)219 && p->tabuleiro[linOrigem][i] != ' ')
                    return 1;
        } else {
            for (i = colOrigem - 1; i > colDestino; i--)
                if (p->tabuleiro[linOrigem][i] != (char)219 && p->tabuleiro[linOrigem][i] != ' ')
                    return 1;
        }
    } else if (colDestino == colOrigem) {
        if (linDestino > linOrigem) {
            for (i = linOrigem + 1; i < linDestino; i++)
                if (p->tabuleiro[i][colOrigem] != (char)219 && p->tabuleiro[i][colOrigem] != ' ')
                    return 1;
        } else {
            for (i = linOrigem - 1; i > linDestino; i--)
                if (p->tabuleiro[i][colOrigem] != (char)219 && p->tabuleiro[i][colOrigem] != ' ')
                    return 1;
        }
    } else {
        return 1;
    }

    return 0;
}

// Regra de movimento do Bispo
int bispo(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino) {
    int i, j, valido = 0;
    if (linDestino > linOrigem && colDestino > colOrigem) {
        for (i = 1; i < 8; i++) {
            if (linDestino == linOrigem + i && colDestino == colOrigem + i) {
                valido = 1;
                for (j = 1; j < i; j++)
                    if (p->tabuleiro[linOrigem + j][colOrigem + j] != (char)219 && p->tabuleiro[linOrigem + j][colOrigem + j] != ' ')
                        return 1;
            }
        }
        if (valido == 0) return 1;
    } else if (linDestino > linOrigem && colDestino < colOrigem) {
        for (i = 1; i < 8; i++) {
            if (linDestino == linOrigem + i && colDestino == colOrigem - i) {
                valido = 1;
                for (j = 1; j < i; j++)
                    if (p->tabuleiro[linOrigem + j][colOrigem - j] != (char)219 && p->tabuleiro[linOrigem + j][colOrigem - j] != ' ')
                        return 1;
            }
        }
        if (valido == 0) return 1;
    } else if (linDestino < linOrigem && colDestino > colOrigem) {
        for (i = 1; i < 8; i++) {
            if (linDestino == linOrigem - i && colDestino == colOrigem + i) {
                valido = 1;
                for (j = 1; j < i; j++)
                    if (p->tabuleiro[linOrigem - j][colOrigem + j] != (char)219 && p->tabuleiro[linOrigem - j][colOrigem + j] != ' ')
                        return 1;
            }
        }
        if (valido == 0) return 1;
    } else if (linDestino < linOrigem && colDestino < colOrigem) {
        for (i = 1; i < 8; i++) {
            if (linDestino == linOrigem - i && colDestino == colOrigem - i) {
                valido = 1;
                for (j = 1; j < i; j++)
                    if (p->tabuleiro[linOrigem - j][colOrigem - j] != (char)219 && p->tabuleiro[linOrigem - j][colOrigem - j] != ' ')
                        return 1;
            }
        }
        if (valido == 0) return 1;
    } else {
        return 1;
    }

    return 0;
}

// Regra de movimento da Rainha (Torre + Bispo)
int rainha(const PartidaXadrez *p, int linOrigem, int colOrigem, int linDestino, int colDestino) {
    if (torre(p, linOrigem, colOrigem, linDestino, colDestino) == 0 ||
        bispo(p, linOrigem, colOrigem, linDestino, colDestino) == 0) {
        return 0;
    }
    return 1;
}

// Regra de movimento do Rei
int rei(int linOrigem, int colOrigem, int linDestino, int colDestino) {
    if ((linDestino == linOrigem + 1 && colDestino == colOrigem) ||
        (linDestino == linOrigem + 1 && colDestino == colOrigem + 1) ||
        (linDestino == linOrigem + 1 && colDestino == colOrigem - 1) ||
        (linDestino == linOrigem && colDestino == colOrigem + 1) ||
        (linDestino == linOrigem && colDestino == colOrigem - 1) ||
        (linDestino == linOrigem - 1 && colDestino == colOrigem) ||
        (linDestino == linOrigem - 1 && colDestino == colOrigem + 1) ||
        (linDestino == linOrigem - 1 && colDestino == colOrigem - 1))
        return 0;

    return 1;
}

// Verifica se o Rei Branco esta em xeque
int xequeBranco(const PartidaXadrez *p, int linRei, int colRei) {
    int i;
    for (i = 1; linRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei + i][colRei];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'K') return 1;
            if (c == 'Q' || c == 'R') return 1;
            if (c != 'k') break;
        }
    }
    for (i = 1; linRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei - i][colRei];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'K') return 1;
            if (c == 'Q' || c == 'R') return 1;
            if (c != 'k') break;
        }
    }
    for (i = 1; colRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei][colRei + i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'K') return 1;
            if (c == 'Q' || c == 'R') return 1;
            if (c != 'k') break;
        }
    }
    for (i = 1; colRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei][colRei - i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'K') return 1;
            if (c == 'Q' || c == 'R') return 1;
            if (c != 'k') break;
        }
    }
    for (i = 1; linRei + i <= 8 && colRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei + i][colRei + i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && (c == 'P' || c == 'K')) return 1;
            if (c == 'Q' || c == 'B') return 1;
            if (c != 'k') break;
        }
    }
    for (i = 1; linRei + i <= 8 && colRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei + i][colRei - i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && (c == 'P' || c == 'K')) return 1;
            if (c == 'Q' || c == 'B') return 1;
            if (c != 'k') break;
        }
    }
    for (i = 1; linRei - i >= 1 && colRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei - i][colRei + i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'K') return 1;
            if (c == 'Q' || c == 'B') return 1;
            if (c != 'k') break;
        }
    }
    for (i = 1; linRei - i >= 1 && colRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei - i][colRei - i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'K') return 1;
            if (c == 'Q' || c == 'B') return 1;
            if (c != 'k') break;
        }
    }

    int dLin[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dCol[8] = {1, -1, 1, -1, 2, -2, 2, -2};
    for (i = 0; i < 8; i++) {
        int nl = linRei + dLin[i];
        int nc = colRei + dCol[i];
        if (nl >= 1 && nl <= 8 && nc >= 1 && nc <= 8) {
            if (p->tabuleiro[nl][nc] == 'N')
                return 1;
        }
    }

    return 0;
}

// Efetua o movimento da peca e contabiliza eventual captura
void executarMovimento(PartidaXadrez *p, int lin1, int col1, int lin2, int col2) {
    if (p->tabuleiro[lin2][col2] != (char)219 && p->tabuleiro[lin2][col2] != ' ') {
        if (islower((unsigned char)p->tabuleiro[lin2][col2])) {
            p->capturadas1[p->qtdCapturadas1] = p->tabuleiro[lin2][col2];
            p->qtdCapturadas1++;
        } else {
            p->capturadas2[p->qtdCapturadas2] = p->tabuleiro[lin2][col2];
            p->qtdCapturadas2++;
        }
    }
    p->tabuleiro[lin2][col2] = p->tabuleiro[lin1][col1];
    p->tabuleiro[lin1][col1] = casaPadrao(lin1, col1);

    desenharTabuleiro(p);
}

// Verifica se o Rei Preto esta em xeque
int xequePreto(const PartidaXadrez *p, int linRei, int colRei) {
    int i;
    for (i = 1; linRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei + i][colRei];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'k') return 1;
            if (c == 'q' || c == 'r') return 1;
            if (c != 'K') break;
        }
    }
    for (i = 1; linRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei - i][colRei];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'k') return 1;
            if (c == 'q' || c == 'r') return 1;
            if (c != 'K') break;
        }
    }
    for (i = 1; colRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei][colRei + i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'k') return 1;
            if (c == 'q' || c == 'r') return 1;
            if (c != 'K') break;
        }
    }
    for (i = 1; colRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei][colRei - i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'k') return 1;
            if (c == 'q' || c == 'r') return 1;
            if (c != 'K') break;
        }
    }
    for (i = 1; linRei + i <= 8 && colRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei + i][colRei + i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'k') return 1;
            if (c == 'q' || c == 'b') return 1;
            if (c != 'K') break;
        }
    }
    for (i = 1; linRei + i <= 8 && colRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei + i][colRei - i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && c == 'k') return 1;
            if (c == 'q' || c == 'b') return 1;
            if (c != 'K') break;
        }
    }
    for (i = 1; linRei - i >= 1 && colRei + i <= 8; i++) {
        char c = p->tabuleiro[linRei - i][colRei + i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && (c == 'p' || c == 'k')) return 1;
            if (c == 'q' || c == 'b') return 1;
            if (c != 'K') break;
        }
    }
    for (i = 1; linRei - i >= 1 && colRei - i >= 1; i++) {
        char c = p->tabuleiro[linRei - i][colRei - i];
        if (c != (char)219 && c != ' ') {
            if (i == 1 && (c == 'p' || c == 'k')) return 1;
            if (c == 'q' || c == 'b') return 1;
            if (c != 'K') break;
        }
    }

    int dLin[8] = {2, 2, -2, -2, 1, 1, -1, -1};
    int dCol[8] = {1, -1, 1, -1, 2, -2, 2, -2};
    for (i = 0; i < 8; i++) {
        int nl = linRei + dLin[i];
        int nc = colRei + dCol[i];
        if (nl >= 1 && nl <= 8 && nc >= 1 && nc <= 8) {
            if (p->tabuleiro[nl][nc] == 'n')
                return 1;
        }
    }

    return 0;
}

// Verifica se o Rei Branco nao possui casas adjacentes seguras
int afogamentoBranco(const PartidaXadrez *p, int linRei, int colRei) {
    int d1, d2, d3, d4, d5, d6, d7, d8;

    d1 = (linRei + 1 > 8 || islower((unsigned char)p->tabuleiro[linRei + 1][colRei])) ? 1 : xequeBranco(p, linRei + 1, colRei);
    d2 = (linRei + 1 > 8 || colRei + 1 > 8 || islower((unsigned char)p->tabuleiro[linRei + 1][colRei + 1])) ? 1 : xequeBranco(p, linRei + 1, colRei + 1);
    d3 = (linRei + 1 > 8 || colRei - 1 < 1 || islower((unsigned char)p->tabuleiro[linRei + 1][colRei - 1])) ? 1 : xequeBranco(p, linRei + 1, colRei - 1);
    d4 = (colRei + 1 > 8 || islower((unsigned char)p->tabuleiro[linRei][colRei + 1])) ? 1 : xequeBranco(p, linRei, colRei + 1);
    d5 = (colRei - 1 < 1 || islower((unsigned char)p->tabuleiro[linRei][colRei - 1])) ? 1 : xequeBranco(p, linRei, colRei - 1);
    d6 = (linRei - 1 < 1 || islower((unsigned char)p->tabuleiro[linRei - 1][colRei])) ? 1 : xequeBranco(p, linRei - 1, colRei);
    d7 = (linRei - 1 < 1 || colRei + 1 > 8 || islower((unsigned char)p->tabuleiro[linRei - 1][colRei + 1])) ? 1 : xequeBranco(p, linRei - 1, colRei + 1);
    d8 = (linRei - 1 < 1 || colRei - 1 < 1 || islower((unsigned char)p->tabuleiro[linRei - 1][colRei - 1])) ? 1 : xequeBranco(p, linRei - 1, colRei - 1);

    return (d1 && d2 && d3 && d4 && d5 && d6 && d7 && d8) ? 1 : 0;
}

// Verifica se o Rei Preto nao possui casas adjacentes seguras
int afogamentoPreto(const PartidaXadrez *p, int linRei, int colRei) {
    int d1, d2, d3, d4, d5, d6, d7, d8;

    d1 = (linRei + 1 > 8 || isupper((unsigned char)p->tabuleiro[linRei + 1][colRei])) ? 1 : xequePreto(p, linRei + 1, colRei);
    d2 = (linRei + 1 > 8 || colRei + 1 > 8 || isupper((unsigned char)p->tabuleiro[linRei + 1][colRei + 1])) ? 1 : xequePreto(p, linRei + 1, colRei + 1);
    d3 = (linRei + 1 > 8 || colRei - 1 < 1 || isupper((unsigned char)p->tabuleiro[linRei + 1][colRei - 1])) ? 1 : xequePreto(p, linRei + 1, colRei - 1);
    d4 = (colRei + 1 > 8 || isupper((unsigned char)p->tabuleiro[linRei][colRei + 1])) ? 1 : xequePreto(p, linRei, colRei + 1);
    d5 = (colRei - 1 < 1 || isupper((unsigned char)p->tabuleiro[linRei][colRei - 1])) ? 1 : xequePreto(p, linRei, colRei - 1);
    d6 = (linRei - 1 < 1 || isupper((unsigned char)p->tabuleiro[linRei - 1][colRei])) ? 1 : xequePreto(p, linRei - 1, colRei);
    d7 = (linRei - 1 < 1 || colRei + 1 > 8 || isupper((unsigned char)p->tabuleiro[linRei - 1][colRei + 1])) ? 1 : xequePreto(p, linRei - 1, colRei + 1);
    d8 = (linRei - 1 < 1 || colRei - 1 < 1 || isupper((unsigned char)p->tabuleiro[linRei - 1][colRei - 1])) ? 1 : xequePreto(p, linRei - 1, colRei - 1);

    return (d1 && d2 && d3 && d4 && d5 && d6 && d7 && d8) ? 1 : 0;
}

// Verifica Xeque-Mate contra o Rei Branco
int xequeMateBranco(const PartidaXadrez *p, int linRei, int colRei) {
    return (afogamentoBranco(p, linRei, colRei) != 0 && xequeBranco(p, linRei, colRei) != 0) ? 1 : 0;
}

// Verifica Xeque-Mate contra o Rei Preto
int xequeMatePreto(const PartidaXadrez *p, int linRei, int colRei) {
    return (afogamentoPreto(p, linRei, colRei) != 0 && xequePreto(p, linRei, colRei) != 0) ? 1 : 0;
}

// Salva o estado da partida de xadrez em arquivos
void salvarJogoXadrez(PartidaXadrez *p) {
    int i = 0, j;
    static int numeroSaves = 1;
    char nomeSave[20];

    printf("Nome do save da partida: ");
    lerTexto(nomeSave, sizeof(nomeSave));
    while (nomeSave[0] == '\0') {
        printf("Digite um nome para o save: ");
        lerTexto(nomeSave, sizeof(nomeSave));
    }

    FILE *arqNomes = fopen("savename.txt", "a+");
    if (arqNomes != NULL) {
        fputs(nomeSave, arqNomes);
        fputs("\n", arqNomes);
        fclose(arqNomes);
    }

    FILE *arqCapturadas = fopen("outer.txt", "a+");
    if (arqCapturadas != NULL) {
        fprintf(arqCapturadas, "%d", numeroSaves++);
        while (p->capturadas1[i++] != '\0')
            fputc(p->capturadas1[i - 1], arqCapturadas);
        i = 0;
        while (p->capturadas2[i++] != '\0')
            fputc(p->capturadas2[i - 1], arqCapturadas);
        fclose(arqCapturadas);
    }

    FILE *arqTabuleiro = fopen("save_load.txt", "a+");
    if (arqTabuleiro != NULL) {
        for (i = 1; i < 9; i++)
            for (j = 1; j < 9; j++)
                fputc(p->tabuleiro[i][j], arqTabuleiro);
        fclose(arqTabuleiro);
    }

    FILE *arqTurno = fopen("turn.txt", "a+");
    if (arqTurno != NULL) {
        fprintf(arqTurno, "%d%d%d%d%d%d",
                p->vezJogador1, p->vezJogador2,
                p->posRei1Linha, p->posRei1Coluna,
                p->posRei2Linha, p->posRei2Coluna);
        fclose(arqTurno);
    }

    system("cls");
}

// Carrega uma partida de xadrez salva anteriormente
void carregarJogoXadrez(PartidaXadrez *p) {
    int i, j, escolha = 0, valido = 0, tamTemp = 0;
    int numeroSaves = 0;
    int ch;
    char nomeSave[20];
    char temp[200] = {0};

    FILE *arqNomes = fopen("savename.txt", "r");
    if (arqNomes != NULL) {
        for (i = 1; fgets(nomeSave, sizeof(nomeSave), arqNomes) != NULL; i++) {
            printf("%d) %s", i, nomeSave);
            numeroSaves++;
        }
        fclose(arqNomes);
    }

    if (numeroSaves == 0) {
        return;
    }

    printf("\nEscolha o jogo salvo:\n");
    while (valido != 1) {
        escolha = lerInteiroValido("====> ", 0);
        if (escolha >= 1 && escolha <= numeroSaves) {
            valido = 1;
        } else {
            printf("Opcao invalida!\n");
        }
    }

    FILE *arqCapturadas = fopen("outer.txt", "r");
    if (arqCapturadas != NULL) {
        i = 0;
        while ((ch = fgetc(arqCapturadas)) != EOF && i < (int)sizeof(temp) - 1) {
            temp[i++] = (char)ch;
            tamTemp++;
        }
        p->qtdCapturadas1 = 0;
        p->qtdCapturadas2 = 0;
        for (i = 0; i < tamTemp; i++) {
            if ((int)temp[i] == 48 + escolha) {
                for (j = i + 1; j < tamTemp; j++) {
                    if (48 + (escolha + 1) == (int)temp[j])
                        break;
                    if (islower((unsigned char)temp[j])) {
                        p->capturadas1[p->qtdCapturadas1++] = temp[j];
                    } else if (isupper((unsigned char)temp[j])) {
                        p->capturadas2[p->qtdCapturadas2++] = temp[j];
                    }
                }
                break;
            }
        }
        fclose(arqCapturadas);
    }

    FILE *arqTabuleiro = fopen("save_load.txt", "r");
    system("cls");
    if (arqTabuleiro != NULL) {
        fseek(arqTabuleiro, (escolha - 1) * 64, SEEK_SET);
        for (i = 1; i < 9; i++)
            for (j = 1; j < 9; j++)
                p->tabuleiro[i][j] = (char)getc(arqTabuleiro);
        fclose(arqTabuleiro);
    }

    FILE *arqTurno = fopen("turn.txt", "r");
    if (arqTurno != NULL) {
        fseek(arqTurno, (escolha - 1) * 6, SEEK_SET);
        p->vezJogador1 = (int)(fgetc(arqTurno) - 48);
        p->vezJogador2 = (int)(fgetc(arqTurno) - 48);
        p->posRei1Linha = (int)(fgetc(arqTurno) - 48);
        p->posRei1Coluna = (int)(fgetc(arqTurno) - 48);
        p->posRei2Linha = (int)(fgetc(arqTurno) - 48);
        p->posRei2Coluna = (int)(fgetc(arqTurno) - 48);
        fclose(arqTurno);
    }

    strcpy(p->nomeJogador1, "Jogador 1");
    strcpy(p->nomeJogador2, "Jogador 2");
}

// Salva o estado do turno na memoria para Desfazer/Refazer
void salvarAutomatico(PartidaXadrez *p) {
    int j, k;
    if (p->contHistorico >= 50)
        return;

    int idx = p->contHistorico;
    for (j = 0; j < 8; j++)
        for (k = 0; k < 8; k++)
            p->histTabuleiro[j][k][idx] = p->tabuleiro[j + 1][k + 1];

    for (j = 0; j <= (p->qtdCapturadas1 / 8); j++)
        for (k = 0; k < 8; k++)
            p->histDados[j][k][idx] = p->capturadas1[j * 8 + k];

    for (j = 2; j <= (2 + (p->qtdCapturadas2 / 8)); j++)
        for (k = 0; k < 8; k++)
            p->histDados[j][k][idx] = p->capturadas2[(j - 2) * 8 + k];

    p->histDados[4][0][idx] = (char)p->vezJogador1;
    p->histDados[4][1][idx] = (char)p->vezJogador2;
    p->histDados[4][2][idx] = (char)p->posRei1Linha;
    p->histDados[4][3][idx] = (char)p->posRei1Coluna;
    p->histDados[4][4][idx] = (char)p->posRei2Linha;
    p->histDados[4][5][idx] = (char)p->posRei2Coluna;
    p->histDados[4][6][idx] = (char)p->qtdCapturadas1;
    p->histDados[4][7][idx] = (char)p->qtdCapturadas2;

    p->contHistorico++;
    if (p->contHistorico > p->maxRefazer)
        p->maxRefazer = p->contHistorico;
}

// Desfaz a ultima jogada no tabuleiro (tecla U)
void desfazer(PartidaXadrez *p) {
    if (p->contHistorico - 2 >= 0) {
        int j, k;
        int idx = p->contHistorico - 2;

        for (j = 0; j < 8; j++)
            for (k = 0; k < 8; k++)
                p->tabuleiro[j + 1][k + 1] = p->histTabuleiro[j][k][idx];

        p->qtdCapturadas1 = (int)p->histDados[4][6][idx];
        p->qtdCapturadas2 = (int)p->histDados[4][7][idx];

        for (j = 0; j <= (p->qtdCapturadas1 / 8); j++)
            for (k = 0; k < 8; k++)
                p->capturadas1[j * 8 + k] = p->histDados[j][k][idx];

        for (j = 2; j <= (2 + (p->qtdCapturadas2 / 8)); j++)
            for (k = 0; k < 8; k++)
                p->capturadas2[(j - 2) * 8 + k] = p->histDados[j][k][idx];

        p->vezJogador1 = (int)p->histDados[4][0][idx];
        p->vezJogador2 = (int)p->histDados[4][1][idx];
        p->posRei1Linha = (int)p->histDados[4][2][idx];
        p->posRei1Coluna = (int)p->histDados[4][3][idx];
        p->posRei2Linha = (int)p->histDados[4][4][idx];
        p->posRei2Coluna = (int)p->histDados[4][5][idx];

        p->contHistorico -= 2;
    } else {
        p->pularAutoSave = 1;
    }
}

// Refaz uma jogada desfeita no tabuleiro (tecla R)
void refazer(PartidaXadrez *p) {
    if (p->contHistorico < p->maxRefazer) {
        int j, k;
        int idx = p->contHistorico;

        for (j = 0; j < 8; j++)
            for (k = 0; k < 8; k++)
                p->tabuleiro[j + 1][k + 1] = p->histTabuleiro[j][k][idx];

        p->qtdCapturadas1 = (int)p->histDados[4][6][idx];
        p->qtdCapturadas2 = (int)p->histDados[4][7][idx];

        for (j = 0; j <= (p->qtdCapturadas1 / 8); j++)
            for (k = 0; k < 8; k++)
                p->capturadas1[j * 8 + k] = p->histDados[j][k][idx];

        for (j = 2; j <= (2 + (p->qtdCapturadas2 / 8)); j++)
            for (k = 0; k < 8; k++)
                p->capturadas2[(j - 2) * 8 + k] = p->histDados[j][k][idx];

        p->vezJogador1 = (int)p->histDados[4][0][idx];
        p->vezJogador2 = (int)p->histDados[4][1][idx];
        p->posRei1Linha = (int)p->histDados[4][2][idx];
        p->posRei1Coluna = (int)p->histDados[4][3][idx];
        p->posRei2Linha = (int)p->histDados[4][4][idx];
        p->posRei2Coluna = (int)p->histDados[4][5][idx];
    } else {
        p->pularAutoSave = 1;
    }
}
