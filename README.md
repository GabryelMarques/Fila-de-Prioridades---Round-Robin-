# Trabalho Prático - Sistemas Operacionais

## UNIVERSIDADE FEDERAL DO TOCANTINS  
### CURSO: Ciência da Computação  
**DISCIPLINA**: Sistemas Operacionais  
**ALUNOS**: Gabryel Marques, Laura Mona e Matheus  
**PROFA**: Dra. Glenda Botelho

### Tema: Escalonamento de Processos por Fila de Prioridades

Este projeto implementa um algoritmo de escalonamento de processos utilizando filas de prioridades, conforme os requisitos do trabalho prático da disciplina de Sistemas Operacionais.

## Descrição do Projeto
O objetivo deste projeto é implementar o escalonamento de processos por Fila de Prioridades, com as seguintes características:

- **4 filas de prioridades distintas**: Cada fila tem uma prioridade diferente, onde a fila de maior prioridade é processada antes das filas de menor prioridade.
- **Listas circulares (Round Robin)**: Cada fila é implementada como uma lista circular para garantir que os processos sejam alternados de forma justa.
- **Quantum de tempo estático**: O quantum de tempo pode ser definido pelo aluno de maneira estática e será aplicado uniformemente em todas as filas.
- **Bloco de Controle de Processos (PCB)**: Cada fila é composta por nós do tipo PCB, que armazenam as informações do processo.

## Funcionalidades
- Implementação do escalonamento de processos com prioridade.
- Criação automática de processos com tempos de CPU e quantum de tempo.
- Exibição dos processos por fila de prioridade.
- Execução dos processos conforme a lógica de escalonamento com Round Robin.

## Linguagem Utilizada
- **C**: O código foi desenvolvido utilizando C, conforme solicitado no trabalho.

## Configuração do terminal (PowerShell)
- Para usar UTF-8 no PowerShell:

- Abra o PowerShell.
- Digite o seguinte comando para mudar a codificação para UTF-8:
- [Console]::OutputEncoding = [System.Text.Encoding]::UTF8


## Instruções para Execução
1. Clone este repositório:
   ```bash
   git clone https://github.com/seu-usuario/seu-repositorio.git
