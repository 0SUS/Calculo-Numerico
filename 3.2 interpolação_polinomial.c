#include <stdio.h>

/*
    Interpolação de Lagrange: A interpolação de Lagrange cria um polinômio único que passa por todos os pontos dados.
        Esse método utiliza uma combinação de polinômios básicos de Lagrange para construir o polinômio de interpolação.

        Vantagens:
            - Simplicidade na implementação.
                - Não exige a pré-calculação de coeficientes intermediários.
                - Não exige uso de uma tabela de diferenças divididas
            - Ele é direto e útil para interpolar um valor quando se conhece um conjunto de pontos fixos.

        Desvantagens:
            - O cálculo pode ser computacionalmente caro e sujeito a erros numéricos.
            - O polinômio completo precisa ser recalculado se um novo ponto for adicionado.
    

    Interpolação de Newton: Utiliza um método incremental de diferenças divididas, o que permite construir o polinômio de forma
        progressiva. Ao calcular as diferenças divididas entre os pontos, o método cria coeficientes que formam um polinômio interpolador.

        Vantagens: 
            - Flexibilidade e eficiência computacional, especialmente em situações onde novos pontos podem ser adicionados.
            - A estrutura de diferenças divididas é mais estável numericamente do que a fórmula de Lagrange em muitos casos.

        Desvantagem:
            - A implementação é mais complexa.
                - Envolve o cálculo das diferenças divididas e a construção do polinômio por multiplicação sucessiva
            - Depende da ordem dos pontos, pois os coeficientes são calculados com base nessa ordem.

*/


#define N 5 // Número de pontos

// Função de Interpolação de Lagrange
double lagrange_interpolation(double x[], double y[], int n, double x_value) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        double term = y[i];
        for (int j = 0; j < n; j++) {
            if (j != i)
                term *= (x_value - x[j]) / (x[i] - x[j]);
        }
        result += term;
    }
    return result;
}

// Função para calcular as diferenças divididas para a interpolação de Newton
void divided_differences(double x[], double y[], double coef[], int n) {
    for (int i = 0; i < n; i++) {
        coef[i] = y[i];
    }
    for (int j = 1; j < n; j++) {
        for (int i = n - 1; i >= j; i--) {
            coef[i] = (coef[i] - coef[i - 1]) / (x[i] - x[i - j]);
        }
    }
}

// Função de Interpolação de Newton
double newton_interpolation(double x[], double coef[], int n, double x_value) {
    double result = coef[n - 1];
    for (int i = n - 2; i >= 0; i--) {
        result = result * (x_value - x[i]) + coef[i];
    }
    return result;
}

int main() {
    double x[N] = {0.25, 0.75, 1.25, 1.5, 2.0}; // Valores de corrente
    double y[N] = {-0.45, -0.60, 0.70, 1.88, 6.0}; // Valores de tensão
    
    double x_value = 1.15; // Ponto onde queremos interpolar
    double coef[N]; // Coeficientes para o método de Newton
    
    // Interpolação de Lagrange
    double lagrange_result = lagrange_interpolation(x, y, N, x_value);
    printf("Interpolação de Lagrange em x = %.2f: %.4f\n", x_value, lagrange_result);
    
    // Interpolação de Newton
    divided_differences(x, y, coef, N);
    double newton_result = newton_interpolation(x, coef, N, x_value);
    printf("Interpolação de Newton em x = %.2f: %.4f\n", x_value, newton_result);
    
    return 0;
}