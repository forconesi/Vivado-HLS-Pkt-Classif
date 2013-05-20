############################################################
## This file is generated automatically by Vivado HLS.
## Please DO NOT edit it.
## Copyright (C) 2013 Xilinx Inc. All rights reserved.
############################################################
open_project core2ublaze_prj
set_top talk2ub
add_files src/talk2ub.cpp
add_files -tb src/simple_talk2ub_tb.cpp
open_solution "solution1"
set_part  {xc5vtx240tff1759-2}
create_clock -period 10

source "./core2ublaze_prj/solution1/directives.tcl"
csynth_design
