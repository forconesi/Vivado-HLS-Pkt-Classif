// ------------------------------------------------------------------------------
// Core to access the registers via the MicroBlaze
// ------------------------------------------------------------------------------


#ifndef _TALK2UB_H_
#define _TALK2UB_H_

#include <stdint.h>

using namespace std;

void talk2ub (uint32_t *pross_pkts_cc, uint32_t *pross_pkts_ub, uint32_t *protocol_selec_ub, uint32_t *protocol_selec_cc);

#endif
