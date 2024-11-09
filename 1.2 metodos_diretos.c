#include <stdio.h>

/*
    a.
    
    x1 -> qt. de componentes do tipo 1 produzidos por dia;
    x2 -> qt. de componentes do tipo 2 produzidos por dia;
    x3 -> qt. de componentes do tipo 3 produzidos por dia.

    -------------------------------------------------------

    total de metal disponível por dia:    X;
    total de plástico disponível por dia: Y;
    total de borracha disponível por dia: Z.

    -------------------------------------------------------

    As equações são formadas com base no consumo de material por cada tipo de componente:

    1. Metal:    M1.x1 + M2.x2 + M3.x3 = X;
    2. Plastico: P1.x1 + P2.x2 + P3.x3 = Y;
    3. Borracha: B1.x1 + B2.x2 + B3.x3 = Z;

    Assim o sistema fica:
    
    |
    | M1.x1 + M2.x2 + M3.x3 = X
    | P1.x1 + P2.x2 + P3.x3 = Y
    | B1.x1 + B2.x2 + B3.x3 = Z
    |

    Usando os dados do problema como exemplo:

    |
    |  15.x1 +  17.x2 +   19.x3 = 3,89
    | 0,3.x1 + 0,4.x2 + 0,55.x3 = 0,095
    | 1,0.x1 + 1,2.x2 + 1,5.x3  = 0,282
    |
*/

// b. & c.

#define N 3 // número de variáveis(número de equações)

void gauss_elimination(float a[N][N+1], float x[N]) {
    int i, j, k;
    float ratio;

    // eliminação para tornar a matriz em triangular superior
    for (i = 0; i < N - 1; i++) {
        for (j = i + 1; j < N; j++) {
            ratio = a[j][i] / a[i][i];
            for (k = 0; k <= N; k++) {
                a[j][k] -= ratio * a[i][k];
            }
        }
    }

    // substituição regressiva para encontrar as soluções
    x[N-1] = a[N-1][N] / a[N-1][N-1];
    for (i = N - 2; i >= 0; i--) {
        x[i] = a[i][N];
        for (j = i + 1; j < N; j++) {
            x[i] -= a[i][j] * x[j];
        }
        x[i] = x[i] / a[i][i];
    }
}

int main(){
    int i,j;
    // matriz aumentada do sistema de equações
    float a[N][N + 1];

    // array para armazenar as soluções
    float x[N];

    // quais os tipos de materiais
    char *s[10] = {
        "Metal",
        "Plastico",
        "Borracha"
    };

    for(i = 0; i < N; i++){
        printf("Consumo em gramas pelo componente %d de: \n", i + 1);
        for(j = 0; j<N; j++){
            printf("\t%s: ", s[j]);
            scanf(" %f", &a[j][i]);
        }
    }

    printf("\nTotal dos materiais disponiveis no dia: \n");
    
    for(i = 0; i < N; i++){
        printf("%s: ", s[i]);
        scanf(" %f", &a[i][N]);
    }

    /*printf("\n");
    for(int i = 0; i < N; i++){
        for(int j = 0; j < (N + 1); j++){
            printf("%10.3f", a[i][j]);
        }
        printf("\n");
    }*/

    gauss_elimination(a, x);

    printf("\nQuantidade de cada tipo de componente:\n");
    for (i = 0; i < N; i++) {
        printf("Componente %d = %.4f\n", i+1, x[i]);
    }

}