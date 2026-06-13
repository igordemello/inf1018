/* Igor Oliveira de Mello - 2512779 - 3WB */
/* Rafael Carvalho Solberg - 2511672 - 3WB */

#include <stdio.h>
#include <string.h>
#include "cria_func.h"
 
int dobro(int x) {
    return x * 2;
}

int mult(int x, int y){
    return x * y;
}

int sub(int a, int b){
    return a - b;
}

int soma3(int a, int b, int c){
    return a + b + c;
}
int primeiro(char* s){
    return (int) s[0];
}
 
char fixa[] = "quero saber se a outra string e um prefixo dessa";
 
int main(void) {
    unsigned char codigo[500];
    DescParam params[3];
    int falhas = 0;
 
    /* A) 1 param, FIX: ignora a entrada, usa a constante */
    {
        printf("INICIANDO TESTE A\n");
        int (*g)(int);
        params[0].tipo_val = INT_PAR; params[0].orig_val = FIX;
        params[0].valor.v_int = 21;
        cria_func(dobro, params, 1, codigo);
        g = (int(*)(int)) codigo;
        int r = g(999);
        printf("A FIX 1-param: %d (esp 42) %s\n", r, r==42?"OK":(falhas++,"FALHOU"));
    }
 
    /* B) 1 param, IND com PONTEIRO (PTR_PAR): le o ponteiro atual */
    {
        printf("INICIANDO TESTE B\n");
        int (*g)(void);
        char* msg;
        params[0].tipo_val = PTR_PAR; params[0].orig_val = IND;
        params[0].valor.v_ptr = &msg;
        cria_func(primeiro, params, 1, codigo);
        g = (int(*)(void)) codigo;
        msg = "Abc"; int r1 = g();
        msg = "Xyz"; int r2 = g();
        printf("B IND ponteiro:  %d,%d (esp 65,88) %s\n", r1, r2, (r1=='A'&&r2=='X')?"OK":(falhas++,"FALHOU"));
    }
 
    /* C) 2 params, ambos PARAM: checa repasse e ordem */
    {
        printf("INICIANDO TESTE C\n");
        int (*g)(int,int);
        params[0].tipo_val = INT_PAR; params[0].orig_val = PARAM;
        params[1].tipo_val = INT_PAR; params[1].orig_val = PARAM;
        cria_func(sub, params, 2, codigo);
        g = (int(*)(int,int)) codigo;
        int r = g(10, 3);
        printf("C PARAM,PARAM:   %d (esp 7) %s\n", r, r==7?"OK":(falhas++,"FALHOU"));
    }
 
    /* D) 3 params: FIX, IND, PARAM */
    {
        printf("INICIANDO TESTE D\n");
        int (*g)(int);
        int v;
        params[0].tipo_val = INT_PAR; params[0].orig_val = FIX;   params[0].valor.v_int = 100;
        params[1].tipo_val = INT_PAR; params[1].orig_val = IND;   params[1].valor.v_ptr = &v;
        params[2].tipo_val = INT_PAR; params[2].orig_val = PARAM;
        cria_func(soma3, params, 3, codigo);
        g = (int(*)(int)) codigo;
        v = 20; int r = g(3);
        printf("D FIX,IND,PARAM: %d (esp 123) %s\n", r, r==123?"OK":(falhas++,"FALHOU"));
    }
 
    /* E) vezes10: PARAM, FIX */
    {
        printf("INICIANDO TESTE E\n");
        int (*g)(int);
        params[0].tipo_val = INT_PAR; params[0].orig_val = PARAM;
        params[1].tipo_val = INT_PAR; params[1].orig_val = FIX; params[1].valor.v_int = 10;
        cria_func(mult, params, 2, codigo);
        g = (int(*)(int)) codigo;
        int r = g(7);
        printf("E vezes10: %d (esp 70) %s\n", r, r==70?"OK":(falhas++,"FALHOU"));
    }
 
    /* F) memcmp: 3 params, caso embaralhado (FIX, PARAM, PARAM) */
    {
        printf("INICIANDO TESTE F\n");
        int (*g)(void*, size_t);
        char s[] = "quero saber tudo";
        params[0].tipo_val = PTR_PAR; params[0].orig_val = FIX;   params[0].valor.v_ptr = fixa;
        params[1].tipo_val = PTR_PAR; params[1].orig_val = PARAM;
        params[2].tipo_val = INT_PAR; params[2].orig_val = PARAM;
        cria_func(memcmp, params, 3, codigo);
        g = (int(*)(void*, size_t)) codigo;
        int p12 = (g(s, 12) == 0);
        int p16 = (g(s, strlen(s)) == 0);
        printf("F memcmp prefixo: %s,%s (esp SIM,NAO) %s\n",p12?"SIM":"NAO", p16?"SIM":"NAO",(p12 && !p16)?"OK":(falhas++,"FALHOU"));
    }
 
    printf("\n%s\n", falhas==0 ? "todos os testes passaram" : "houve falhas");
    return falhas;
}