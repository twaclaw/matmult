open_project matmult
set_top matmult_accel

add_files matmult.h

add_files matmult_accel.cpp \
-cflags "-D__SDSVHLS__ -std=c++14"

add_files -tb matmult_tb.cpp \
-cflags "-D__SDSVHLS__ -std=c++14"

open_solution "solution1"
set_part {zynq}
create_clock -period 10 -name default
set_clock_uncertainty 27.0%

# run testbench
csim_design -clean 

csynth_design
export_design -format ip_catalog -description "Matrix multiplication IP" -display_name "matmult_accel"
exit
