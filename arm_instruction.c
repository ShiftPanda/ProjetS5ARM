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
#include "arm_instruction.h"
#include "arm_exception.h"
#include "arm_data_processing.h"
#include "arm_load_store.h"
#include "arm_branch_other.h"
#include "arm_constants.h"
#include "util.h"

/* Prend le code condition, bit de 31 a 28 */
//Evalue si on execute une instruction en fonction du code condition
int eval_code_cond(uint8_t cond){

	switch(cond){ //Page 112 liste des conditions
		case 0 : return  (Z == 1); break;
		case 1 : return  (Z == 0); break;
		case 2 : return  (C == 1); break;
		case 3 : return  (C == 0); break;
		case 4 : return  (N == 1); break;
		case 5 : return  (N == 0); break;
		case 6 : return  (V == 1); break;
		case 7 : return  (V == 0); break;
		case 8 : return  ((C == 1) && (Z == 0)); break;
		case 9 : return  ((C == 0) || (Z == 1)); break;
		case 10 : return (((N == 1) && (V == 1)) || ((N == 0) && (V == 0))); break;
		case 11 : return (((N == 1) && (V == 0)) || ((N == 0) && (V == 1))); break;
		case 12 : return ((Z == 0) && (((N == 1) && (V == 1)) || ((N == 0) && (V == 0)))); break;
		case 13 : return ((Z == 1) || (((N == 1) && (V == 0)) || ((N == 0) && (V == 1)))); break;
		case 14 : return 1; break;
		case 15 : return 2 break; //page 149 Unconditionnal instruction  
		default : return 0 break; 
	}
}

/* type_instructions de 27 a 26
*00:data processing
*01:Load/Store
*10:Branch
*11:Co Processing
*/

int eval_type_op(arm_core p, uint32_t ins){
	uint8_t type_op = get_bits(ins,27,26);
	switch(type_op){
		case 0: //exectuiton instruction data processing
			arm_data_processing(p,ins); //A completer fonction d'appel
			break;
		case 1: //execution instruction load_store
			arm_load_store(p,ins);
			break;
		case 2: //execution instruction brannchement 
			arm_branch(p,ins);
			break;  
		case 3: //execution instruction coprocessor
			break;
	}
	return 0;
}

static int arm_execute_instruction(arm_core p) {
	uint32_t ins;
	int result=arm_fetch(p,&ins);

	if( result == 0 ){ // si le fetch c'est bien passé

		result = eval_code_cond(get_bits(ins,31,28));
		switch(result){
			case 1 : //on execute l'instruction
				break;
			case 2 : //on execute l'Unconditionnal instruction
				break;
			default: break;
		}


	}
	else{
		//GESTION ERREUR MEMOIRE .
	}

    return 0;
}

int arm_step(arm_core p) {
    int result;

    result = arm_execute_instruction(p);
    if (result)
        arm_exception(p, result);
    return result;
}
