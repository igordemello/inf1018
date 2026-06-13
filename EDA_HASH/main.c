#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4919
#define MAX_CPFS 4096
#define ARQUIVO "CPFsValidos.txt"
#define PASSO 100
#define TAM_CPF 12

static char cpfs[MAX_CPFS][TAM_CPF];
static int  ocupado[N];

typedef unsigned long long ull;
typedef long long ll;

int le_cpfs(void)
{
    FILE *f = fopen(ARQUIVO, "r");
    if (!f) {
        printf("Erro ao abrir '%s'\n", ARQUIVO);
        exit(1);
    }
    int n = 0;
    while (n < MAX_CPFS && fscanf(f, " %11s", cpfs[n]) == 1)
    {
        n++;
    }
    fclose(f);
    return n;
}

static ull cpf_num(const char *s)
{
    ull v = 0;
    while (*s) {
        if (*s >= '0' && *s <= '9')
            v = v * 10 + (*s - '0');
        s++;
    }
    return v;
}

static int h1(const char *s)
{
    ull x = cpf_num(s);
    return (int)((x * 2654435761ULL) % N);
}

static int h2(const char *s)
{
    ull x = cpf_num(s);
    x = (x >> 17) ^ (x >> 5) ^ x;
    return 1 + (int)(x % (N - 1));
}

int insere(const char *cpf)
{
    int pos  = h1(cpf);
    int step = h2(cpf);
    int col  = 0;

    while (ocupado[pos]) {
        pos = (pos + step) % N;
        col++;
        if (col == N) {
            printf("\ntabela cheia\n");
            exit(1);
        }
    }
    ocupado[pos] = 1;
    return col;
}

int main(void)
{
    int total = le_cpfs();
    printf("Lidos %d CPFs\n\n", total);

    memset(ocupado, 0, sizeof(ocupado));

    ll acum = 0;

    for (int i = 0; i < total; i++) {
        acum += insere(cpfs[i]);

        int n = i + 1;
        if (n % PASSO == 0 || n == total)
        {
            printf("%d;%lld\n", n, acum);
        }
    }

    printf("\n\nN (tamanho da tabela) = %d\n", N);
    printf("Chaves inseridas = %d\n", total);
    printf("Fator de carga = %.3f\n", (double)total / N);
    printf("Colisoes totais = %lld\n", acum);

    return 0;
}