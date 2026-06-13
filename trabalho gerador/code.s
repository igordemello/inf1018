    .globl retorna
retorna:
    push %rbp          /* salva o rbp antigo */
    mov  %rsp, %rbp    /* novo frame, pilha alinhada */
    mov  %edi, %eax    /* copia o 1o argumento (edi) pro retorno (eax) */
    leave              /* desfaz o frame */
    ret                /* volta pro chamador */
