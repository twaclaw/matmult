open_project matmult
set_top matmult_accel

add_files matmult.h

add_files matmult_accel.cpp \
-cflags "-D__SDSVHLS__ -std=c++0x"

add_files -tb matmult_tb.cpp \
-cflags "-D__SDSVHLS__ -std=c++0x"

open_solution "solution1"
set_part {zynq} -tool vivado
create_clock -period 10 -name default
set_clock_uncertainty 27.0%

set_directive_inline "mmult_hw"
set_directive_pipeline -II 1 "mmult_hw/L2"
set_directive_array_partition -type block -factor 16 -dim 2 "mmult_hw" a
set_directive_array_partition -type block -factor 16 -dim 1 "mmult_hw" b

# run testbench
csim_design -clean 

#
csynth_design
export_design -format ip_catalog -description "Matrix multiplication IP" -display_name "matmult_accel"
exit
