// HelloWorld.cpp
// Hello World Implementation

#include <iostream>
#include <cstdlib>
#include <array>

#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <CL/opencl.h>
#endif

#include "functions.h"

using namespace std;

int main()
{
	// Start timing.
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();

	cl_context context = 0;
	cl_command_queue commandQueue = 0;
	cl_program program = 0;
	cl_device_id device = 0;
	cl_kernel kernel = 0;
	cl_mem memObjects[3] = {0, 0, 0};
	cl_int errNum;

	// Create an OpenCL context on first available platform
	context = CreateContext();

	if(context == NULL)
	{
		cerr << "Failed to create OpenCL context.\n";

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	// Create a command queue on first available device
	commandQueue = CreateCommandQueue(context, &device);
	if(commandQueue == NULL)
	{
		Cleanup(context, commandQueue, program, kernel, memObjects);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	// Create program from "HelloWorld.cl" kernel source
	program = CreateProgram(context, device, "HelloWorld.cl");
	if(program == NULL)
	{
		Cleanup(context, commandQueue, program, kernel, memObjects);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	// Create OpenCL kernel
	kernel = clCreateKernel(program, "hello_kernel", NULL);
	if(kernel == NULL)
	{
		cerr << "Failed to create kernel." << '\n';
		Cleanup(context, commandQueue, program, kernel, memObjects);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	// Create memory objects that will be used as arguments to kernel.
	// First create host memory arrays that will store the arguments to kernel.
	array<float, ARRAY_SIZE> result = {};
	array<float, ARRAY_SIZE> a = {};
	array<float, ARRAY_SIZE> b = {};

	// Open two files a.txt and b.txt because they contain the arrays.
	{
		// The input file streams will be closed at the end of this scope.
		ifstream a_array;
		ifstream b_array;

		// Open files for reading.
		a_array.open("a.txt");
		b_array.open("b.txt");

		if(a_array.good() && b_array.good())
		{
			cout << "Reading arrays from files.\n";

			string line_a;
			string line_b;

			int index = 0;
			while(getline(a_array, line_a))
			{
				a[index] = atof(line_a.c_str());
				index++;
			}

			index = 0;
			while(getline(b_array, line_b))
			{
				b[index] = atof(line_b.c_str());
				index++;
			}
		}
	}

	// Print out contents of arrays.
	for(unsigned int i = 0; i < ARRAY_SIZE; i++)
	{
		//a[i] = (float)i;
		cout << "a[" << i << "] = " << a[i] << '\n';

		//b[i] = (float)(2*i);
		cout << "b[" << i << "] = " << b[i] << '\n';

	}

	if(CreateMemObjects(context, memObjects, a.data(), b.data()) == false)
	{
		Cleanup(context, commandQueue, program, kernel, memObjects);
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	errNum = clSetKernelArg(kernel, 0, sizeof(cl_mem), &memObjects[0]);
	errNum |= clSetKernelArg(kernel, 1, sizeof(cl_mem), &memObjects[1]);
	errNum |= clSetKernelArg(kernel, 2, sizeof(cl_mem), &memObjects[2]);

	if (errNum != CL_SUCCESS)
	{
		cerr << "Error setting kernel arguments.\n";
		Cleanup(context, commandQueue, program, kernel, memObjects);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	size_t globalWorkSize[1] = {ARRAY_SIZE};
	size_t localWorkSize[1] = {1};

	// Queue the kernel up for execution across the array
	errNum = clEnqueueNDRangeKernel(commandQueue, kernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	if (errNum != CL_SUCCESS)
	{
		cerr << "Error.\n";
		Cleanup(context, commandQueue, program, kernel, memObjects);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	// Transfer the result from buffer back to host.
	errNum = clEnqueueReadBuffer(commandQueue, memObjects[2], CL_TRUE, 0, ARRAY_SIZE * sizeof(float),
	result.data(), 0, NULL, NULL);
	if(errNum != CL_SUCCESS)
	{
		cerr << "Error reading result buffer.\n";
		Cleanup(context, commandQueue, program, kernel, memObjects);

		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		timer(start, end);
		return 1;
	}

	// Output the result buffer to a file.
	ofstream result_array;
	result_array.open("results.txt");
	if(result_array.good())
	{
		for(unsigned int i = 0; i < ARRAY_SIZE; i++)
		{
			result_array << result[i] << '\n';
		}
		cout << "Results saved to results.txt.\n";
	}
	result_array.close();


	cout << '\n';
	cout << "Executed program successfully.\n";
	Cleanup(context, commandQueue, program, kernel, memObjects);

	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
	timer(start, end);
	return 0;
}
