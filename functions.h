// functions.h
// HelloWorld

#ifndef __HelloWorld__functions__
#define __HelloWorld__functions__

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#define ARRAY_SIZE 10

cl_context CreateContext();
cl_command_queue CreateCommandQueue(cl_context, cl_device_id *);
cl_program CreateProgram(cl_context, cl_device_id, const char *);

bool CreateMemObjects(cl_context, cl_mem memObjects[3], float *, float *);
void Cleanup(cl_context context, cl_command_queue commandQueue,
	           cl_program program, cl_kernel kernel,
						 cl_mem memObjects[3]);

#include "functions.cpp"
#endif /* defined(__HelloWorld__functions__) */
