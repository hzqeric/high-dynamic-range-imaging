#include "core/hdrSolver.h"

using namespace shdr;

int main(int argc, char* argv[]) {
	if (argc < 3) {
		fprintf(stderr, "simpleHDR.exe [./image path] [shutterspeed file]\n");
		exit(0);
	}

	cv::Mat hdri;
	HDRSolver hdrSolver = HDRSolver(argv[1], argv[2]);
	hdrSolver.solve(hdri);

	return 0;
}

