#include <stdio.h>
#include <ctype.h>

int char2int(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else {
        return c - 'A' + 10;
    }
}

int string2num(char *s, int base) {
    int result = 0;
    while (*s) {
        int digitValue = char2int(*s);
        if (digitValue >= base) {
            printf("Erro: Caractere fora da base\n");
            return -1; // Tratamento de erro se o caractere estiver fora da base
        }
        result = result * base + digitValue;
        s++;
    }
    return result;
}

int main(void) {
    printf("Base 2: %d\n", string2num("1101", 2));
    printf("Base 5: %d\n", string2num("1234", 5));
    printf("Base 16: %d\n", string2num("1A3", 16));
    return 0;
}
 
