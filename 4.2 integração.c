#include <stdio.h>

#define N 5 // Número de intervalos

/*
    Regra do Trapézio:  A Regra do Trapézio aproxima a área sob a curva usando segmentos de reta
        entre os pontos. Para cada intervalo [x(i), x(i + 1)], a area calculada considerando o trapézio formado
        pelas alturas f(x(i)) e f(x(i + 1)).

        Vantagens:
            - É simples de implementar e rápida, especialmente quando os pontos estão igualmente espaçados.
            - Funciona bem para funções que variam de forma mais linear.

        Desvantagens:
            - Pode ser imprecisa quando a função a ser integrada tem curvas acentuadas ou grandes variações entre os pontos.
            - A regra do trapézio pode subestimar ou superestimar a área devido à simplicidade da aproximação


    Regra de Simpson: A Regra de Simpson aproxima a área sob a curva usando parábolas em vez de retas.
        Ela calcula a área combinando pares de intervalos, ajustando uma parábola que passa por três
        pontos consecutivos ( x(i), f(x(i)) ), ( x(i + 1), f(x(i + 1)) ) e ( x(i + 2), f(x(i + 2)) ).
        Essa regra exige um número ímpar de subintervalos.

        Vantagens: 
            - Geralmente é mais precisa que a do Trapézio, pois a parábola ajustada entre três pontos pode capturar melhor as curvaturas e variações da função.
            - Útil para funções suaves e contínuas, onde as mudanças entre os pontos podem ser representadas de forma mais natural por curvas.

        Desvantagem:
            - É menos eficiente para dados "ruidosos" ou irregulares, pois a suposição de continuidade suave pode não se aplicar bem.
            - Requer um número ímpar de subintervalos, o que pode ser uma limitação em alguns conjuntos de dados.
*/

// area usando a regra do trapézio

double trapezoidal_rule(double x[], double M1[], double M2[], int n) {
    double area = 0.0;
    for (int i = 0; i < n - 1; i++) {
        double h = x[i+1] - x[i];
        double avg_height = (M2[i] - M1[i] + M2[i+1] - M1[i+1]) / 2.0;
        area += avg_height * h;
    }
    return area;
}

// area usando a regra de simpson

double simpson_rule(double x[], double M1[], double M2[], int n) {
    if (n % 2 == 0) {
        printf("A regra de Simpson requer um número ímpar de intervalos.\n");
        return -1;
    }
    
    double area = 0.0;
    double h = (x[n-1] - x[0]) / (n - 1);
    
    for (int i = 0; i < n; i++) {
        double yi = M2[i] - M1[i];
        if (i == 0 || i == n - 1) {
            area += yi;
        } else if (i % 2 == 0) {
            area += 2 * yi;
        } else {
            area += 4 * yi;
        }
    }
    
    area = area * h / 3.0;
    return area;
}

int main() {
    double x[N] = {0, 10, 20, 30, 40};
    double M1[N] = {50.8, 86.2, 136, 72.8, 51};
    double M2[N] = {113.6, 144.5, 185, 171.2, 95.3};
    
    double area_trapezoidal = trapezoidal_rule(x, M1, M2, N);
    double area_simpson = simpson_rule(x, M1, M2, N);
    
    printf("Área aproximada (Regra do Trapézio): %.2f metros quadrados\n", area_trapezoidal);
    printf("Área aproximada (Regra de Simpson): %.2f metros quadrados\n", area_simpson);
}