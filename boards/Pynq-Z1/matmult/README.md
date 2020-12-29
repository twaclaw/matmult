# matmult Vivado Project

To build run:

```bash
make clean && make all
```

If required, copy the hardware files to the PYNQ-Z1 device, for instance:

```bash
scp matmult.{bit,hwh,tcl} xilinx@pynq:jupyter_notebooks/matmult
```