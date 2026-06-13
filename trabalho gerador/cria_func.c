/* Igor Oliveira de Mello - 2512779 - 3WB */
/* Rafael Carvalho Solberg - 2511672 - 3WB */
 
#include <string.h>
#include "cria_func.h"
 
void cria_func (void* f, DescParam params[], int n, unsigned char codigo[]) {
    int i = 0;
    int s;
    int n_param = 0;
    int param_ordem[3];
 
    const unsigned char MOVABS[3] = {0xbf, 0xbe, 0xba}; /* movabs $imm, REG */
    const unsigned char MEM2REG[3] = {0x38, 0x30, 0x10}; /* mov (%rax), REG */
    const unsigned char RBP_REG[3] = {0x7d, 0x75, 0x55}; /* modrm p/ disp(%rbp) */
    const unsigned char disp[3] = {0xf8, 0xf0, 0xe8}; /* -8, -16, -24 */
 
    codigo[i++] = 0x55; /* push %rbp */
    codigo[i++] = 0x48; codigo[i++] = 0x89; codigo[i++] = 0xe5;  /* mov %rsp,%rbp  */
    codigo[i++] = 0x48; codigo[i++] = 0x83; codigo[i++] = 0xec; codigo[i++] = 0x20; /* sub $32,%rsp */
 
    /*salva na pilha os argumentos PARAM recebidos, eles chegam em rdi, rsi, rdx, na ordem em que aparecem em params[] */
    for (s = 0; s < n; s++) {
        if (params[s].orig_val == PARAM) {
            param_ordem[s] = n_param;
            codigo[i++] = 0x48; codigo[i++] = 0x89;/* mov REG, disp(%rbp) */
            codigo[i++] = RBP_REG[n_param];
            codigo[i++] = disp[n_param];
            n_param++;
        }
    }
 
    /* monta cada registrador alvo (slot s -> rdi/rsi/rdx)*/
    for (s = 0; s < n; s++) {
        DescParam p = params[s];
 
        if (p.orig_val == FIX) {
            long val = (p.tipo_val == INT_PAR) ? (long) p.valor.v_int : (long) p.valor.v_ptr;
            codigo[i++] = 0x48; codigo[i++] = MOVABS[s]; /* movabs $val, REG */
            memcpy(&codigo[i], &val, 8); i += 8;
 
        }
        else if (p.orig_val == IND) {
            void* addr = p.valor.v_ptr;
            codigo[i++] = 0x48; codigo[i++] = 0xb8; /* movabs $addr, %rax */
            memcpy(&codigo[i], &addr, 8); i += 8;
            if (p.tipo_val == INT_PAR) {
                codigo[i++] = 0x8b; codigo[i++] = MEM2REG[s]; /* mov (%rax), REG32 */
            }
            else {
                codigo[i++] = 0x48; codigo[i++] = 0x8b; codigo[i++] = MEM2REG[s]; /* mov (%rax), REG64 */
            }
 
        }
        else {
            int j = param_ordem[s];
            codigo[i++] = 0x48; codigo[i++] = 0x8b; /* mov disp(%rbp), REG */
            codigo[i++] = RBP_REG[s]; /* destino: registrador do slot s */
            codigo[i++] = disp[j]; /* origem: o PARAM salvo nr j */
        }
    }
 
    codigo[i++] = 0x48; codigo[i++] = 0xb8; /* movabs $f, %rax */
    memcpy(&codigo[i], &f, 8); i += 8;
    codigo[i++] = 0xff; codigo[i++] = 0xd0; /* call *%rax      */
 
    codigo[i++] = 0xc9; /* leave */
    codigo[i++] = 0xc3; /* ret */
}