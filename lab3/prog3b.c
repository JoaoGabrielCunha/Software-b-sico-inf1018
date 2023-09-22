#include <stdio.h>

unsigned char rotate_left(unsigned char x, int n) {
    int num_bits = 8;
    n %= num_bits;
    return (x << n) | (x >> (num_bits - n));
}

int main() {
    unsigned char valor = 0x61;
    for (int deslocamento = 1; deslocamento <= 7; deslocamento++) {
        unsigned char resultado = rotate_left(valor, deslocamento);
        printf("0x%02X 0x%02X\n", valor, resultado);
    }
    return 0;
}
