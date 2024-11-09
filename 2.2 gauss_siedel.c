#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*
    Resolvendo o problema, encontramos uma matriz 7x7 que inicialmente não estava diagonalmente dominante, mas, fazendo alguns ajustes, tem-se: 

    0.7071 0 -0.7071 -1 0 0 0                              F1                          =                              0
    0.7071 0.7071 0 0 0 0 0                                F2                          =                            -500   
    0 0 1 0.5 -0.8660 0 0                                  F3                          =                              0
    0 0 0 0.8660 -0.5 0 0                                  F4                          =                            -100
    0 0 -0.7071 0 -0.8660 0 0                              F5                          =                              0
    0 0 0 0 0.8660 1 0                                     F6                          =                              0
    0 1 0.7071 0 -0.5 0 - 1                                F7                          =                              0

    Logo, tem-se o sistema: 

    0.7071F1 - 0.7071F3 - F4 = 0
    0.7071F1 + 0.7071F2 = -500
    F3 + 0.5F4 - 0.8660F5 = 0
    0.8660F4 -0.5F5 = -100
    -0.7071F3 - 0.8660F5 = 0
    0.8660F5 + F6 = 0
    F2 + 0.7071 -0.5F5 -F7 = 0

*/




#define N 7 // Número de variáveis (ajuste conforme o sistema)
#define PRECISION 0.0001 // Precisão de 0,0001

// Função para verificar o critério de Sassenfeld para convergência
bool verificaSassenfeld(double matriz[N][N]) {
    double beta[N] = {0};
    for (int i = 0; i < N; i++) {
        double soma = 0.0;
        for (int j = 0; j < N; j++) {
            if (i != j) {
                soma += fabs(matriz[i][j]) * beta[j];
            }
        }
        beta[i] = soma / fabs(matriz[i][i]);
        if (beta[i] >= 1) return false; // Critério de Sassenfeld não atendido
    }
    return true;
}

// Função para o método de Gauss-Seidel
void gaussSeidel(double matriz[N][N], double termosIndep[N], double solucao[N]) {
    double novo[N];
    bool convergiu;

    for (int i = 0; i < N; i++) solucao[i] = 0; // Inicializa a solução com zeros

    do {
        convergiu = true;
        for (int i = 0; i < N; i++) {
            novo[i] = termosIndep[i];
            for (int j = 0; j < N; j++) {
                if (j != i) {
                    novo[i] -= matriz[i][j] * solucao[j];
                }
            }
            novo[i] /= matriz[i][i];
            if (fabs(novo[i] - solucao[i]) > PRECISION) {
                convergiu = false;
            }
            solucao[i] = novo[i];
        }
    } while (!convergiu);
}

int main() {
    double matriz[N][N] = {
        // Exemplo de matriz de coeficientes baseada no sistema
        {0.7071, 0, -0.7071, -1, 0, 0, 0},
        {0.7071, 0.7071, 0, 0, 0, 0, 0},
        {0, 0, 1, 0.5, -0.8660, 0, 0},
        {0, 0, 0, 0.8660, -0.5, 0, 0},
        {0, 0, -0.7071, 0, -0.8660, 0, 0},
        {0, 0, 0, 0, 0.8660, 1, 0},
        {0, 1, 0.7071, 0, -0.5, 0, -1}        
    };
    double termosIndep[N] = {0, -500, 0, -100, 0, 0, 0}; // Termos independentes (ajuste conforme necessário)
    double solucao[N];

    // Verifica o critério de Sassenfeld antes de resolver
    if (!verificaSassenfeld(matriz)) {
        printf("O sistema pode não convergir com Gauss-Seidel (critério de Sassenfeld não atendido).\n");
        return 1;
    }

    //variando a força aplicada
    
    /*for(int i = 0; i<N; i++)
        scanf("%lf", &termosIndep[i]);*/

    // Resolve o sistema usando Gauss-Seidel
    gaussSeidel(matriz, termosIndep, solucao);

    // Exibe a solução
    printf("Solucoes:\n");
    for (int i = 0; i < N; i++) {
        printf("F%d = %.5f\n", i + 1, solucao[i]);
    }

    return 0;
}
