/*
Armator - simulateur de jeu d'instruction ARMv5T à but pédagogique
Copyright (C) 2011 Guillaume Huard
Ce programme est libre, vous pouvez le redistribuer et/ou le modifier selon les
termes de la Licence Publique Générale GNU publiée par la Free Software
Foundation (version 2 ou bien toute autre version ultérieure choisie par vous).

Ce programme est distribué car potentiellement utile, mais SANS AUCUNE
GARANTIE, ni explicite ni implicite, y compris les garanties de
commercialisation ou d'adaptation dans un but spécifique. Reportez-vous à la
Licence Publique Générale GNU pour plus de détails.

Vous devez avoir reçu une copie de la Licence Publique Générale GNU en même
temps que ce programme ; si ce n'est pas le cas, écrivez à la Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307,
États-Unis.

Contact: Guillaume.Huard@imag.fr
	 Bâtiment IMAG
	 700 avenue centrale, domaine universitaire
	 38401 Saint Martin d'Hères
*/
#include "arm_branch_other.h"
#include "arm_constants.h"
#include "util.h"
#include <debug.h>
#include <stdlib.h>

//Page 160 B,BL
int arm_branch(arm_core p, uint32_t ins) {
    //L indique si c'est un branchement avec Link ou non
    uint8_t L=get_bit(ins,24);
    uint8_t sign=get_bit(ins,23);
    uint32_t offset=get_bits(ins,22,0)
    if(L){ // Si c'est un branchement avec Link (BL)
        // On place la valeur de pc dans le reg[14] 
        p->reg[14]=p->cycle_count; 
    }
    if(sign){ //Si le signe est negatif
        p->cycle_count-=offset;
    }
    else{ //Si il est positif
        p->cycle_count+=offset; 
    }
    return 1;
}

int arm_coprocessor_others_swi(arm_core p, uint32_t ins) {
    if (get_bit(ins, 24)) {
        /* Here we implement the end of the simulation as swi 0x123456 */
        if ((ins & 0xFFFFFF) == 0x123456)
            exit(0);
        return SOFTWARE_INTERRUPT;
    } 
    return UNDEFINED_INSTRUCTION;
}

int arm_miscellaneous(arm_core p, uint32_t ins) {
    return UNDEFINED_INSTRUCTION;
}
