#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int codigo;
    char descricao[50];
    int quantidade;
    float valor;
} Produto;

typedef struct Node {
    Produto produto;
    struct Node *prox;
} Node;

Node* inicializarLista() {
    return NULL;
}

Node* adicionarProduto(Node *lista) {
    Node *novoProduto = (Node*)malloc(sizeof(Node));

    printf("Informe o código do produto: ");
    scanf("%d", &novoProduto->produto.codigo);
    printf("Informe a descrição do produto: ");
    scanf("%s", novoProduto->produto.descricao);
    printf("Informe a quantidade do produto: ");
    scanf("%d", &novoProduto->produto.quantidade);
    printf("Informe o valor do produto: ");
    scanf("%f", &novoProduto->produto.valor);

    novoProduto->prox = lista;

    printf("Produto cadastrado com sucesso!\n");

    return novoProduto;
}

void imprimirRelatorio(Node *lista) {
    Node *atual = lista;

    if (atual == NULL) {
        printf("Estoque vazio.\n");
        return;
    }

    printf("\nRelatório de Produtos:\n");
    printf("-------------------------------------------------\n");
    printf("| Código | Descrição           | Quantidade | Valor |\n");
    printf("-------------------------------------------------\n");

    while (atual != NULL) {
        printf("| %-6d | %-20s | %-10d | %-5.2f |\n",
               atual->produto.codigo, atual->produto.descricao,
               atual->produto.quantidade, atual->produto.valor);
        atual = atual->prox;
    }

    printf("-------------------------------------------------\n");
}

void pesquisarProduto(Node *lista) {
    int codigo;
    printf("Informe o código do produto a ser pesquisado: ");
    scanf("%d", &codigo);

    Node *atual = lista;

    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            printf("\nProduto encontrado:\n");
            printf("Código: %d\n", atual->produto.codigo);
            printf("Descrição: %s\n", atual->produto.descricao);
            printf("Quantidade: %d\n", atual->produto.quantidade);
            printf("Valor: %.2f\n", atual->produto.valor);
            return;
        }
        atual = atual->prox;
    }

    printf("Produto não encontrado.\n");
}

Node* removerProduto(Node *lista) {
    int codigo;
    printf("Informe o código do produto a ser removido: ");
    scanf("%d", &codigo);

    Node *anterior = NULL;
    Node *atual = lista;

    while (atual != NULL) {
        if (atual->produto.codigo == codigo) {
            if (anterior == NULL) {
                Node *temp = atual->prox;
                free(atual);
                printf("Produto removido com sucesso!\n");
                return temp;
            } else {
                anterior->prox = atual->prox;
                free(atual);
                printf("Produto removido com sucesso!\n");
                return lista;
            }
        }
        anterior = atual;
        atual = atual->prox;
    }

    printf("Produto não encontrado.\n");
    return lista;
}

void liberarLista(Node *lista) {
    Node *atual = lista;
    Node *proximo;

    while (atual != NULL) {
        proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
}

int main() {
    Node *estoque = inicializarLista();
    int opcao;

    do {
        printf("\nMenu:\n");
        printf("1. Cadastrar Produto\n");
        printf("2. Consultar Produtos\n");
        printf("3. Gerar Relatório\n");
        printf("4. Remover Produto\n");
        printf("0. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                estoque = adicionarProduto(estoque);
                break;
            case 2:
                pesquisarProduto(estoque);
                break;
            case 3:
                imprimirRelatorio(estoque);
                break;
            case 4:
                estoque = removerProduto(estoque);
                break;
            case 0:
                liberarLista(estoque);
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção inválida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
