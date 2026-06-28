#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int codigo;
    char nome[50];
    float preco;
    int quantidade;
} Produto;

void cadastrarProduto(FILE *arquivo) {
    int voltar;
    do {
        system("clear");
        Produto p;

        printf("\n===== CADASTRO DE PRODUTO =====\n");

        printf("Digite o codigo do produto: ");
        scanf("%d", &p.codigo);

        getchar();  // Limpa o buffer
        printf("Nome do produto: ");
        fgets(p.nome, sizeof(p.nome), stdin);
        p.nome[strcspn(p.nome, "\n")] = '\0';

        printf("Preco: ");
        scanf("%f", &p.preco);

        printf("Quantidade em estoque: ");
        scanf("%d", &p.quantidade);

        fseek(arquivo, 0, SEEK_END);
        fwrite(&p, sizeof(Produto), 1, arquivo);

        printf("\nProduto cadastrado com sucesso!");

        printf("\n\nDigite 0 para voltar ao menu: ");
        scanf("%d", &voltar);
    } while(voltar != 0);
}

void listarProdutos(FILE *arquivo) {
    int voltar;
    do {
        system("clear");
        Produto p;
        rewind(arquivo);  // Volta para o início do arquivo

        printf("\n===== LISTA DE PRODUTOS =====\n");

        int encontrou = 0;
        while(fread(&p, sizeof(Produto), 1, arquivo) == 1) {
            printf("\nCodigo: %d\n", p.codigo);
            printf("Nome: %s\n", p.nome);
            printf("Preco: %.2f\n", p.preco);
            printf("Quantidade: %d\n", p.quantidade);
            encontrou = 1;
        }

        if(!encontrou) {
            printf("\nNenhum produto cadastrado.\n");
        }

        printf("\nDigite 0 para voltar ao menu: ");
        scanf("%d", &voltar);
    } while(voltar != 0);
}

void alterarPreco(FILE *arquivo) {
    int voltar;
    do {
        system("clear");
        int codigoBusca;
        Produto p;
        int encontrado = 0;

        printf("\n===== ALTERAR PREÇO DE PRODUTO =====\n");
        printf("Digite o codigo do produto que deseja alterar o preco: ");
        scanf("%d", &codigoBusca);

        rewind(arquivo);

        while(fread(&p, sizeof(Produto), 1, arquivo) == 1) {
            if(p.codigo == codigoBusca) {
                printf("\nProduto encontrado: %s (Preco atual: %.2f)\n", p.nome, p.preco);

                printf("Digite o novo preco: ");
                scanf("%f", &p.preco);

                fseek(arquivo, -sizeof(Produto), SEEK_CUR);
                fwrite(&p, sizeof(Produto), 1, arquivo);

                printf("\nPreco atualizado com sucesso!");
                encontrado = 1;
                break;
            }
        }

        if(!encontrado) {
            printf("\nProduto com codigo %d nao encontrado.\n", codigoBusca);
        }

        printf("\n\nDigite 0 para voltar ao menu: ");
        scanf("%d", &voltar);
    } while(voltar != 0);
}

void resetarArquivo(FILE **arquivo) {
    fclose(*arquivo);
    *arquivo = fopen("produtos.bin", "wb+");
    if (*arquivo == NULL) {
        printf("\nErro ao recriar o arquivo!\n");
        exit(1);
    }
    printf("\nArquivo resetado com sucesso (todos os produtos foram apagados)!\n");
    printf("\nPressione Enter para voltar ao menu...");
    getchar(); getchar();
}

int main() {
    FILE *arquivo;
    int opcao;

    arquivo = fopen("produtos.bin", "rb+");

    if(arquivo == NULL) {
        arquivo = fopen("produtos.bin", "wb+");
        if(arquivo == NULL) {
            printf("Erro ao criar o arquivo!\n");
            return 1;
        }
    }

    do {
        system("clear");
        printf("\n===== MENU =====\n");
        printf("1 - Cadastrar produto\n");
        printf("2 - Listar produtos\n");
        printf("3 - Alterar preco de um produto\n");
        printf("4 - Resetar arquivo (apagar todos os produtos)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1:
                cadastrarProduto(arquivo);
                break;
            case 2:
                listarProdutos(arquivo);
                break;
            case 3:
                alterarPreco(arquivo);
                break;
            case 4:
                resetarArquivo(&arquivo);
                break;
            case 0:
                printf("\nEncerrando o programa...\n");
                break;
            default:
                printf("\nOpcao invalida!\n");
        }

        fflush(arquivo);

    } while(opcao != 0);

    fclose(arquivo);
    return 0;
}
