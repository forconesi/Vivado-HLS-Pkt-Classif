// ------------------------------------------------------------------------------
// Core to access the registers via the MicroBlaze
// ------------------------------------------------------------------------------

#include "talk2ub.h"
#include <stdint.h>

using namespace std;
uint32_t increm = 0;

//Note: the sufix _cc stands for "classification core", while _ub stands for "microblaze"

void talk2ub (uint32_t *pross_pkts_cc, uint32_t *pross_pkts_ub, uint32_t *protocol_selec_ub, uint32_t *protocol_selec_cc){

#pragma HLS INTERFACE ap_none register port=protocol_selec_cc

	//Mapping the pointers to an AXI4-lite interface
#pragma HLS RESOURCE variable=pross_pkts_ub core=AXI4LiteS metadata="-bus_bundle BUS_READ"
#pragma HLS RESOURCE variable=protocol_selec_ub core=AXI4LiteS metadata="-bus_bundle BUS_READ"

	*pross_pkts_ub = *pross_pkts_cc;	//read from the classification the total # of processed pkts
	*protocol_selec_cc = *protocol_selec_ub;	//ublaze sets the protocol to be filter through interface 1

} //




