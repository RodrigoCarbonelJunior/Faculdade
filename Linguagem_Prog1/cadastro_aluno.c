#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ALUNOS 5
#define DISCIPLINAS 3
#define AVALIACOES 2

typedef struct {
    char nome[50];
    int matricula;
    float notas[DISCIPLINAS][AVALIACOES];
} Aluno;

void preencherAluno(Aluno *aluno) {
    system("clear");
    printf("\n===== CADASTRO DE ALUNO =====\n");
    getchar();  // Limpa o buffer de entrada
    printf("Nome do aluno: ");
    fgets(aluno->nome, sizeof(aluno->nome), stdin);
    aluno->nome[strcspn(aluno->nome, "\n")] = '\0';  // Remove o \n no final

    printf("Matricula: ");
    scanf("%d", &aluno->matricula);

    for(int i = 0; i < DISCIPLINAS; i++) {
        for(int j = 0; j < AVALIACOES; j++) {
            printf("Nota da disciplina %d, avaliacao %d: ", i+1, j+1);
            scanf("%f", &aluno->notas[i][j]);
        }
    }
}

void calcularMedia(Aluno aluno) {
    float soma = 0;
    int totalNotas = DISCIPLINAS * AVALIACOES;

    for(int i = 0; i < DISCIPLINAS; i++) {
        for(int j = 0; j < AVALIACOES; j++) {
            soma += aluno.notas[i][j];
        }
    }

    printf("\nMedia do aluno %s (Matricula %d): %.2f\n", aluno.nome, aluno.matricula, soma / totalNotas);
}

void mostrarAlunos(Aluno *alunos, int quantidade) {
    for(int i = 0; i < quantidade; i++) {
        printf("\nAluno %d:\n", i+1);
        printf("Nome: %s\n", alunos[i].nome);
        printf("Matricula: %d\n", alunos[i].matricula);
        for(int d = 0; d < DISCIPLINAS; d++) {
            printf("Notas da disciplina %d: ", d+1);
            for(int a = 0; a < AVALIACOES; a++) {
                printf("%.1f ", alunos[i].notas[d][a]);
            }
            printf("\n");
        }
    }
}

int main() {
    Aluno alunos[MAX_ALUNOS];
    Aluno *alunosDinamicos = NULL;
    int opcao, quantidade = 0, quantidadeDinamica = 0;

    do {
        system("clear");
        printf("\n===== MENU =====\n");
        printf("1 - Inserir aluno (estatico)\n");
        printf("2 - Mostrar alunos (estatico)\n");
        printf("3 - Calcular media de um aluno (estatico)\n");
        printf("4 - Inserir alunos (dinamico)\n");
        printf("5 - Mostrar alunos (dinamico)\n");
        printf("6 - Calcular media (dinamico)\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: {
                int voltar;
                do {
                    system("clear");
                    if(quantidade < MAX_ALUNOS) {
                        preencherAluno(&alunos[quantidade]);
                        quantidade++;
                        printf("\nAluno cadastrado com sucesso!");
                    } else {
                        printf("\nLimite de alunos estaticos atingido!");
                    }
                    printf("\nDigite 0 para voltar ao menu: ");
                    scanf("%d", &voltar);
                } while(voltar != 0);
                break;
            }

            case 2: {
                int voltar;
                do {
                    system("clear");
                    printf("\n===== LISTA DE ALUNOS (ESTÁTICO) =====\n");
                    mostrarAlunos(alunos, quantidade);
                    printf("\nDigite 0 para voltar ao menu: ");
                    scanf("%d", &voltar);
                } while(voltar != 0);
                break;
            }

            case 3: {
                int voltar;
                do {
                    system("clear");
                    int index;
                    printf("\n===== CALCULAR MÉDIA DE UM ALUNO (ESTÁTICO) =====\n");
                    printf("Digite o numero do aluno (1 a %d): ", quantidade);
                    scanf("%d", &index);
                    if(index >= 1 && index <= quantidade) {
                        calcularMedia(alunos[index - 1]);
                    } else {
                        printf("Indice invalido!\n");
                    }
                    printf("\nDigite 0 para voltar ao menu: ");
                    scanf("%d", &voltar);
                } while(voltar != 0);
                break;
            }

            case 4: {
                int voltar;
                do {
                    system("clear");
                    printf("\n===== INSERIR ALUNOS (DINÂMICO) =====\n");
                    printf("Quantos alunos deseja cadastrar de forma dinamica? ");
                    scanf("%d", &quantidadeDinamica);

                    alunosDinamicos = (Aluno *) malloc(quantidadeDinamica * sizeof(Aluno));

                    if(alunosDinamicos == NULL) {
                        printf("Erro ao alocar memoria!\n");
                        exit(1);
                    }

                    for(int i = 0; i < quantidadeDinamica; i++) {
                        printf("\n--- Aluno Dinamico %d ---\n", i+1);
                        preencherAluno(alunosDinamicos + i);
                    }

                    printf("\nCadastro dinamico finalizado!");
                    printf("\nDigite 0 para voltar ao menu: ");
                    scanf("%d", &voltar);
                } while(voltar != 0);
                break;
            }

            case 5: {
                int voltar;
                do {
                    system("clear");
                    printf("\n===== LISTA DE ALUNOS (DINÂMICO) =====\n");
                    if(alunosDinamicos != NULL) {
                        mostrarAlunos(alunosDinamicos, quantidadeDinamica);
                    } else {
                        printf("Nenhum aluno dinamico cadastrado!\n");
                    }
                    printf("\nDigite 0 para voltar ao menu: ");
                    scanf("%d", &voltar);
                } while(voltar != 0);
                break;
            }

            case 6: {
                int voltar;
                do {
                    system("clear");
                    if(alunosDinamicos != NULL) {
                        int index;
                        printf("\n===== CALCULAR MÉDIA (DINÂMICO) =====\n");
                        printf("Digite o numero do aluno dinamico (1 a %d): ", quantidadeDinamica);
                        scanf("%d", &index);
                        if(index >= 1 && index <= quantidadeDinamica) {
                            calcularMedia(*(alunosDinamicos + (index - 1)));
                        } else {
                            printf("Indice invalido!\n");
                        }
                    } else {
                        printf("Nenhum aluno dinamico cadastrado!\n");
                    }
                    printf("\nDigite 0 para voltar ao menu: ");
                    scanf("%d", &voltar);
                } while(voltar != 0);
                break;
            }

            case 0:
                printf("Encerrando o programa...\n");
                break;

            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);

    if(alunosDinamicos != NULL) {
        free(alunosDinamicos);
    }

    return 0;
}
