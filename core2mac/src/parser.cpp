// ------------------------------------------------------------------------------
// Core to classify packets
// ------------------------------------------------------------------------------

#include "parser.h"
#include <stdint.h>

using namespace std;

uint32_t _pross_pkts = 0;

void parser_top (axi_interface_type data_input[240], axi_interface_type data_output1[240], axi_interface_type data_output2[240], uint32_t *pross_pkts, uint32_t *protocol_selection){

//Register interfaces to be connected to the core that talks to ublaze
#pragma HLS INTERFACE ap_none port=protocol_selection
#pragma HLS INTERFACE register port=pross_pkts

//Tell the compiler this interfaces talk to FIFOs
#pragma HLS INTERFACE ap_fifo port=data_input
#pragma HLS INTERFACE ap_fifo port=data_output1
#pragma HLS INTERFACE ap_fifo port=data_output2

//Map HLS ports to AXI interfaces. Tell the compiler this interfaces are AXI4-Stream
#pragma HLS RESOURCE variable=data_input	core=AXIS metadata="-bus_bundle STREAM_A"
#pragma HLS RESOURCE variable=data_output1	core=AXIS metadata="-bus_bundle STREAM_B"
#pragma HLS RESOURCE variable=data_output2 	core=AXIS metadata="-bus_bundle STREAM_C"

	axi_interface_type data_read, data_tosend;
	ap_uint<64> internal_buffer[240];
	ap_uint<8> last_strobe;
	ap_uint<64> data_out;
	ap_uint<1> lastt;
	ap_uint<64> reg2analyze[5];
	#pragma HLS ARRAY_PARTITION variable=reg2analyze complete factor=0 dim=1

	int i;

	read_head: for(i=0;i<5;i++){	//the first 5 transactions have the data to classify the pkt
		data_read = *data_input;
		internal_buffer[i] = data_read.data;
		reg2analyze[i] = data_read.data;
		data_input++;
	}

	int decision = 0;
	classify_pross: {
		ap_uint<64> temp;
		temp = reg2analyze[2];
		uint8_t *byte_pointer;
		byte_pointer = (uint8_t *)&temp;
		byte_pointer = byte_pointer + 0x07;
		if (*protocol_selection == *byte_pointer)
			decision = 1;
		else
			decision = 2;
	}

	update_statistics: {
		_pross_pkts = _pross_pkts + 1;
		*pross_pkts = _pross_pkts;
	}

	int j=4;
	read_tail: do {
		data_read = *data_input;
		internal_buffer[++j] = data_read.data;
		last_strobe = data_read.strb;
		data_input++;
	} while (!(data_read.last));		//Read until the pkt ends

	if (decision == 1){
		send_out1: for(i=0;i<=j;i++){
			data_tosend.data = internal_buffer[i];
			if (i < j){
				data_tosend.strb = 0xff;
				data_tosend.last = 0;
			} else {
				data_tosend.strb = last_strobe;
				data_tosend.last = 1;
			}
			*data_output1 = data_tosend;
			data_output1++;
		}
	} else {
		send_out2: for(i=0;i<=j;i++){
			data_tosend.data = internal_buffer[i];
			if (i < j){
				data_tosend.strb = 0xff;
				data_tosend.last = 0;
			} else {
				data_tosend.strb = last_strobe;
				data_tosend.last = 1;
			}
			*data_output2 = data_tosend;
			data_output2++;
		}
	}

} //
