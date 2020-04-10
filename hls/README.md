# matmult HLS Implementation

This folder contains the matrix multiplication kernel *c++* code. 

To build run:
```bash
make clean && make solution1
```

---

The following directives are applied to the `mult_hw` function (See [script_solution1.tcl](./script_solution1.tcl)):

```tcl
set_directive_inline "mmult_hw"
set_directive_pipeline -II 1 "mmult_hw/L2"
set_directive_array_partition -type block -factor 16 -dim 2 "mmult_hw" a
set_directive_array_partition -type block -factor 16 -dim 1 "mmult_hw" b

```

These directives result in the following utilization and performance estimates (Vivado version 2019.2):

```
================================================================
== Performance Estimates
================================================================
+ Timing: 
    * Summary: 
    +--------+----------+----------+------------+
    |  Clock |  Target  | Estimated| Uncertainty|
    +--------+----------+----------+------------+
    |ap_clk  | 10.00 ns | 6.329 ns |   2.70 ns  |
    +--------+----------+----------+------------+

+ Latency: 
    * Summary: 
    +---------+---------+----------+----------+-------+-------+----------+
    |  Latency (cycles) |  Latency (absolute) |    Interval   | Pipeline |
    |   min   |   max   |    min   |    max   |  min  |  max  |   Type   |
    +---------+---------+----------+----------+-------+-------+----------+
    |   116617|   116617| 1.166 ms | 1.166 ms |  66181|  66181| dataflow |
    +---------+---------+----------+----------+-------+-------+----------+

    + Detail: 
        * Instance: 
        +-------------------+------------------+---------+---------+----------+----------+-------+-------+---------+
        |                   |                  |  Latency (cycles) |  Latency (absolute) |    Interval   | Pipeline|
        |      Instance     |      Module      |   min   |   max   |    min   |    max   |  min  |  max  |   Type  |
        +-------------------+------------------+---------+---------+----------+----------+-------+-------+---------+
        |Loop_L1_proc_U0    |Loop_L1_proc      |    66180|    66180| 0.662 ms | 0.662 ms |  66180|  66180|   none  |
        |axis2Mat_float_U0  |axis2Mat_float_s  |    33538|    33538| 0.335 ms | 0.335 ms |  33538|  33538|   none  |
        |Mat2axis_float_U0  |Mat2axis_float_s  |    16897|    16897| 0.169 ms | 0.169 ms |  16897|  16897|   none  |
        +-------------------+------------------+---------+---------+----------+----------+-------+-------+---------+

        * Loop: 
        N/A



================================================================
== Utilization Estimates
================================================================
* Summary: 
+-----------------+---------+-------+--------+-------+-----+
|       Name      | BRAM_18K| DSP48E|   FF   |  LUT  | URAM|
+-----------------+---------+-------+--------+-------+-----+
|DSP              |        -|      -|       -|      -|    -|
|Expression       |        -|      -|       0|     67|    -|
|FIFO             |        -|      -|       -|      -|    -|
|Instance         |        0|    160|   36240|  35929|    -|
|Memory           |       96|      -|       0|      0|    0|
|Multiplexer      |        -|      -|       -|     96|    -|
|Register         |        -|      -|      32|      -|    -|
+-----------------+---------+-------+--------+-------+-----+
|Total            |       96|    160|   36272|  36092|    0|
+-----------------+---------+-------+--------+-------+-----+
|Available        |      280|    220|  106400|  53200|    0|
+-----------------+---------+-------+--------+-------+-----+
|Utilization (%)  |       34|     72|      34|     67|    0|
+-----------------+
```