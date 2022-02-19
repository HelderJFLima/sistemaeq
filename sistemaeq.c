// Programa para resolver sistemas de equa��es pelo m�todo de Gauss
// � preciso que o n�mero de equa��es seja igual ao de inc�gnitas.

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