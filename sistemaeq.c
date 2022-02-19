// Programa para resolver sistemas de equações pelo método de Gauss
// É preciso que o número de equações seja igual ao de incógnitas.

#include "funcsistemaeq.h"

int main()
{
    Vetor *soluc;
    Matriz *sistema;

    sistema = capta_matriz("sistema.txt");

    imprime_matriz(sistema);

    soluc = soluciona_sistema(sistema);

    imprime_matriz(sistema);

    imprime_resultado(soluc, sistema);

    libera_matriz(sistema);

    libera_vetor(soluc);

    return 0;
}