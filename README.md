
# matmult 
> A floating point matrix multiplication implemented in hardware.

<p align="center">
<img src="images/matrix.png" height="200"> 
</p>

This repo describes the implementation of a floating point matrix multiplication on a [PYNQ-Z1](https://store.digilentinc.com/pynq-z1-python-productivity-for-zynq-7000-arm-fpga-soc/) development board. 

The hardware kernel implements the matrix product **C** = **AB**, where **A**, **B**, and **C** are 128 x 128 matrices.

The use of the  hardware kernel results in a 5x speedup compared to NumPy. This performance increase is achieved at expenses of a considerable utilization of the FPGA resources (DSP48E: 72%, BRAM: 34%, LUT: 67%). 

## Repo Organization

* [[hls]](./hls) contains the matrix multiplication kernel *c++* source code.
* [[boards/Pynq-Z1/matmult]](./boards/Pynq-Z1/matmult) contains the Vivado project.
* [[notebooks]](./notebooks) contains the Jupyter Notebook to evaluate the design. This notebook uses the [Xilinx/PYNQ](https://github.com/Xilinx/PYNQ) Python library.
* [[overlay]](./overlay) contains the generated hardware files. These files were generated using `vivado` and `vivado_hls` version 2019.2.

## Installation

* Copy `overlay/matmult`  to the PYNQ-Z1 device.
* Copy `notebooks/matmult.ipynq` to the Jupyter notebook area in the PYNQ-Z1 device. 

## Build
* Build the `matmult` ip:
    ```bash
    cd hls
    make clean && make solution1
    ```
* Build the Vivado project
    ```bash
    cd boards/Pynq-Z1/matmult
    make clean  && make all
    ```
## Credits

* This implementation borrows ideas and code from this [application note](https://www.xilinx.com/support/documentation/application_notes/xapp1170-zynq-hls.pdf), and the [PYNQ hello world example](https://github.com/Xilinx/PYNQ-HelloWorld).

* Schematic of matrix multiplication taken from [Wikipedia](https://en.wikipedia.org/wiki/Matrix_multiplication#/media/File:Matrix_multiplication_qtl1.svg)

