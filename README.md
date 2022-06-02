# Co-Design2022_EX2
110.2 EEE5009_軟硬體共同設計：implement "FIR Filter" communicate with "8051 Instruction Set Simulator"（8051_ISS） （SystemC）


# Task Description

[[To Do] SystemC-Ex2.pdf](./%5BTo%20Do%5D%20SystemC-Ex2.pdf)


# Install systemC

[Link](https://github.com/DANTA-HOJA/SystemC_Practice)


# How to Generate "memory dump file" for 8051_ISS

[Link](https://hackmd.io/25SsN_aGRD-ww4fAIBP-7A)


# NOTE

- Remember to add all ```.cpp``` file and tag ```-I.``` while compiling with g++ compiler, for example,

```
/usr/bin/g++ -g ./8051_iss.cpp -o ./out/8051_iss.out ./core_8051.cpp ./creg.cpp ./FIR_asic.cpp ./keyboard.cpp ./keyboardcontroller.cpp ./matrix.cpp ./op_bytes.cpp ./periph.cpp ./sram.cpp ./top.cpp ./Xram.cpp -I. -I[path to]/systemc-2.3.3/include -L[path to]/systemc-2.3.3/lib-linux64 -lsystemc
```

# Reference

[loserking/Hardware-Software-Codesign-](https://github.com/loserking/Hardware-Software-Codesign-)
