#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QTD_DADOS_EXTRATO 10
#define TRUE 1
#define FALSE 0

typedef struct Extrato
{
    float valor;
    char tipo[40];
} EXTRATO;

typedef struct Conta
{
    char nome[51];
    char cpf[13];
    float quantia;
    char senha[21];
    EXTRATO extrato[10];
} CONTA;

typedef struct Nodo
{
    struct Nodo *pAnt;
    struct Nodo *pProx;
    CONTA *pConta;
} NODO;

NODO *pInicio = NULL;
NODO *pFim = NULL;
NODO *pAtual = NULL;

void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

void insereNaLista(NODO *pNodo)
{
    if (pInicio == NULL)
    {
        pInicio = pNodo;
        pFim = pNodo;
        pNodo->pProx = NULL;
        pNodo->pAnt = NULL;
    }
    else
    {
        pFim->pProx = pNodo;
        pNodo->pAnt = pFim;
        pNodo->pProx = NULL;
        pFim = pNodo;
    }
}

void limpar_newline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

void cadastraConta()
{
    system("clear");

    CONTA *pNovaConta;
    NODO *pNovoNodo;

    pNovaConta = malloc(sizeof(CONTA));
    pNovoNodo = malloc(sizeof(NODO));

    puts("Digite o nome do dono da conta: ");
    fgets(pNovaConta->nome, sizeof(pNovaConta->nome), stdin);
    limpar_newline(pNovaConta->nome);
    //pNovaConta->nome[strcspn(pNovaConta->nome, "\n")] = 0;

    puts("Digite o CPF do dono da conta: ");
    fgets(pNovaConta->cpf, sizeof(pNovaConta->cpf), stdin);
    limpar_newline(pNovaConta->cpf);
    //pNovaConta->cpf[strcspn(pNovaConta->cpf, "\n")] = 0;

    puts("Digite a senha: ");
    fgets(pNovaConta->senha, sizeof(pNovaConta->senha), stdin);
    limpar_newline(pNovaConta->senha);
    //pNovaConta->senha[strcspn(pNovaConta->senha, "\n")] = 0;

    pNovaConta->quantia = 0.0;
    pNovoNodo->pConta = pNovaConta;

    insereNaLista(pNovoNodo);
}

void imprimeLista(void)
{
    system("clear");
    pAtual = pInicio;

    while (pAtual != NULL)
    {
        printf("\nNome: %s, CPF: %s, senha: %s, quantia depositada: R$%.2f", 
            pAtual->pConta->nome, 
            pAtual->pConta->cpf,
            pAtual->pConta->senha, 
            pAtual->pConta->quantia);
        pAtual = pAtual->pProx;
    }

    puts("\nDigite qualquer tecla para continuar.");
    getchar();
}

void limpaMemoria(void)
{
    pAtual = pInicio;
    while (pAtual != NULL)
    {
        NODO *pTemp = pAtual->pProx;
        free(pAtual->pConta);
        free(pAtual);
        pAtual = pTemp;
    }
}

void salvaNoArquivo(void)
{
    FILE *fp;
    fp = fopen("contas.bin", "wb");

    pAtual = pInicio;
    while (pAtual != NULL)
    {
        fwrite(pAtual->pConta, sizeof(CONTA), 1, fp);
        pAtual = pAtual->pProx;
    }

    fclose(fp);
}

void leDoArquivo(void)
{
    FILE *fp;
    fp = fopen("contas.bin", "rb");

    if(fp == NULL){
        return;
    }

    CONTA *pNovaConta;
    NODO *pNovoNodo;

    while (1)
    {
        pNovaConta = malloc(sizeof(CONTA));
        pNovoNodo = malloc(sizeof(NODO));

        pNovoNodo->pConta = pNovaConta;

        if (fread(pNovaConta, sizeof(CONTA), 1, fp) == 0)
        {
            break;
        }

        insereNaLista(pNovoNodo);
    }

    fclose(fp);
}

