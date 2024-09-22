#include <stdio.h>
#include <stdlib.h>

typedef struct PCB {
    int id;             // ID do processo (identificador único)
    int estado;         // Estado do processo (0 = Pronto, 1 = Executando, 2 = Bloqueado)
    int tempo_cpu;      // Tempo total de CPU necessário para o processo
    int quantum;        // Quantum de tempo para o processo
    struct PCB* prox;   // Ponteiro para o próximo PCB (para lista circular)
} PCB;

// Estrutura de Fila
typedef struct Fila {
    PCB* inicio;    // Ponteiro para o primeiro PCB da fila
    PCB* fim;       // Ponteiro para o último PCB da fila (para facilitar a inserção)
} Fila;

// Função para criar um novo PCB
PCB* criarPCB(int id, int tempo_cpu, int quantum) {
    PCB* novo_processo = (PCB*) malloc(sizeof(PCB));
    novo_processo->id = id;
    novo_processo->estado = 0;  // Inicialmente, o processo está "Pronto"
    novo_processo->tempo_cpu = tempo_cpu;
    novo_processo->quantum = quantum;
    novo_processo->prox = NULL; // Ponteiro para o próximo, inicializado como NULL
    return novo_processo;
}

// Função para inicializar uma fila
void inicializarFila(Fila* fila) {
    fila->inicio = NULL;
    fila->fim = NULL;
}

// Função para inserir um PCB na fila (inserção no final)
void inserirNaFila(Fila* fila, PCB* processo) {
    if (fila->inicio == NULL) {
        // Se a fila está vazia, o processo será o único elemento e a lista será circular
        fila->inicio = processo;
        fila->fim = processo;
        processo->prox = processo; // Lista circular
    } else {
        // Inserir no final da fila
        fila->fim->prox = processo;
        processo->prox = fila->inicio; // Manter a lista circular
        fila->fim = processo;
    }
}

// Função para remover o primeiro PCB da fila (remoção da cabeça da fila)
PCB* removerDaFila(Fila* fila) {
    if (fila->inicio == NULL) {
        return NULL;  // Fila vazia
    }
    
    PCB* processo_removido = fila->inicio;
    
    if (fila->inicio == fila->fim) {
        // Se houver apenas um processo na fila
        fila->inicio = NULL;
        fila->fim = NULL;
    } else {
        // Mais de um processo na fila
        fila->inicio = fila->inicio->prox;
        fila->fim->prox = fila->inicio;  // Manter a lista circular
    }
    
    processo_removido->prox = NULL;  // Remover o link circular
    return processo_removido;
}

// Função para verificar se uma fila está vazia
int filaVazia(Fila* fila) {
    return (fila->inicio == NULL);
}

// Função do escalonador que segue a lógica de prioridades
void escalonador(Fila filas[], int quantum) {
    while (1) {
        int todasVazias = 1;
        
        // Verificar todas as filas em ordem de prioridade
        for (int i = 0; i < 4; i++) {
            if (!filaVazia(&filas[i])) {
                todasVazias = 0;  // Há pelo menos uma fila com processos
                PCB* processo = removerDaFila(&filas[i]);
                
                // Simula a execução do processo
                printf("Executando processo %d da fila de prioridade %d\n", processo->id, i);
                
                // Processa o quantum de tempo
                if (processo->tempo_cpu > quantum) {
                    processo->tempo_cpu -= quantum;
                    inserirNaFila(&filas[i], processo);  // Reinsere o processo na fila
                } else {
                    printf("Processo %d finalizado\n", processo->id);
                    free(processo);  // O processo terminou
                }
            }
        }
        
        // Se todas as filas estiverem vazias, o escalonamento termina
        if (todasVazias) {
            printf("Todos os processos foram concluídos.\n");
            break;
        }
    }
}

int main() {
    // Criar o vetor de 4 filas de prioridades
    Fila filas[4];
    for (int i = 0; i < 4; i++) {
        inicializarFila(&filas[i]);
    }

    // Criar processos de exemplo
    PCB* p1 = criarPCB(1, 20, 5);
    PCB* p2 = criarPCB(2, 10, 5);
    PCB* p3 = criarPCB(3, 15, 5);
    PCB* p4 = criarPCB(4, 5, 5);

    // Inserir processos nas filas (baseado na prioridade das filas)
    inserirNaFila(&filas[0], p1);  // Prioridade mais alta
    inserirNaFila(&filas[0], p2);  // Segunda prioridade
    inserirNaFila(&filas[1], p3);  // Terceira prioridade
    inserirNaFila(&filas[1], p4);  // Quarta prioridade (menor)

    // Definir o quantum de tempo (mesmo para todos os processos)
    int quantum = 5;

    // Chamar o escalonador
    escalonador(filas, quantum);

    return 0;
}
