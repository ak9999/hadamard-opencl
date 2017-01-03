# Hadamard Product Demo with OpenCL

This program takes advantage of the GPU by using a OpenCL kernel to perform the multiplication.

The contents of all 3 arrays are printed to the terminal.

# Building

Run `make`

Works on Mac and Linux.
Those on Windows should read this [StackOverflow post](https://stackoverflow.com/questions/23173374/configure-opencl-under-cygwin) to set up MinGW with OpenCL libraries.

# Running

First run create_arrays to create the files holding the numbers, then run HelloWorld.

Check results.txt to see what happened.

# Update:

I wanted to see if I could pass `std::array`s to the GPU instead of C-style arrays. Turns out we can.
