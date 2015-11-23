#Compiler and compiler flags for standard g++
CC=g++
C++FLAGS=-Wall -std=c++11 -pedantic

# It is important that "-l OpenCL" is the final argument when calling g++.

# Compiler flags differ depending on platform.
# Need to check whether we're on Linux or Mac.
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	C++FLAGS += -l OpenCL
endif
ifeq ($(UNAME_S),Darwin)
	C++FLAGS += -framework OpenCL
endif

# Define RM depending on platform.
# On Windows, cmd.exe is the available shell, which uses `del` instead of `rm` to delete files.
# If COMSPEC is defined, then we know we're on Windows.
ifdef COMSPEC
	RM ?= del
else
	RM ?= rm -f
endif

# Math Library
MATH_LIBS = -lm
EXEC_DIR=.

# CUDA Libraries
CUDA_LIBS64=/usr/local/cuda/lib64

# AMD APP SDK libraries
AMDAPPSDK=AMDAPPSDKROOT/lib

#Including
INCLUDES= -I. -I /usr/local/cuda/include
LIBS_ALL= -L/usr/lib -L/usr/local/lib -L $(MATH_LIBS) -L $(CUDA_LIBS64) -L $(AMDAPPSDK)

all:
	$(CC) HelloWorld.cpp -o HelloWorld \
		$(C++FLAGS)

clean:
	($(RM) *.o;)
	($(RM) *.out;)
	$(RM) HelloWorld