deletaConta(void)
{
    if (pAtual == NULL)
    {
        return;
    }
    
    if (pAtual->pAnt != NULL)
    {
        pAtual->pAnt->pProx = pAtual->pProx;
    }
    else
    {
        pInicio = pAtual->pProx;
    }
    if (pAtual->pProx != NULL)
    {
        pAtual->pProx->pAnt = pAtual->pAnt;
    }
    

    /*
    if (pAtual == pInicio && pAtual == pFim)
    {
        free(pAtual->pConta);
        free(pAtual);
        pInicio = NULL;
        pAtual = NULL;
        pFim = NULL;
    }
    else if (pAtual == pFim && pAtual != pInicio)
    {
        pAtual->pAnt->pProx = NULL;
        free(pAtual->pConta);
        free(pAtual);
        pAtual = NULL;
    }
    else if (pAtual == pInicio)
    {
        pAtual->pProx->pAnt = NULL;
        free(pAtual->pConta);
        free(pAtual);
        pAtual = NULL;
    }
    else if (pAtual->pProx != NULL && pAtual->pAnt != NULL)
    {
        pAtual->pAnt->pProx = pAtual->pProx;
        pAtual->pProx->pAnt = pAtual->pAnt;
        free(pAtual->pConta);
        free(pAtual);
        pAtual = NULL;
    }*/
}

void insereNoExtrato(EXTRATO extrato, NODO* pConta)
{
    for (int i = QTD_DADOS_EXTRATO - 1; i >= 0; i--)
    {
        if (pConta->pConta->extrato[i - 1].valor != 0)
        {
            pConta->pConta->extrato[i] = pConta->pConta->extrato[i - 1];
        }
    }
    pConta->pConta->extrato[0] = extrato;
}

