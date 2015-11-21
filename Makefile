#Compiler and compiler flags for standard g++
CC=g++
C++FLAGS=-Wall -std=c++11 -pedantic

# It is important that "-l OpenCL" is the final argument when calling g++.

#Compiler and compiler flags for NVIDIA CUDA Compiler
#CC=nvcc
#C++FLAGS= -V --verbose -std=c++11 -lOpenCL

#Math Library
MATH_LIBS = -lm
EXEC_DIR=.
CUDA_LIBS64=/usr/local/cuda/lib64
OPENCL_LIBS = -l OpenCL

#Including
INCLUDES= -I. -I /usr/local/cuda/include
LIBS_ALL= -L/usr/lib -L/usr/local/lib -L $(MATH_LIBS) -L $(CUDA_LIBS64)

all:
	$(CC) HelloWorld.cpp -o HelloWorld \
		$(C++FLAGS) \
		$(OPENCL_LIBS)

clean:
	(rm -f *.o;)
	(rm -f *.out;)
	rm -f HelloWorld
