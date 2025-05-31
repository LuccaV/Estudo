#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_CONTAS 100

typedef struct {
    int numero;
    char nome[50];
    char cpf[15];
    char telefone[15];
    float saldo;
} Conta;

Conta corrente[MAX_CONTAS];
Conta poupanca[MAX_CONTAS];
int qtd_corrente = 0;
int qtd_poupanca = 0;

//A)
int buscar(Conta cadastro[], int tamanho, int numero_conta) {
    if (tamanho == 0) return -1;
    for (int i = 0; i < tamanho; i++) {
        if (cadastro[i].numero == numero_conta) {
            return i; 
        }
    }
    return -2;
}

//B)
void cadastrarConta(Conta cadastro[], int *tamanho) {
    if (*tamanho >= MAX_CONTAS) {
        printf("limite de contas ultrapassado\n");
        return;
    }
    
    int numero;
    printf("\nnumero da conta: ");
    scanf("%d", &numero);
    
    int pos = buscar(cadastro, *tamanho, numero);
    if (pos >= 0) {
        printf("erro: numero de conta ja existe\n");
        return;
    }
    
    Conta nova;
    nova.numero = numero;
    
    printf("nome do titular: ");
    scanf(" %[^\n]s", nova.nome);
    printf("CPF: ");
    scanf("%s", nova.cpf);
    printf("telefone: ");
    scanf("%s", nova.telefone);
    nova.saldo = 0.0;
    
    cadastro[*tamanho] = nova;
    (*tamanho)++;
    printf("conta cadastrada com sucesso\n");
}

//C)
void consultarSaldo(Conta cadastro[], int tamanho) {
    int numero;
    printf("\nnumero da conta: ");
    scanf("%d", &numero);
    
    int pos = buscar(cadastro, tamanho, numero);
    if (pos == -1) {
        printf("cadastro vazio\n");
    } else if (pos == -2) {
        printf("conta nao encontrada\n");
    } else {
        printf("saldo: R$ %.2f\n", cadastro[pos].saldo);
    }
}

//D)
void depositar(Conta cadastro[], int tamanho) {
    int numero;
    printf("\nnumero da conta: ");
    scanf("%d", &numero);
    
    int pos = buscar(cadastro, tamanho, numero);
    if (pos < 0) {
        printf(pos == -1 ? "cadastro vazio\n" : "conta nao encontrada\n");
        return;
    }
    
    float valor;
    printf("valor do deposito: R$ ");
    scanf("%f", &valor);
    
    if (valor > 0) {
        cadastro[pos].saldo += valor;
        printf("deposito realizado novo saldo: R$ %.2f\n", cadastro[pos].saldo);
    } else {
        printf("valor invalido\n");
    }
}

// LETRA E
void sacar(Conta cadastro[], int tamanho) {
    int numero;
    printf("\nnumero da conta: ");
    scanf("%d", &numero);
    
    int pos = buscar(cadastro, tamanho, numero);
    if (pos < 0) {
        printf(pos == -1 ? "cadastro vazio\n" : "conta nao encontrada\n");
        return;
    }
    
    float valor;
    printf("valor do saque: R$ ");
    scanf("%f", &valor);
    
    if (valor <= 0) {
        printf("valor invalido para saque\n");
    } else if (valor > cadastro[pos].saldo) {
        printf("saldo insuficiente\n");
    } else {
        cadastro[pos].saldo -= valor;
        printf("saque realizado novo saldo: R$ %.2f\n", cadastro[pos].saldo);
    }
}

//F)
void listarContas(Conta cadastro[], int tamanho, const char *tipo) {
    printf("\n=== CONTAS %s ===\n", tipo);
    if (tamanho == 0) {
        printf("nenhuma conta cadastrada\n");
        return;
    }
    
    for (int i = 0; i < tamanho; i++) {
        printf("\nconta: %d", cadastro[i].numero);
        printf("\ntitular: %s", cadastro[i].nome);
        printf("\ntelefone: %s", cadastro[i].telefone);
        printf("\n-------------------\n");
    }
}

void menuConta(Conta cadastro[], int *tamanho, const char *tipo) {
    int opcao;
    do {
        printf("\n=== %s ===", tipo);
        printf("\n1. cadastrar nova conta");
        printf("\n2. consultar saldo");
        printf("\n3. fazer deposito");
        printf("\n4. fazer saque");
        printf("\n5. listar contas");
        printf("\n6. voltar");
        printf("\nopcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarConta(cadastro, tamanho);
                break;
            case 2:
                consultarSaldo(cadastro, *tamanho);
                break;
            case 3:
                depositar(cadastro, *tamanho);
                break;
            case 4:
                sacar(cadastro, *tamanho);
                break;
            case 5:
                listarContas(cadastro, *tamanho, tipo);
                break;
            case 6:
                printf("retornando ao menu...\n");
                break;
            default:
                printf("opcao invalida\n");
        }
    } while(opcao != 6);
}

int main() {
    int opcao;
    
    do {
        printf("\n=== BANCO DINHEIRO CERTO ===");
        printf("\n1. conta corrente");
        printf("\n2. conta poupanca");
        printf("\n3. sair");
        printf("\nopcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                menuConta(corrente, &qtd_corrente, "CORRENTE");
                break;
            case 2:
                menuConta(poupanca, &qtd_poupanca, "POUPANCA");
                break;
            case 3:
                printf("encerrando...\n");
                break;
            default:
                printf("opcao invalida\n");
        }
    } while(opcao != 3);

    return 0;
}