void depositar(void)
{
    pAtual = pInicio;
    system("clear");
    char busca[13];

    puts("Digite o CPF da conta");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    unsigned short int encontrado = FALSE;

    while (pAtual != NULL)
    {
        if (strcmp(pAtual->pConta->cpf, busca) == 0)
        {
            encontrado = TRUE;
            break;
        }
        pAtual = pAtual->pProx;
    }

    if (encontrado == FALSE)
    {
        puts("Conta nao encontrada!");
        return;
    }

    char senha[21];
    puts("Digite a senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if (strcmp(pAtual->pConta->senha, senha) != 0)
    {
        puts("Senha incorreta! Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }

    float valor;
    puts("Digite o valor a ser depositado: ");
    scanf("%f", &valor);
    pAtual->pConta->quantia += valor;
    EXTRATO extrato = {valor, "Depositado pelo banco"};
    insereNoExtrato(extrato, pAtual);
}

void sacar(void)
{
    pAtual = pInicio;
    system("clear");
    char busca[13];

    puts("Digite o CPF da conta");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    unsigned short int encontrado = FALSE;

    while (pAtual != NULL)
    {
        if (strcmp(pAtual->pConta->cpf, busca) == 0)
        {
            encontrado = TRUE;
            break;
        }
        pAtual = pAtual->pProx;
    }

    if (encontrado == FALSE)
    {
        puts("Conta nao encontrada!");
        return;
    }

    char senha[21];
    puts("Digite a senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if (strcmp(pAtual->pConta->senha, senha) != 0)
    {
        puts("Senha incorreta! Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }

    float valor;
    puts("Digite o valor a ser sacado: ");
    scanf("%f", &valor);
    limparBuffer();

    if (pAtual->pConta->quantia < valor)
    {
        puts("\nEssa conta não tem dinheiro suficiente para sacar esse valor!");
        puts("Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }
    pAtual->pConta->quantia -= valor;
    EXTRATO extrato = {-valor, "Retirado pelo banco"};
    insereNoExtrato(extrato, pAtual);
}

void transferir(void)
{
    NODO *pOrigem;
    pAtual = pInicio;
    system("clear");
    char busca[13];

    puts("Digite o CPF da conta de origem");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    unsigned short int encontrado = FALSE;

    while (pAtual != NULL)
    {
        if (strcmp(pAtual->pConta->cpf, busca) == 0)
        {
            encontrado = TRUE;
            break;
        }
        pAtual = pAtual->pProx;
    }

    if (encontrado == FALSE)
    {
        puts("Conta de origem nao encontrada! Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }

    pOrigem = pAtual;
    char senha[21];
    puts("Digite a senha: ");
    fgets(senha, sizeof(senha), stdin);
    senha[strcspn(senha, "\n")] = '\0';

    if (strcmp(pOrigem->pConta->senha, senha) != 0)
    {
        puts("Senha incorreta! Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }

    NODO *pDestino;
    pAtual = pInicio;
    encontrado = FALSE;
    puts("Digite o CPF da conta de destino: ");
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    while (pAtual != NULL)
    {
        if (strcmp(pAtual->pConta->cpf, busca) == 0)
        {
            encontrado = TRUE;
            break;
        }
        pAtual = pAtual->pProx;
    }

    if (encontrado == FALSE)
    {
        puts("Conta de destino nao encontrada! Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }

    pDestino = pAtual;
    float valor;
    puts("Digite o valor a ser transferido: ");
    scanf("%f", &valor);
    limparBuffer();

    if (pOrigem->pConta->quantia < valor)
    {
        puts("\nEssa conta não tem dinheiro suficiente para sacar esse valor!");
        puts("Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }
    pOrigem->pConta->quantia -= valor;
    char descricao1[100];
    sprintf(descricao1, "Transferido pelo banco para %s", pOrigem->pConta->cpf);
    EXTRATO extratoOrigem = {-valor, ""};
    strcpy(extratoOrigem.tipo, descricao1);
    insereNoExtrato(extratoOrigem, pOrigem);

    pDestino->pConta->quantia += valor;
    char descricao2[100];
    sprintf(descricao2, "Transferido pelo banco de %s", pDestino->pConta->cpf);
    EXTRATO extratoDestino = {valor, ""};
    strcpy(extratoDestino.tipo, descricao2);
    insereNoExtrato(extratoDestino, pDestino);
}

void deletar(void){
    system("clear");
    puts("Digite o CPF da conta a ser apagada.");
    char busca[13];
    unsigned short int encontrado = FALSE;
    fgets(busca, sizeof(busca), stdin);
    busca[strcspn(busca, "\n")] = '\0';

    pAtual = pInicio;

    while (pAtual != NULL)
    {
        if (strcmp(pAtual->pConta->cpf, busca) == 0)
        {
            encontrado = TRUE;
            break;
        }
        pAtual = pAtual->pProx;
    }

    if (encontrado == FALSE)
    {
        puts("Conta de destino nao encontrada! Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }

    deletaConta();
}

void menu(void)
{
    while (1)
    {
        system("clear");
        puts("BANCO CATUPIROLA");
        puts("\n1 - Cadastrar conta");
        puts("2 - Listar contas");
        puts("3 - Depositar");
        puts("4 - Sacar");
        puts("5 - Transferir");
        puts("6 - Deletar conta");
        puts("7 - Sair");
        puts("\nDigite a opcao desejada: ");

        unsigned short int opcao = 0;
        scanf("%d", &opcao);

        limparBuffer();

        switch (opcao)
        {
        case 1:
            cadastraConta();
            break;

        case 2:
            imprimeLista();
            break;

        case 3:
            depositar();
            break;

        case 4:
            sacar();
            break;

        case 5:
            transferir();
            break;

        case 6:
            deletar();
            break;

        case 7:
            salvaNoArquivo();
            limpaMemoria();
            exit(0);
            break;

        default:
            printf("\nOpcao invalida!");
            break;
        }
    }
}

int main(void)
{
    leDoArquivo();
    menu();

    return 0;
}
