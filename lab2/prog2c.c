#include <stdio.h>
#include <ctype.h>

int char2int(char c) {
    if (isdigit(c)) {
        return c - '0';
    } else if (isalpha(c)) {
        if (isupper(c)) {
            return c - 'A' + 10;
        } else {
            return c - 'a' + 10;
        }
    }
    return -1; // Caractere inválido
}

int string2num(char *s, int base) {
    int result = 0;
    while (*s) {
        int digitValue = char2int(*s);
        if (digitValue == -1 || digitValue >= base) {
            printf("Erro: Caractere fora da base\n");
            return -1; // Tratamento de erro se o caractere estiver fora da base
        }
        result = result * base + digitValue;
        s++;
    }
    return result;
}

int main(void) {
    printf("Base 16: %d\n", string2num("1A3", 16));
    printf("Base 36: %d\n", string2num("1z", 36));
    printf("Base 36 (upper): %d\n", string2num("1Z", 36));
    return 0;
}

