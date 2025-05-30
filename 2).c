#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 40

typedef struct {
    int codigo;
    char descricao[50];
    int quantidade_estoque;
    float valor_unitario;
} Produto;

Produto estoque[MAX_PRODUTOS];
int total_produtos = 0;

void inicializarEstoque() {
    //primeiro produto
    estoque[0].codigo = 1001;
    strcpy(estoque[0].descricao, "lapis HB");
    estoque[0].valor_unitario = 1.20;
    estoque[0].quantidade_estoque = 100;
    
    //segundo produto
    estoque[1].codigo = 1002;
    strcpy(estoque[1].descricao, "borracha");
    estoque[1].valor_unitario = 0.80;
    estoque[1].quantidade_estoque = 50;
    
    //terceiro produto
    estoque[2].codigo = 1003;
    strcpy(estoque[2].descricao, "caderno 200 folhas");
    estoque[2].valor_unitario = 25.90;
    estoque[2].quantidade_estoque = 30;
    
    total_produtos = 3;
}

//A)
void cadastrarProduto() {
    if (total_produtos >= MAX_PRODUTOS) {
        printf("limite de produtos atingido\n");
        return;
    }
    
    Produto novo;
    printf("\n--- cadastro de novo produto ---\n");
    
    int codigo_existente;
    do {
        codigo_existente = 0;
        printf("codigo: ");
        scanf("%d", &novo.codigo);
        
        for (int i = 0; i < total_produtos; i++) {
            if (estoque[i].codigo == novo.codigo) {
                printf("codigo ja existente tente novamente\n");
                codigo_existente = 1;
                break;
            }
        }
    } while (codigo_existente);
    
    printf("descricao: ");
    scanf(" %[^\n]s", novo.descricao);
    printf("valor unitario: R$ ");
    scanf("%f", &novo.valor_unitario);
    printf("quantidade em estoque: ");
    scanf("%d", &novo.quantidade_estoque);
    
    estoque[total_produtos] = novo;
    total_produtos++;
    
    printf("produto cadastrado com sucesso\n");
}

//B)
void alterarValor() {
    int codigo;
    printf("\n--- alteracao do valor ---\n");
    printf("codigo do produto: ");
    scanf("%d", &codigo);
    
    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].codigo == codigo) {
            printf("produto: %s\n", estoque[i].descricao);
            printf("valor atual: R$ %.2f\n", estoque[i].valor_unitario);
            printf("novo valor: R$ ");
            scanf("%f", &estoque[i].valor_unitario);
            printf("valor atualizado\n");
            return;
        }
    }
    printf("produto nao encontrado\n");
}

//C)
float informarValor(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].codigo == codigo) {
            return estoque[i].valor_unitario;
        }
    }
    return -1; 
}

//D)
int informarEstoque(int codigo) {
    for (int i = 0; i < total_produtos; i++) {
        if (estoque[i].codigo == codigo) {
            return estoque[i].quantidade_estoque;
        }
    }
    return -1; 
}

//E)
void realizarVenda() {
    int codigo, quantidade;
    printf("\n--- realizar venda ---\n");
    printf("codigo do produto: ");
    scanf("%d", &codigo);
    
    int estoque_atual = informarEstoque(codigo);
    if (estoque_atual == -1) {
        printf("produto nao encontrado\n");
        return;
    }
    
    if (estoque_atual == 0) {
        printf("produto fora de estoque\n");
        return;
    }
    
    printf("quantidade desejada: ");
    scanf("%d", &quantidade);
    
    if (quantidade <= estoque_atual) {
        for (int i = 0; i < total_produtos; i++) {
            if (estoque[i].codigo == codigo) {
                estoque[i].quantidade_estoque -= quantidade;
                float total = quantidade * estoque[i].valor_unitario;
                printf("venda realizada total: R$ %.2f\n", total);
                return;
            }
        }
    } else {
        char opcao;
        printf("quantidade insuficiente\n");
        printf("deseja comprar estoque disponivel (%d unidades)? (S/N): ", estoque_atual);
        scanf(" %c", &opcao);
        
        if (toupper(opcao) == 'S') {
            for (int i = 0; i < total_produtos; i++) {
                if (estoque[i].codigo == codigo) {
                    float total = estoque_atual * estoque[i].valor_unitario;
                    estoque[i].quantidade_estoque = 0;
                    printf("venda realizada total: R$ %.2f\n", total);
                    return;
                }
            }
        } else {
            printf("venda cancelada\n");
        }
    }
}

void exibirMenu() {
    printf("\n=== PAPELARIA ===\n");
    printf("1. cadastrar novo produto\n");
    printf("2. alterar valor unitario\n");
    printf("3. consultar valor unitario\n");
    printf("4. consultar estoque\n");
    printf("5. realizar venda\n");
    printf("6. sair\n");
    printf("opcao: ");
}

int main() {
    int opcao;
    inicializarEstoque();
    
    do {
        exibirMenu();
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                cadastrarProduto();
                break;
                
            case 2:
                alterarValor();
                break;
                
            case 3: {
                int codigo;
                printf("codigo do produto: ");
                scanf("%d", &codigo);
                float valor = informarValor(codigo);
                if (valor == -1) {
                    printf("produto nao encontrado\n");
                } else {
                    printf("valor unitario: R$ %.2f\n", valor);
                }
                break;
            }
                
            case 4: {
                int codigo;
                printf("codigo do produto: ");
                scanf("%d", &codigo);
                int qtd = informarEstoque(codigo);
                if (qtd == -1) {
                    printf("produto nao encontrado\n");
                } else {
                    printf("quantidade no estoque: %d\n", qtd);
                }
                break;
            }
                
            case 5:
                realizarVenda();
                break;
                
            case 6:
                printf("saindo...\n");
                break;
                
            default:
                printf("opcao invalida\n");
        }
    } while (opcao != 6);

    return 0;
}