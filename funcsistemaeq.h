// Funções usadas no programa 'sistemaeq'


// Tipo exportado para usar vetores
typedef struct vetor Vetor;

// Tipo exportado para usar matrizes
typedef struct matriz Matriz;

// Cria um vetor de tamanho 'n', com alocação dinâmica.
//
Vetor* cria_vetor(int comp);

// Cria uma matriz, dadas as suas dimensões, com alocação dinâmica.
//
Matriz* cria_matriz(int m, int n);

// Libera o espaço usado por um vetor.
//
void libera_vetor(Vetor *vet);

// Libera o espaço usado por uma matriz.
//
void libera_matriz(Matriz *mat);

// Troca duas linhas de posição em uma matriz.
// Deve-se contar as linhas a partir da 'linha 0'.
//
void troca_linha(Matriz *mat, int a, int b);

// Verifica se o sistema de equações é determinado ou não a partir
// da análise da diagonal principal da matriz dos seus coeficientes,
// após ela ter sido transformada em triangular superior.
// Retorna '1' no caso verdadeiro e '0' no falso.
//
int sistema_determinado(Matriz *mat);

// Verifica se há apenas elementos nulos na linha da matriz aumentada.
// Deve-se contar a partirda 'linha 0'.
// Retorna '1' no caso verdadeiro e '0' no falso.
//
int linha_a_nula(int lin, Matriz *mat);

// Verifica se há apenas elementos nulos na linha da matriz de coeficientes.
// Deve-se contar a partirda 'linha 0'.
// Retorna '1' no caso verdadeiro e '0' no falso.
//
int linha_v_nula(int lin, Matriz *mat);

// Calcula a característica da matriz aumentada.
// Retorna o número de linhas não-nulas na matriz aumentada.
//
int carac_a(Matriz *mat);

// Calcula a característica da matriz de coeficientes.
// Retorna o número de linhas não-nulas na matriz de coeficientes.
//
int carac_v(Matriz *mat);

// Lê um arquivo txt, contendo uma matriz e grava seus valores.
//
Matriz* capta_matriz(char *nome);

// Imprime os valores de uma matriz na tela.
//
void imprime_matriz(Matriz *mat);

// Mostra o resultado e o salva no arquivo de saída.
//
void imprime_resultado(Vetor* vet, Matriz *sist);

// Resolve o sistema de equações usando o método de Gauss.
// Retorna um ponteiro para um vetor contendo as soluções.
//
Vetor* soluciona_sistema(Matriz *mat);