#include <stdio.h>

int odd_ones(unsigned int x) {
    int aux = 0;
    while(x != 0x00000000)
    {
        aux = (x & 1)^aux;
        x = x >> 1;
    }
    return aux;
}


int main() {
    printf("%x tem numero %s de bits\n",0x01010101,odd_ones(0x01010101) ? "impar":"par");
    printf("%x tem numero %s de bits\n",0x01030101,odd_ones(0x01030101) ? "impar":"par");
    return 0;
}