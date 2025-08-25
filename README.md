# Project Description 
This project demonstrates how to utilize the Serial Flash Programmer II IP to read and write chunks of data into the non-volatile EPCQ/ EPCS Memory on the FPGA. A NIOS II Softcore Processor is used together with the HAL API Provided.

## FPGA Model
Intel Cyclone 10 LP 

## Author 
Dennis Wong Guan Ming

## Technical
1. Clock must be connected to pin E1, E2 is grounded. 
2. All EPCQ Addresses can be accessed however, depending on the programming address, they may/ may not be rewriteable. The designer may change the start of the programming address in Quartus Programmer.
