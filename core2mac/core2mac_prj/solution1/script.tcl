############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2013 Xilinx Inc. All rights reserved.
############################################################
open_project core2mac_prj
set_top parser_top
add_files src/parser.cpp
add_files -tb src/2flujos
add_files -tb src/50_pkts
add_files -tb src/simpleParser_test.cpp
open_solution "solution1"
set_part  {xc5vtx240tff1759-2}
create_clock -period 5

source "./core2mac_prj/solution1/directives.tcl"
csynth_design
