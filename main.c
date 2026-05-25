#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LIVROS 100

// Definicao da struct sem o uso de typedef
struct Livro {
    int codigo;
    char titulo[100];
    int ano;
    int quantidade;
};

// Funcao para ler o arquivo texto no inicio da execucao
int carregar_livros(struct Livro livros[], const char *nome_arquivo) {
    FILE *arquivo = fopen(nome_arquivo, "r");
    if (arquivo == NULL) {
        printf("Erro: Nao foi possivel abrir o arquivo %s.\n", nome_arquivo);
        return 0;
    }

    int total = 0;
    // Le os dados respeitando o formato: codigo, titulo (sem espacos), ano e quantidade
    while (total < MAX_LIVROS && fscanf(arquivo, "%d %s %d %d",
           &livros[total].codigo,
           livros[total].titulo,
           &livros[total].ano,
           &livros[total].quantidade) == 4) {
        total++;
    }

    fclose(arquivo);
    return total;
}

// Opcao 1: Adicionar novo livro
void adicionar_livro(struct Livro livros[], int *total) {
    if (*total >= MAX_LIVROS) {
        printf("Capacidade maxima do vetor alcancada!\n");
        return;
    }
    
    int novo_codigo;
    printf("\n--- Adicionar Livro ---\n");
    printf("Codigo: ");
    scanf("%d", &novo_codigo);

    // Verificacao de codigo duplicado
    for (int i = 0; i < *total; i++) {
        if (livros[i].codigo == novo_codigo) {
            printf("Erro: Ja existe um livro cadastrado com o codigo %d!\n", novo_codigo);
            return; // Encerra a funcao sem adicionar o livro
        }
    }

    // Se o codigo for unico, salva e continua pedindo o resto dos dados
    livros[*total].codigo = novo_codigo;
    printf("Titulo (sem espacos): ");
    scanf("%s", livros[*total].titulo);
    printf("Ano de publicacao: ");
    scanf("%d", &livros[*total].ano);
    printf("Quantidade: ");
    scanf("%d", &livros[*total].quantidade);

    (*total)++;
    printf("Livro adicionado com sucesso!\n");
}

// Opcao 2: Busca sequencial (linear) por codigo
void buscar_livro(struct Livro livros[], int total) {
    int codigo_busca;
    printf("\nDigite o codigo do livro para busca: ");
    scanf("%d", &codigo_busca);

    for (int i = 0; i < total; i++) {
        if (livros[i].codigo == codigo_busca) {
            printf("\nLivro Encontrado:\n");
            printf("Titulo: %s | Ano: %d | Quantidade: %d\n",
                   livros[i].titulo, livros[i].ano, livros[i].quantidade);
            return;
        }
    }
    printf("Livro com codigo %d nao encontrado.\n", codigo_busca);
}

// Opcao 3: Imprimir todos os livros no formato atual
void imprimir_livros(struct Livro livros[], int total) {
    printf("\n--- Lista de Livros ---\n");
    for (int i = 0; i < total; i++) {
        printf("Cod: %d | Titulo: %s | Ano: %d | Qtd: %d\n",
               livros[i].codigo, livros[i].titulo, livros[i].ano, livros[i].quantidade);
    }
}

// Opcao 4: Algoritmo de ordenacao (Bubble Sort) por ano
void ordenar_e_imprimir(struct Livro livros[], int total) {
    // Cria uma copia temporaria do vetor para nao alterar a ordem original de insercao
    struct Livro copia[MAX_LIVROS];
    for (int i = 0; i < total; i++) {
        copia[i] = livros[i];
    }

    // Ordenacao (Bubble Sort)
    for (int i = 0; i < total - 1; i++) {
        for (int j = 0; j < total - i - 1; j++) {
            if (copia[j].ano > copia[j+1].ano) {
                struct Livro temp = copia[j];
                copia[j] = copia[j+1];
                copia[j+1] = temp;
            }
        }
    }

    printf("\n--- Livros Ordenados por Ano ---\n");
    for (int i = 0; i < total; i++) {
        printf("Ano: %d | Cod: %d | Titulo: %s | Qtd: %d\n",
               copia[i].ano, copia[i].codigo, copia[i].titulo, copia[i].quantidade);
    }
}

int main() {
    struct Livro livros[MAX_LIVROS];
    
    // Carrega o arquivo contendo os 20 registros iniciais
    int total_livros = carregar_livros(livros, "livros.txt");

    // Inicializando a variavel para garantir a entrada no laco while
    int opcao = 0;
    
    // Substituicao do do-while por um laco while simples
    while (opcao != 5) {
        printf("\n============================\n");
        printf("  CONTROLE DE LIVROS\n");
        printf("============================\n");
        printf("1. Adicionar livro\n");
        printf("2. Buscar livro por codigo\n");
        printf("3. Imprimir livros\n");
        printf("4. Ordenar por ano e imprimir\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        // Estrutura de decisao usando apenas if e else if
        if (opcao == 1) {
            adicionar_livro(livros, &total_livros);
        } 
        else if (opcao == 2) {
            buscar_livro(livros, total_livros);
        } 
        else if (opcao == 3) {
            imprimir_livros(livros, total_livros);
        } 
        else if (opcao == 4) {
            ordenar_e_imprimir(livros, total_livros);
        } 
        else if (opcao == 5) {
            printf("Saindo do programa...\n");
        } 
        else {
            printf("Opcao invalida! Tente novamente.\n");
        }
    }

    return 0;
}