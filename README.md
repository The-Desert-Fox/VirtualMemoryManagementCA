# VirtualMemoryManagementCA
Make a C program to simulate virtual memory management that will also print to a test file all physical memory in a readable form addresses range from 0 - 2^16-1

# Overview
This project is the design and implementation of a standalone virtual memory manager, where there is a software-managed TLB. It must (1) allocate a block of memory suffcient to store bytes for the full system address. (2) Create a Page Table for a single process.(3) Randomly write 2048 to 20480 bytes of data belonging to the process.(4) Print physical memory and page tables to a text file.

# Information on Simulated Virtual Memory
- 16-bit virtual address. Can address 65536 bytes of data.
- bits 0 - 7 = Page Number
- bits 8 - 15 = Offset
- Page table size: 2^8 bytes. (256)
- Page size: 2^8 bytes. (256)
- Frame size: 2^8 bytes. (256)
- Number of frames: 256 (Addr bus size / page size)

First 8 most significant bits are the physical address.
Least significant bit tells us if the page is in use.(1/Yes, 0/No)
Second least significant tells us if the page is on the disc or not.(1/yes, 0/no)

# Links
[Github file used to help](https://github.com/zedtran/VirtualMemoryManagementSim)

[Makefile tutorial used](http://www.cs.colby.edu/maxwell/courses/tutorials/maketutor/)
