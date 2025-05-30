#include <stdio.h>
#include <string.h>

#define ESTADOS 26

typedef struct {
    char nomes[40];
    int veiculos;
    int acidentes;
} Estados;

//A)
void ESTADOS_NOMES(Estados coleta[]) {
    char lista_de_estados[ESTADOS][40] = {
        "pernambuco", "sao paulo", "rio de janeiro", "acre", "alagoas", "amapa", "amazonas", "bahia", "ceara",
        "espirito Santo", "goias", "maranhao", "mato Grosso", "mato grosso do sul",
        "minas gerais", "para", "paraiba", "parana", "piaui",
        "rio grande do norte", "rio grande do sul", "rondonia", "roraima", "santa catarina",
        "sergipe", "tocantins"
    };

    for (int i = 0; i < ESTADOS; i+=1) {
        strcpy(coleta[i].nomes, lista_de_estados[i]);
        scanf("%d\n", &coleta[i].veiculos);
        scanf("%d\n", &coleta[i].acidentes);
        
    }

    for (int i = 0; i < ESTADOS; i+=1) {
        printf("--- Estado: %s\n", coleta[i].nomes);
        printf("--- veiculos: %d\n ", coleta[i].veiculos);
        printf("--- acidentes: %d\n ", coleta[i].acidentes);
    }
}

//B)
void MenorMaior(Estados coleta[], int *menor, int *maior) {
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
float Percentual(Estados estado) {
    if (estado.veiculos == 0) return 0; 
    return (estado.acidentes * 100.0) / estado.veiculos;
}

//D)
int MediaAcidentes(Estados coleta[]) {
    int media = 0;
    for (int i = 0; i < ESTADOS; i +=1) {
        media +=coleta[i].acidentes;
    
    }
    return media / ESTADOS;
}

//E)
void ACIMA_MediaAcidentes(Estados coleta[], int media) {
    for (int i = 0; i < ESTADOS; i +=1) {
        if (coleta[i].acidentes > media) {
            printf("%s acima da media de acidentes\n",coleta[i].nomes);
        }
    
    }
}

int main() {
    Estados coleta[ESTADOS];
    int menor, maior;
    int media;
    
    
    ESTADOS_NOMES(coleta);
    MenorMaior(coleta, &menor, &maior);

    printf("%s e o estado com menores acidentes: %d\n", coleta[menor].nomes, coleta[menor].acidentes);
    printf("%s e o estado com maiores acidentes: %d\n", coleta[maior].nomes, coleta[maior].acidentes);

    printf("\npercentual de acidentes por veiculo nos estados:\n");

    for (int i = 0; i < ESTADOS; i++) {
        float porcentagem = Percentual(coleta[i]);
        printf("%s: %.2f%%\n", coleta[i].nomes, porcentagem);
    }

    media = MediaAcidentes(coleta);

    printf("MEDIA DOS ACIDENTES: %d\n", media);
    
    ACIMA_MediaAcidentes(coleta, media);

    return 0;
}