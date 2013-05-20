//*****************************************************************************
// Testbench file
//*****************************************************************************
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "talk2ub.h"

using namespace std;

int main(void){

	uint32_t pross_pkts_cc=7, pross_pkts_ub=0, protocol_selec_cc=0, protocol_selec_ub=0x0006;

	cout << "Test started..." << endl;

	for (uint32_t i=0;i<5;i++){
		talk2ub (&pross_pkts_cc,&pross_pkts_ub,&protocol_selec_ub,&protocol_selec_cc);
		cout << "pross_pkts_ub: " << pross_pkts_ub << "\tprotocol_selec_cc: " << protocol_selec_cc << endl;
	}

	cout << "Test finishes" << endl;
}
