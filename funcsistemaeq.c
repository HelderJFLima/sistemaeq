// Funções usadas no programa 'sistemaeq'


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "funcsistemaeq.h"

#define ALG_SIG 30                                  // Permite trabalhar com até (ALG_SIG - 3) algarismos significativos.

struct vetor                                        // Estrutura usada para o vetor com a solução do sistema.
{
    int n;

    double *v;
};

struct matriz                                       // Estrutura usada para a matriz aumentada do sistema.
{
    int lin;

    int col;

    double **v;
};

Vetor* cria_vetor(int comp)                         // Cria um vetor de tamanho 'comp', com alocação dinâmica.
{
    Vetor *p;

    p = (Vetor*)malloc(sizeof(Vetor));

    if (p == NULL)                                      // Verifica se houve espaço suficiente na memória.
    {
        printf("\n\n** Erro: mem%cria insuficiente para aloca%c%co! **\n\a", 162, 135, 198);

        exit(1);
    }

    p->v = (double*)calloc(comp, sizeof(double));

    if (p->v == NULL)
    {
        printf("\n\n** Erro: mem%cria insuficiente para aloca%c%co! **\n\a", 162, 135, 198);

        exit(2);
    }

    p->n = comp;

    return p;
}

Matriz* cria_matriz(int m, int n)                   // Cria uma matriz, dadas as suas dimensões, com alocação dinâmica.
{
    register int i;

    Matriz *mat;

    mat = (Matriz*)malloc(sizeof(Matriz));

    if (mat == NULL)
    {
        printf("\n\n** Erro: mem%cria insuficiente para aloca%c%co! **\n\a", 162, 135, 198);

        exit(3);
    }

    mat->lin = m;

    mat->col = n;

    mat->v = (double**)calloc(m, sizeof(double*));

    if (mat->v == NULL)
    {
        printf("\n\n** Erro: mem%cria insuficiente para aloca%c%co! **\n\a", 162, 135, 198);

        exit(4);
    }

    for (i = 0; i < m; i++)
    {
        mat->v[i] = (double*)calloc(n, sizeof(double));

        if (mat->v[i] == NULL)
        {
            printf("\n\n** Erro: mem%cria insuficiente para aloca%c%co! **\n\a", 162, 135, 198);

            exit(11 * (i + 1));                         // Permite identificar em qual ponto do loop ocorreu o problema.
        }
    }

    return mat;
}

void libera_vetor(Vetor *vet)                       // Libera o espaço usado por um vetor.
{
    if (vet != NULL)
    {
        free(vet->v);

        free(vet);
    }
}

void libera_matriz(Matriz *mat)                     // Libera o espaço usado por uma matriz.
{
    register int i;

    for (i = 0; i < mat->lin; i++)
        free(mat->v[i]);

    free(mat->v);

    free(mat);
}

Matriz* capta_matriz(char *nome)                    // Lê um arquivo txt, contendo uma matriz e grava seus valores.
{
    char str[ALG_SIG];                                  // String com espaço suficiente para se trabalhar com (ALG_SIG - 3) algarismos significativos
    int m, n, c;
    register int i, j;

    Matriz *mat;
    FILE *arqin, *arqout;

    arqin = fopen(nome, "r");                           // Abre o arquivo com os dados da matriz e testa se ele é válido.

    if (arqin == NULL)
    {
        printf("\n\n** Erro na abertura do arquivo de entrada! **\n\a");

        exit(5);
    }

    arqout = fopen("output.txt", "w");                  // Cria um arquivo para salvar os resultados.

    if (arqout == NULL)
    {
        printf("\n\n** Erro na abertura do arquivo de sa%cda! **\n\a", 161);

        exit(6);
    }

    fgets(str, ALG_SIG, arqin);

    sscanf(str, "%dx%d", &m, &n);

    if (m + 1 != n)                                     // Só é aceito o sistema com o mesmo número de equações e incógnitas.
    {
        printf("\n\n** Erro: n%cmero de equa%c%ces incompat%cvel com o de inc%cgnitas! **\n\a", 163, 135, 228, 161, 162);

        exit(7);
    }

    mat = cria_matriz(m, n);                            // Cria espaço para gravar os valores.

    for (i = 0; i < m; i++)                             // Lê o arquivo e grava os valores da matriz.
    {
        register int k;

        for (j = 0; j < n; j++)
        {
            for (k = 0; k < ALG_SIG; k++)
            {
                c = fgetc(arqin);

                if (!isspace(c) && k < ALG_SIG - 1)         // Verifica se o caractere é válido e se há espaço suficiente na string.
                    str[k] = c;

                else if (!isspace(c) && k == ALG_SIG - 1)
                    str[k] = '\0';
                else
                {
                    str[k] = '\0';

                    break;
                }
            }

            sscanf(str, " %lf", &mat->v[i][j]);
        }
    }

    fclose(arqin);

    fprintf(arqout, "\nSistema:\n\n");

    for (i = 0; i < m; i++)                             // Copia a matriz para o arquivo de saída.
    {
        for (j = 0; j < n; j++)
            fprintf(arqout, "%lf\t", mat->v[i][j]);

        fprintf(arqout, "\n");
    }

    fprintf(arqout, "\n");

    fclose(arqout);

    return mat;
}

