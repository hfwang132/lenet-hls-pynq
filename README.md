# Lenet-5 on PYNQ via HLS
- Software Platform: Vitis HLS 2020.2
- Hardware Platform: PYNQ-Z2 (xc7z020clg484-1)
- FP32 model accuracy: 97.65%; Int8 PTSQ model accuracy: 96.88%
- Software fps: 25; Hardware fps: 417; 17 times acceleration
- AXI Stream not used. Expected in the future.

## Repository Tree

```
├── bd/
├── jupyter/
├── README.md
├── report.pdf
├── src_fp32/
└── src_int8/
```

`bd` folder contains the reference block design.

`jupyter` folder contains the bitstream files, the hardware description files, and the reference jupyter notebook.

`src_fp32` and `src_int8` contains HLS source codes for float32 and int8 models.
