#include <stdio.h>
#include <string.h>
#define ESTADOS 27

typedef struct {
    char nomes[40];
    int veiculos;
    int acidentes;
} Estados;

//A)
void carregar_estados(Estados coleta[]) {
    char lista_de_estados[ESTADOS][40] = {
        "acre", "alagoas", "amapa", "amazonas", "bahia", "ceara", 
        "distrito federal", "espirito santo", "goias", "maranhao", 
        "mato grosso", "mato grosso do sul", "minas gerais", "para", 
        "paraiba", "parana", "pernambuco", "piaui", "rio de janeiro", 
        "rio grande do norte", "rio grande do sul", "rondonia", "roraima", 
        "santa catarina", "sao paulo", "sergipe", "tocantins"
    };

    for (int i = 0; i < ESTADOS; i++) {
        strcpy(coleta[i].nomes, lista_de_estados[i]);
        printf("digite veiculos para %s: ", coleta[i].nomes);
        scanf("%d", &coleta[i].veiculos);
        printf("digite acidentes para %s: ", coleta[i].nomes);
        scanf("%d", &coleta[i].acidentes);
    }
}

void encontrar_extremos(Estados coleta[], int *menor, int *maior) {
    *menor = 0;
    *maior = 0;
    for (int i = 1; i < ESTADOS; i++) {
        if (coleta[i].acidentes > coleta[*maior].acidentes) {
            *maior = i;
        }
        if (coleta[i].acidentes < coleta[*menor].acidentes) {
            *menor = i;
        }
    }
}   

//C)
float calcular_percentual(Estados estado) {
    if (estado.veiculos == 0) return 0; 
    return (estado.acidentes * 100.0) / estado.veiculos;
}

//D)
float calcular_media_acidentes(Estados coleta[]) {
    int soma = 0;
    for (int i = 0; i < ESTADOS; i++) {
        soma += coleta[i].acidentes;
    }
    return (float)soma / ESTADOS;
}

//E)
void listar_estados_acima_media(Estados coleta[], float media) {
    for (int i = 0; i < ESTADOS; i++) {
        if (coleta[i].acidentes > media) {
            printf("%s esta acima da media de acidentes\n", coleta[i].nomes);
        }
    }
}

int main() {
    Estados coleta[ESTADOS];
    int menor, maior;
    float media;

    carregar_estados(coleta);
    encontrar_extremos(coleta, &menor, &maior);

    printf("\n%s tem o menor numero de acidentes: %d\n", coleta[menor].nomes, coleta[menor].acidentes);
    printf("%s tem o maior numero de acidentes: %d\n\n", coleta[maior].nomes, coleta[maior].acidentes);

    printf("acidentes por veiculo: \n");
    for (int i = 0; i < ESTADOS; i++) {
        float porcentagem = calcular_percentual(coleta[i]);
        printf("- %s: %.2f%%\n", coleta[i].nomes, porcentagem);
    }

    media = calcular_media_acidentes(coleta);
    printf("\nmedia de acidentes: %.2f\n", media);

    printf("\nestados acima da media: \n");
    listar_estados_acima_media(coleta, media);

    return 0;
}