void imprime_matriz(Matriz *mat)                    // Imprime os valores de uma matriz na tela.
{
    register int i, j;

    printf("\n\nSistema:\n\n");

    for (i = 0; i < mat->lin; i++)
    {
        for (j = 0; j < mat->col; j++)
            printf("%lf\t", mat->v[i][j]);

        printf("\n");
    }

    printf("\n");
}

void troca_linha(Matriz *mat, int a, int b)         // Troca duas linhas de uma matriz.
{
    register int j;
    double temp;

    if (a >= mat->lin || b >= mat->lin)                 // Testa se as linhas existem. Deve-se contar a partir da linha '0'.
    {
        printf("\n\n** Erro: dimens%ces incompat%cveis para troca de linhas! **\n\a", 228, 161);

        exit(8);
    }

    for (j = 0; j < mat->col; j++)
    {
        temp = mat->v[a][j];

        mat->v[a][j] = mat->v[b][j];

        mat->v[b][j] = temp;
    }
}

int sistema_determinado(Matriz *mat)                // Verifica se o sistema é determinado ou não.
{
    register int i;

    for (i = 0; i < mat->lin; i++)                      // Percorre a diagonal principal da matriz triangular superior dos coeficientes.
    {
        if (mat->v[i][i] == 0)
            return 0;                                       // Retorna '0' caso o produto dos elementos seja nulo.
    }

    return 1;                                           // Retorna '1' caso contrário.
}

int linha_a_nula(int lin, Matriz *mat)              // Verifica se há apenas elementos nulos na linha da matriz aumentada.
{
    register int j;

    if (lin >= mat->lin)                                // Testa se a linha existe. Conta-se a partir da 'linha 0'.
    {
        printf("\n\n** Erro: a linha informada n%co existe! **\n\a", 198);

        exit(9);
    }

    for (j = 0; j < mat->col; j++)
    {
        if (mat->v[lin][j] != 0)
            return 0;
    }

    return 1;
}

int linha_v_nula(int lin, Matriz *mat)              // Verifica se há apenas elementos nulos na linha da matriz de coeficientes.
{
    register int j;

    if (lin >= mat->lin)                                // Testa se a linha existe. Conta-se a partir da 'linha 0'.
    {
        printf("\n\n** Erro: a linha informada n%co existe! **\n\a", 198);

        exit(10);
    }

    for (j = 0; j < mat->col - 1; j++)                  // Desconsidera a última linha, dos termos independentes.
    {
        if (mat->v[lin][j] != 0)
            return 0;
    }

    return 1;
}

int carac_a(Matriz *mat)                            // Calcula a característica da matriz aumentada.
{
    register int i;
    int n = mat->lin;

    for (i = 0; i < mat->lin; i++)
    {
        if (linha_a_nula(i, mat))
            n--;
    }

    return n;
}

int carac_v(Matriz *mat)                            // Calcula a característica da matriz de coeficientes.
{
    register int i;
    int n = mat->lin;

    for (i = 0; i < mat->lin; i++)
    {
        if (linha_v_nula(i, mat))
            n--;
    }

    return n;
}

