#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 31

typedef struct paciente{
    char nome[MAX_NOME];
} tipoPaciente;

typedef struct {
    int qtde;
    tipoPaciente *fila;
} tipoGerente;

int inicio, fim, capacidade;

void inicializaFila(tipoGerente *gerente, int cap) {
	
    capacidade = cap;
    gerente->qtde = 0;
    inicio = 0;
    fim = -1;
    
    gerente->fila = (tipoPaciente*) malloc(capacidade * sizeof(tipoPaciente));
}

int filaCheia(tipoGerente *gerente) {
    return gerente->qtde == capacidade;
}

int filaVazia(tipoGerente *gerente) {
    return gerente->qtde == 0;
}

void adicionarPaciente(tipoGerente *gerente) {
    if (filaCheia(gerente)) {
        printf("A fila esta cheia, aguarde!\n");
        return;
    }

    fim = (fim + 1) % capacidade;

    printf("Digite o nome de quem entrou na fila:\n");
    scanf("%s", gerente->fila[fim].nome);
    
    gerente->qtde++;
}

void atenderPaciente(tipoGerente *gerente) {
    int atende, i;

    while (1) {
        printf("\nDigite quantos pacientes deseja atender: ");
        scanf("%d", &atende);

        if (atende > gerente->qtde) {
            printf("Esta tentando atender mais pacientes do que o disponivel.\n");
            printf("Número de pacientes na fila: %d\n", gerente->qtde);
            continue;
        }
        break;
    }

    for (i = 0; i < atende; i++) {
        printf("%s Paciente atendido.\n", gerente->fila[inicio].nome);
        inicio = (inicio + 1) % capacidade;
        
        gerente->qtde--;
    }

    if (filaVazia(gerente)) {
    	
        inicio = 0;
        fim = -1;
    }
}

void mostrarFila(tipoGerente *gerente) {
    int i;
    
    if (filaVazia(gerente)) {
        printf("\nA fila esta vazia.\n");
        return;
    }

    printf("----- Pacientes -----\n");
    for (i = 0; i < gerente->qtde; i++) {
        int indice = (inicio + i) % capacidade;
        printf("%s\n", gerente->fila[indice].nome);
    }
}

int main() {
	
    tipoGerente gerente;
    int max, qtde, acao, i;

    printf("\nDigite a capacidade maxima de atendimento: ");
    scanf("%d", &max);

    inicializaFila(&gerente, max);

    while (1) {
        printf("\nQuantas pessoas entraram na fila? ");
        scanf("%d", &qtde);

        if (qtde > max - gerente.qtde) {
            printf("\nA fila esta cheia, adicione uma quantidade menor ou aguarde liberar espaco!\n");
            continue;
        }

        for (i = 0; i < qtde; i++) {
            adicionarPaciente(&gerente);
        }

        while (1) {
            printf("\nSelecione a acao que deseja realizar\n1- Atender Pacientes.\n2- Mostrar pacientes na fila.\n3- Adicionar mais pacientes a fila.\n4- Verificar quantidade de pacientes na fila.\n5- Finalizar o atendimento.\nDigite a acao desejada: ");
            scanf("%d", &acao);

            if (acao == 3)
                break;

            switch (acao) {
                case 1:
                    atenderPaciente(&gerente);
                    break;

                case 2:
                    mostrarFila(&gerente);
                    continue;

                case 4:
                    printf("\nNumero de pacientes na fila: %d\n", gerente.qtde);
                    continue;

                case 5:
                    printf("\nFinalizando o atendimento...\n");
                    free(gerente.fila); 
                    return 0;

                default:
                    printf("Selecione uma opcao valida!\n");
                    continue;
            }
        }
    }

    return 0;
}

