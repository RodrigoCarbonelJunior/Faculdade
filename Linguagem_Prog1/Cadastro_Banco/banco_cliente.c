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
    char nome[50];
    char cpf[11];
    float quantia;
    char senha[20];
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
NODO *pNodoContaLogada = NULL;

void limparBuffer(void)
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
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

    if (fp == NULL)
    {
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

void insereNoExtrato(EXTRATO extrato, NODO *pContaDestino)
{
    //loop que comeca no fim da lista e vai ao inicio
    for (int i = QTD_DADOS_EXTRATO - 1; i >= 0; i--)
    {
        //se extrato[i].valor for igual a 0, isso significa que aquela posicao nao tem nenhum dado
        if (pContaDestino->pConta->extrato[i - 1].valor != 0)
        {
            //o extrato atual recebe o extrato anterior a ele, entao a lista toda move uma posicao pra frente
            pContaDestino->pConta->extrato[i] = pContaDestino->pConta->extrato[i - 1];
        }
    }
    //e a primeira posicao do array recebe o extrato novo
    pContaDestino->pConta->extrato[0] = extrato;
}

void depositar(void)
{
    system("clear");
    float valor;
    puts("Digite o valor a ser depositado: ");
    scanf("%f", &valor);

    pNodoContaLogada->pConta->quantia += valor;
    EXTRATO extrato = {valor, "Deposito"};
    insereNoExtrato(extrato, pNodoContaLogada);

    limparBuffer();
}

void sacar(void)
{
    system("clear");
    float valor;
    puts("Digite o valor a ser sacado: ");
    scanf("%f", &valor);
    limparBuffer();

    if (pNodoContaLogada->pConta->quantia < valor)
    {
        puts("\nEssa conta não tem dinheiro suficiente para sacar esse valor!");
        puts("Digite qualquer coisa para cancelar.");

        //getchar() le um caracter (do buffer, caso tenha, ou do teclado). ate ela ler
        //alguma coisa, o sistema fica pausado. isso basicamente serve pra pausar o sistema.
        getchar();
        return;
    }
    pNodoContaLogada->pConta->quantia -= valor;
    EXTRATO extrato = {-valor, "Saque"};

    insereNoExtrato(extrato, pNodoContaLogada);
}

void transferir(void)
{
    system("clear");
    NODO *pDestino;
    pAtual = pInicio;
    char busca[50];
    unsigned short int encontrado = FALSE;

    //funcao puts (put string) imprime uma string e automaticamente deixa uma linha
    puts("Digite o CPF da conta de destino: ");
    fgets(busca, sizeof(busca), stdin);
    
    //funcao strcspan (string character span) busca a primeira posicao dentro da string "busca" onde aparece 
    //o caracter \n, que deixa uma linha, isso pq o fgets tambem le o enter. nessa posicao da string, substituimos
    // \n por 0, para indicar o fim da string
    busca[strcspn(busca, "\n")] = 0;

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

    if (pNodoContaLogada->pConta->quantia < valor)
    {
        puts("\nEssa conta não tem dinheiro suficiente para sacar esse valor!");
        puts("Digite qualquer coisa para cancelar.");
        getchar();
        return;
    }
    pNodoContaLogada->pConta->quantia -= valor;
    pDestino->pConta->quantia += valor;

    char descricao1[40];
    //a funcao sprintf (string printf) insere na string "descricao1" a string
    //do segundo parâmetro, recebendo no terceiro paragrafo a string que substitui "%s"
    sprintf(descricao1, "Transferencia para %s", pDestino->pConta->cpf);
    EXTRATO extrato = {-valor, ""};

    //a funcao strcpy insere no primeiro parametro a string no segundo parametro
    strcpy(extrato.tipo, descricao1);
    insereNoExtrato(extrato, pNodoContaLogada);

    char descricao2[40];
    sprintf(descricao2, "Transferencia de %s", pNodoContaLogada->pConta->cpf);
    EXTRATO extratoOutro = {valor, ""};
    strcpy(extratoOutro.tipo, descricao2);
    insereNoExtrato(extratoOutro, pDestino);
}

void imprimeConta(void)
{
    system("clear");
    printf("Nome: %s\n", pNodoContaLogada->pConta->nome);
    printf("CPF: %s\n", pNodoContaLogada->pConta->cpf);
    printf("Senha: %s\n", pNodoContaLogada->pConta->senha);
    printf("Quantia depositada: %.2f\n", pNodoContaLogada->pConta->quantia);
    puts("Digite qualquer coisa para continuar.");
    getchar();
}

void imprimeExtrato(void)
{
    system("clear");
    unsigned short int vazio = TRUE;
    for (int i = 0; i < QTD_DADOS_EXTRATO; i++)
    {
        if (pNodoContaLogada->pConta->extrato[i].valor != 0)
        {
            printf("%.2f - %s\n", 
                pNodoContaLogada->pConta->extrato[i].valor, 
                pNodoContaLogada->pConta->extrato[i].tipo
            );
            vazio = FALSE;
        }
    }
    if (vazio == TRUE)
    {
        puts("Essa conta nao realizou operacoes ainda!");
    }
    puts("Digite qualquer coisa para continuar.");
    getchar();
}

void logar(void)
{
    while (pNodoContaLogada == NULL)
    {
        system("clear");

        pAtual = pInicio;

        char busca[50];

        puts("Digite o CPF da conta");
        fgets(busca, sizeof(busca), stdin);
        busca[strcspn(busca, "\n")] = 0;

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
            getchar();
        }
        else
        {
            int logado = TRUE;
            char senha[20];
            puts("Digite a senha: ");
            fgets(senha, sizeof(senha), stdin);
            senha[strcspn(senha, "\n")] = 0;

            if (strcmp(pAtual->pConta->senha, senha) != 0)
            {
                puts("Senha incorreta! Digite qualquer coisa para cancelar.");
                logado = 0;
                pNodoContaLogada = NULL;
                getchar();
            }

            if (logado != FALSE)
            {
                pNodoContaLogada = pAtual;
            }
        }
    }
}