void imprime_resultado(Vetor *vet, Matriz *sist)    // Mostra o resultado e o salva no arquivo de saída.
{
    register int i;

    FILE *arqout;

    arqout = fopen("output.txt", "a");                  // Abre o arquivo de saída para salvar os resultados.

    if (arqout == NULL)
    {
        printf("\n\n** Erro na abertura do arquivo de sa%cda! **\n\a", 161);

        exit(11);
    }

    printf("\n\nSolu%c%co:\n\n", 135, 198);

    fprintf(arqout, "\nSolu%c%co:\n\n", 231, 227);

    if (vet == NULL)                                    // Caso em que o sistema não é determinado.
    {
        int ca, cv;

        ca = carac_a(sist);                                 // As características permitem determinar se o sistema
                                                            // é impossível ou não.
        cv = carac_v(sist);

        if (ca < cv)                                        // Testa se o cálculo foi coerente.
        {
            printf("\n\n** Erro no c%clculo da caracter%cstica! **\n\a", 160, 161);

            exit(12);
        }
        else if (ca > cv)                                   // Sistema impossível
        {
            printf("O sistema de equa%c%ces %c imposs%cvel.\n", 135, 228, 130, 161);

            fprintf(arqout, "O sistema de equa%c%ces %c imposs%cvel.\n", 231, 245, 233, 237);
        }
        else
        {
            if (ca > sist->lin)                             // Testa, novamente, se o cálculo foi coerente.
            {
                printf("\n\n** Erro no c%clculo da caracter%cstica! **\n\a", 160, 161);

                exit(13);
            }
            else if (ca < sist->lin)                        // Sistema indeterminado
            {
                printf("O sistema de equa%c%ces %c poss%cvel e indeterminado.", 135, 228, 130, 161);

                printf("\n\nGrau de liberdade: %d\n", sist->lin - ca);

                fprintf(arqout, "O sistema de equa%c%ces %c poss%cvel e indeterminado.", 231, 245, 233, 237);

                fprintf(arqout, "\n\nGrau de liberdade: %d\n", sist->lin - ca);
            }
            else                                            // Redundância proposital para teste (sistema determinado)
            {
                printf("O sistema de equa%c%ces %c poss%cvel e determinado.\n", 135, 228, 130, 161);

                fprintf(arqout, "O sistema de equa%c%ces %c poss%cvel e determinado.\n", 231, 245, 233, 237);
            }
        }
    }
    else                                                // Caso em que o sistema é determinado.
    {
        for (i = 0; i < vet->n; i++)
        {
            printf("x%d: %lf\n", i + 1, vet->v[i]);

            fprintf(arqout, "x%d: %lf\n", i + 1, vet->v[i]);
        }
    }

    fclose(arqout);
}

Vetor* soluciona_sistema(Matriz *mat)               // Algoritmo de Gauss
{
    register int i, j, k;

    Vetor *p;

    for (i = 0; i < mat->lin; i++)                      // Transforma a matriz do sistema em uma matriz triangular superior.
    {
        if (mat->v[i][i] == 0 && i < mat->lin - 1)          // Verifica se o elemento da diagonal principal não é zero.
        {
            for (k = i + 1; k < mat->lin; k++)
            {
                if (mat->v[k][i] != 0)
                {
                    troca_linha(mat, i, k);                     // Troca as linhas se for necessário e possível.

                    break;
                }
            }
        }

        if (mat->v[i][i] != 0)                              // Realiza a seqüência de operações elementares na matriz aumentada do sistema.
        {
            for (j = mat->col - 1; j >= i; j--)
                mat->v[i][j] /= mat->v[i][i];

            if (i < mat->lin - 1)
            {
                for (k = i + 1; k < mat->lin; k++)
                {
                    for (j = mat->col - 1; j >= i; j--)
                        mat->v[k][j] += -(mat->v[k][i]) * (mat->v[i][j]);
                }
            }
        }
    }

    if (!sistema_determinado(mat))                      // Testa se o sistema é determinado.
    {
        printf("\n\nSistema de equa%c%ces n%co-determinado!\n\n", 135, 228, 198);

        return NULL;
    }
    else                                                    // Caso seja determinado, calcula as incógnitas.
    {
        p = cria_vetor(mat->lin);

        p->n = mat->lin;

        for (i = p->n - 1; i >= 0; i--)
        {
            p->v[i] = mat->v[i][mat->col - 1];

            for (j = i + 1; j < mat->col; j++)
                p->v[i] -= mat->v[i][j] * p->v[j];

            p->v[i] /= mat->v[i][i];
        }
    }

    return p;
}