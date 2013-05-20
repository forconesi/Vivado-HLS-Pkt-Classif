// ------------------------------------------------------------------------------
// Core to classify packets
// ------------------------------------------------------------------------------
#ifndef _PARSER_H_
#define _PARSER_H_

using namespace std;

#include "ap_int.h"
#include <stdint.h>
//#include "ap_axi_sdata.h"

#define ETH_INTERFACE_WIDTH 8

template<int D>
  struct my_axis{
    ap_uint<D>   data;
    ap_uint<D/8> strb;
    ap_uint<1>   last;
  };

typedef my_axis<ETH_INTERFACE_WIDTH*8> axi_interface_type;

void parser_top (axi_interface_type data_input[240], axi_interface_type data_output1[240], axi_interface_type data_output2[240], uint32_t *pross_pkts, uint32_t *protocol_selection);

#endif