void editar(void)
{
    system("clear");
    int opcao = 0;
    puts("O que voce deseja alterar?");
    puts("1 - Nome");
    puts("2 - CPF");
    puts("3 - Senha");
    puts("Outro numero - Voltar ao menu");
    puts("\nDigite a opcao desejada.");
    scanf("%d", &opcao);
    limparBuffer();
    system("clear");

    switch (opcao)
    {
    case 1:
        puts("Nome atual:");
        printf("%s\n", pNodoContaLogada->pConta->nome);
        puts("Novo nome:");
        fgets(pNodoContaLogada->pConta->nome, sizeof(pNodoContaLogada->pConta->nome), stdin);
        pNodoContaLogada->pConta->nome[strcspn(pNodoContaLogada->pConta->nome, "\n")] = 0;
        break;

    case 2:
        puts("CPF atual:");
        printf("%s\n", pNodoContaLogada->pConta->cpf);
        puts("Novo CPF:");
        fgets(pNodoContaLogada->pConta->cpf, sizeof(pNodoContaLogada->pConta->cpf), stdin);
        pNodoContaLogada->pConta->cpf[strcspn(pNodoContaLogada->pConta->cpf, "\n")] = 0;
        break;

    case 3:
        puts("Senha atual:");
        printf("%s\n", pNodoContaLogada->pConta->senha);
        puts("Nova senha:");
        fgets(pNodoContaLogada->pConta->senha, sizeof(pNodoContaLogada->pConta->senha), stdin);
        pNodoContaLogada->pConta->senha[strcspn(pNodoContaLogada->pConta->senha, "\n")] = 0;
        break;

    case 4:
        break;

    default:
        break;
    }
}

void menu(void)
{
    while (1)
    {
        system("clear");
        printf("BANCO CATUPIROLA");
        printf("\nConta atual: %s", pNodoContaLogada->pConta->cpf);
        printf("\n\n1 - Informacoes da Conta");
        printf("\n2 - Ver extrato");
        printf("\n3 - Depositar");
        printf("\n4 - Sacar");
        printf("\n5 - Transferir");
        printf("\n6 - Editar conta");
        printf("\n7 - Sair");
        printf("\n\nDigite a opcao desejada: ");

        int opcao = 0;
        scanf("%d", &opcao);

        limparBuffer();

        switch (opcao)
        {
        case 1:
            imprimeConta();
            break;

        case 2:
            imprimeExtrato();
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
            editar();
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
    logar();
    if (pNodoContaLogada != NULL)
    {
        menu();
    }
    return 0;
}