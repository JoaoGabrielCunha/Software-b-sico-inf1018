#include <stdio.h>

unsigned char switch_byte(unsigned char x){

    return ((x>>4) & 0x0F) | ((x<<4) & 0xF0);


}

int main(){
    unsigned char valor= 0xAB;
    unsigned char resultado = switch_byte(valor);

    printf("Valor original: 0x%02X\n",valor);
    printf("Valor trocado: 0x%02X\n", resultado);

}
