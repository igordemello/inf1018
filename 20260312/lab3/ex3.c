#include <stdio.h>

unsigned char switch_byte(unsigned char x) {
    unsigned char parte_esq = (x & 0xF0) >> 4;
    unsigned char parte_dir = (x & 0x0F) << 4;

    return parte_esq | parte_dir;
}

unsigned char rotate_left(unsigned char x, int n) {
    return (x << n) | (x >> (8 - n));
}

int main() {
    unsigned char v = 0xAB;
    printf("switch_byte(%02X) = %02X\n", v, switch_byte(v));

    unsigned char r = 0x61;
    printf("rotate_left(%02X, 1) = %02X\n", r, rotate_left(r, 1));
    printf("rotate_left(%02X, 2) = %02X\n", r, rotate_left(r, 2));
    printf("rotate_left(%02X, 7) = %02X\n", r, rotate_left(r, 7));

    return 0;
}