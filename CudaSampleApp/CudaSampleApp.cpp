#include "stdafx.h"
#include "complexCalc.h"
#include <chrono>

using namespace CudaLib;

int main()
{
	std::chrono::system_clock::time_point timeStart, timeEnd;
	int timeElapsed;

	printf("My app uses library\n");

	/*** example 1 ***/
	complexCalcFast(2);
	complexCalcFast(5);

	/*** example 2***/
	int n = 1000000;
	int *in, *out;
	allocManaged(&in, n * sizeof(int));
	allocManaged(&out, n * sizeof(int));
	for (int i = 0; i < n; i++) {
		in[i] = i;
		out[i] = 0;
	}

	/* call library function (non CUDA) */
	timeStart = std::chrono::system_clock::now();
	complexCalc2Original(in, out, n);
	timeEnd = std::chrono::system_clock::now();
	timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();
	printf("execution time = %d\n", timeElapsed);

	/* call library function (CUDA) */
	timeStart = std::chrono::system_clock::now();
	complexCalc2Fast(in, out, n);
	timeEnd = std::chrono::system_clock::now();
	timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(timeEnd - timeStart).count();
	printf("execution time = %d\n", timeElapsed);
	//for (int i = 0; i < n; i++) {
	//	printf("out[%d] = %d\n", i, out[i]);
	//}

	freeManaged(in);
	freeManaged(out);

	getchar();
    return 0;
}

