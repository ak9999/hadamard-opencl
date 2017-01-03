// functions.h
// HelloWorld

#pragma once

#include <chrono> // To time how long our program takes to run.

// OpenCL headers
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

const unsigned int ARRAY_SIZE = 100;

cl_context CreateContext();
cl_command_queue CreateCommandQueue(cl_context, cl_device_id *);
cl_program CreateProgram(cl_context, cl_device_id, const char *);

bool CreateMemObjects(cl_context, cl_mem memObjects[3], float *, float *);
void Cleanup(cl_context context,
			cl_command_queue commandQueue,
			cl_program program, cl_kernel kernel,
			cl_mem memObjects[3]);

// Returns program duration.
void timer(std::chrono::steady_clock::time_point start, std::chrono::steady_clock::time_point end);

#include "functions.cpp"
