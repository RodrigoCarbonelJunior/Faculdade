#include <stdio.h>

int main() {
    int numNotas, i, opcao;
    float notas[100], soma = 0, media, pesos[100], somaPesos = 0;

    printf("Quantas notas deseja inserir? ");
    scanf("%d", &numNotas);

    // Entrada das notas
    for(i = 0; i < numNotas; i++) {
        printf("Digite a nota %d: ", i + 1);
        scanf("%f", &notas[i]);
    }

    // Menu de escolha de tipo de media
    printf("\nEscolha o tipo de media:\n");
    printf("1 - Media Aritmetica\n");
    printf("2 - Media Ponderada\n");
    printf("Opcao: ");
    scanf("%d", &opcao);

    switch(opcao) {
        case 1:
            // Calculando a media aritmetica
            for(i = 0; i < numNotas; i++) {
                soma += notas[i];
            }
            media = soma / numNotas;
            break;

        case 2:
            // Entrada dos pesos e calculo da media ponderada
            for(i = 0; i < numNotas; i++) {
                printf("Digite o peso da nota %d: ", i + 1);
                scanf("%f", &pesos[i]);
                soma += notas[i] * pesos[i];
                somaPesos += pesos[i];
            }
            if(somaPesos != 0) {
                media = soma / somaPesos;
            } else {
                printf("Erro: Soma dos pesos nao pode ser zero.\n");
                return 1;
            }
            break;

        default:
            printf("Opcao invalida.\n");
            return 1;
    }

    // Exibindo a media final
    printf("\nMedia final: %.2f\n", media);

    // Verificando a situacao do aluno
    if(media >= 7.0) {
        printf("Situacao: Aprovado\n");
    } else if(media >= 5.0) {
        printf("Situacao: Recuperacao\n");
    } else {
        printf("Situacao: Reprovado\n");
    }

    return 0;
}
