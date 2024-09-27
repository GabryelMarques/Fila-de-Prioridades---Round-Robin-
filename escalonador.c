#include <stdio.h>
#include <stdlib.h>
#include <time.h>  // Para usar srand() e gerar números aleatórios com base no tempo

typedef struct PCB {
    int id;             // ID do processo (identificador único)
    int estado;         // Estado do processo (0 = Pronto, 1 = Bloqueado)
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

// Função para criar e inicializar o vetor de 4 filas (para 4 níveis de prioridade)
void criarVetorFilas(Fila filas[]) {
    for (int i = 0; i < 4; i++) {
        inicializarFila(&filas[i]);
    }
}
void escalonador(Fila filas[], int quantum) {
    int troca = 1;  // Contador de troca para impressão das interações

    // Iterar sobre as filas em ordem de prioridade
    for (int i = 0; i < 4; i++) {
        // Enquanto houver processos na fila de prioridade `i`
        while (filas[i].inicio != NULL) {
            printf("Troca %d: Executando processo %d da fila de prioridade %d. Tempo restante: %d\n", 
                   troca, filas[i].inicio->id, i+1, filas[i].inicio->tempo_cpu);

            // Subtrai o quantum do tempo de CPU do processo
            filas[i].inicio->tempo_cpu -= quantum;
            
            if (filas[i].inicio->tempo_cpu <= 0) {  // Se o processo terminou
                PCB* processo_finalizado = filas[i].inicio;
                
                if (filas[i].inicio == filas[i].fim) {  // Se há apenas um processo na fila
                    filas[i].inicio = NULL;
                    filas[i].fim = NULL;
                } else {  // Mais de um processo na fila
                    filas[i].inicio = filas[i].inicio->prox;
                    filas[i].fim->prox = filas[i].inicio;  // Manter a lista circular
                }

                // Imprime que o processo foi finalizado
                // Códigos ANSI para cores
                #define RESET   "\033[0m"
                #define RED     "\033[31m"
                #define GREEN   "\033[32m"

                // Exibindo o processo finalizado com cor
                printf(GREEN "╔════════════════════════════════════╗\n");
                printf("║         Processo Finalizado        ║\n");
                printf("╠════════════════════════════════════╣\n");
                printf("║         Processo ID: %d             ║\n", processo_finalizado->id);
                printf("╚════════════════════════════════════╝" RESET "\n");


                free(processo_finalizado);  // Libera a memória do processo finalizado
            } else {  // Se o processo não terminou, ele volta para o final da fila
                filas[i].fim->prox = filas[i].inicio;
                filas[i].fim = filas[i].inicio;
                filas[i].inicio = filas[i].inicio->prox;  // Atualiza o início
                filas[i].fim->prox = filas[i].inicio;     // Manter a lista circular
            }

            troca++;  // Incrementa o número de trocas (interações)
        }
    }

    printf("Todos os processos foram concluidos.\n");
}
#include <stdio.h>
#include <stdlib.h>

// Função para exibir todos os processos organizados por fila com caracteres especiais
void exibirProcessosPorFila(Fila filas[]) {
    printf("╔════════════════════╦═══════════════════╦════════════╦══════════╦═════════╗\n");
    printf("║ Fila de Prioridade ║ ID do Processo    ║ Tempo CPU  ║ Quantum  ║ Estado  ║\n");
    printf("╠════════════════════╬═══════════════════╬════════════╬══════════╬═════════╣\n");

    for (int i = 0; i < 4; i++) {
        PCB* atual = filas[i].inicio;
        
        if (atual == NULL) {
            printf("║        %d           ║       -           ║     -      ║    -     ║   -     ║\n", i + 1);
        } else {
            do {
                printf("║        %d           ║       %d           ║    %d      ║   %d     ║   %d     ║\n", 
                       i + 1, atual->id, atual->tempo_cpu, atual->quantum, atual->estado);
                atual = atual->prox;
            } while (atual != filas[i].inicio); // Continua até voltar ao início da fila (circular)
        }
    }

    printf("╚════════════════════╩═══════════════════╩════════════╩══════════╩═════════╝\n");
}


// Função para gerar processos aleatórios e inserir nas filas correspondentes
void gerarProcessosAleatorios(Fila filas[], int num_processos, int min_tempo_cpu, int max_tempo_cpu, int quantum) {
    // Usar o tempo atual para inicializar a semente de números aleatórios
    srand(time(NULL));
    
    for (int i = 0; i < num_processos; i++) {
        // Gerar um tempo de CPU aleatório entre min_tempo_cpu e max_tempo_cpu
        int tempo_cpu = min_tempo_cpu + rand() % (max_tempo_cpu - min_tempo_cpu + 1);
        
        // Sortear uma fila de prioridade aleatória entre 0 e 3
        int fila_prioridade = rand() % 4;
        
        // Criar o processo com ID e os valores sorteados
        PCB* novo_processo = criarPCB(i + 1, tempo_cpu, quantum);
        
        // Inserir o processo na fila correspondente
        inserirNaFila(&filas[fila_prioridade], novo_processo);
        
        // Imprimir os detalhes do processo gerado
        printf("Processo %d criado: Tempo CPU = %d, Quantum = %d, Inserido na fila de prioridade %d\n",
               novo_processo->id, novo_processo->tempo_cpu, novo_processo->quantum, fila_prioridade+1);
    }
}

int main() {
    // Criar o vetor de 4 filas de prioridades
    Fila filas[4];
    for (int i = 0; i < 4; i++) {
        inicializarFila(&filas[i]);
    }

    // Definir o quantum de tempo (mesmo para todos os processos)
    int quantum = 5;

    // Gerar processos aleatórios
    int num_processos = 10;  // Quantidade de processos a serem gerados
    int min_tempo_cpu = 5;  // Valor mínimo de tempo de CPU
    int max_tempo_cpu = 20; // Valor máximo de tempo de CPU
    gerarProcessosAleatorios(filas, num_processos, min_tempo_cpu, max_tempo_cpu, quantum);

    // Exibir os processos organizados por fila
    exibirProcessosPorFila(filas);

    // Chamar o escalonador
    escalonador(filas, quantum);

    return 0;
}