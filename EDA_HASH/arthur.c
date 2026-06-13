#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define C 31 //constante C para o metodo hash de char para um valor inteiro
#define A 2654435761 //constante para valores inteiros 
#define M 4919 //numero proximo de 4,916 (numero de cpfs + 20% de sobra) e primo
#define N 4096 //quantidade de CPFs a serem inseridos
#define K 13 // 2^13 (para o metodo da dobra)
#define TAM_CPF 12 //11 digitos + '\0'

//struct dos dados a serem armazenados
typedef struct {
    char CPF[TAM_CPF];

} CPFs;



//HASH 1 método de multiplicação + divisão
unsigned int multiplicabinario(unsigned int cpf)
{
    unsigned int codigo = cpf*A;
    codigo = codigo % M;

    return codigo;
}

//função para gerar um valor inteiro a partir de cada string de CPF
unsigned int stringtoint(char cpf[])
{
    unsigned int valor = 0;
    for (int i = 0; cpf[i] != '\0'; i++)
    {
        valor = valor*C + cpf[i];
    }
    return valor;

}

//HASH2 DobraBinária com alguns ajustes
unsigned int dobrabinaria(unsigned int cpf)
{
    unsigned int p1 = cpf >> K; 
    unsigned int p2 = cpf << (32 - K);  
    p2 = p2 >> (32 - K);
    int codigo = p1 ^ p2; 
    return 1+ (codigo % (M-1)); // +1 garante que não vai ser 0 -> loop infinito, M-1 -> evita loop infinito com número primo

}

//Endereçamento aberto utilizando a disperção dupla
unsigned int dispercaodupla(unsigned int cpf, int quantidade)
{
    unsigned int codigo = (multiplicabinario(cpf) + quantidade*(dobrabinaria(cpf))) % M; 
    return codigo;
}

//função para criar a tabela hash
int criarHash(char tabela_CPF[N][TAM_CPF], int i, CPFs tabela_HASH[M])
{
    int colisoes = 0;
    for (int j = 0; j < i; ++j)
    {
        int indice = stringtoint(tabela_CPF[j]);
        indice = multiplicabinario(indice);
        int quantidade = 1;

        if (tabela_HASH[indice].CPF[0] != '\0')
        {
            while (tabela_HASH[indice].CPF[0] != 0)
            {
                indice = stringtoint(tabela_CPF[j]);
                indice = dispercaodupla(indice,quantidade);
                ++quantidade;
                ++colisoes;
            }
            strcpy(tabela_HASH[indice].CPF, tabela_CPF[j]);
        }

        else
            strcpy(tabela_HASH[indice].CPF, tabela_CPF[j]);
    }
    return colisoes;

}

int main(void)
{
    int colisoes = 0;

    CPFs tabela_HASH[M] = {0};

    CPFs  tabela_HASH_COPIA1[M] = {0};
    CPFs  tabela_HASH_COPIA2[M] = {0};
    CPFs  tabela_HASH_COPIA3[M] = {0};
    CPFs  tabela_HASH_COPIA4[M] = {0};
    CPFs  tabela_HASH_COPIA5[M] = {0};
    CPFs  tabela_HASH_COPIA6[M] = {0};
    CPFs  tabela_HASH_COPIA7[M] = {0};


    char tabela_CPF[M][TAM_CPF];

    FILE* arquivo_CPF = fopen("CPFsValidos.txt","rt");
    int i = 0;
    while(fscanf(arquivo_CPF, " %s", tabela_CPF[i])==1)
    {
        ++i;
    }
    fclose(arquivo_CPF);


    //testes gerais com menos inclusoes
    printf("100 INCLUSOES \n");
    colisoes = criarHash(tabela_CPF, 100, tabela_HASH_COPIA1);
    printf("colisoes: %d\n \n", colisoes);

    printf("\n200 INCLUSOES \n");
    colisoes = criarHash(tabela_CPF, 200, tabela_HASH_COPIA2);
    printf("colisoes: %d \n \n", colisoes);

    printf("\n300 INCLUSOES \n");
    colisoes = criarHash(tabela_CPF, 300, tabela_HASH_COPIA3);
    printf("colisoes: %d\n \n", colisoes);

    printf("\n500 INCLUSOES \n");
    colisoes = criarHash(tabela_CPF, 500, tabela_HASH_COPIA4);
    printf("colisoes: %d \n \n", colisoes);

    printf("\n1000 INCLUSOES \n");
    colisoes = criarHash(tabela_CPF, 1000, tabela_HASH_COPIA5);
    printf("colisoes: %d \n \n", colisoes);

    printf("\n2000 INCLUSOES \n");
    colisoes = criarHash(tabela_CPF, 2000, tabela_HASH_COPIA6);
    printf("colisoes: %d \n \n", colisoes);

    printf("\n3000 INCLUSOES \n");
    colisoes = criarHash(tabela_CPF, 3000, tabela_HASH_COPIA7);
    printf("colisoes: %d \n \n", colisoes);


    // TESTE GERAL OFICIAL PARA O 4096
    colisoes = criarHash(tabela_CPF, 4096, tabela_HASH);

    printf("\n4096 INCLUSOES \n");
    printf("colisoes: %d \n", colisoes);

    return 0;
}