#include <stdio.h>
#include <stdlib.h>
#include "memory.h"
#include "util.h"
#include "registers.h"
#include "registers.c"

void print_test(int result) {
    if (result)
        printf("Test succeded\n");
    else
        printf("TEST FAILED !!\n");
}

int compare(registers r, uint8_t reg, uint32_t value){
    return r->tabReg[reg]==value;
}

int main() {
    registers r=registers_create();
    uint8_t reg=1;
    uint32_t value=1500;

    //Test des registres
    printf("Test des registres : \n");
    //Test d'ecriture dans un registre
    printf("Ecriture dans un registre: ");
    write_register(r,reg,value);
    print_test(compare(r,reg,value));
    //Test lecture registre
    printf("Lecture dans un registre: ");
    print_test(read_register(r,reg)==value);
    //Test mode
    r->mode=1;
    printf("Test de Get_mode: ");
    print_test(get_mode(r)==1);
    //Test ecriture et lecture spsr dans le mauvais mode 
    printf("Test d'ecriture spsr dans le mauvais mode: ");
    write_spsr(r,value);
    print_test(!(compare(r,17,value)));  //La fonction compare devrait renvoyer 0
    printf("Test de lecture spsr dans le mauvais mode: ");
    print_test(read_spsr(r)==0);
    //Test ecriture et lecture spsr dans le bon mode
    r->mode=3;
    printf("Test d'ecriture spsr dans le bon mode: ");
    write_spsr(r,value);
    print_test(compare(r,17,value));
    printf("Test de lecture spsr dans le bon mode: ");
    print_test(read_spsr(r));
    //Test de registers_destroy
    return 0;
}