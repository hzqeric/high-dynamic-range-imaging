#include "core/hdrSolver.h"

#include <iostream>

using namespace shdr;

int main(int argc, char* argv[]) {
    if (argc == 1) {
        std::cout << "Simple-HDR -h for further informations."
                  << std::endl;

        return 0;
    }

    else if (argc == 2 &&
             std::string(argv[1]) == "-h") {

        fprintf(stdout, R"(Simple-HDR, copyright (c)2019-2020 Chia-Yu, Chou

[<options>] <images directory path> <shutterspeed file path>

Notice you need to specify images 'directory path' and shutterspeed 'file path'.
For example:
Simple-HDR ./IMAGES/ ./SHUTTERSPEED.txt

Options:
    -h             Print this help text.
    -crfs <method> Specify crfSolver method used for solving camera response function.
                   It currently only supports one method.
                   <debevec>

                   default: <debevec> 
    -tm   <method> Specify toneMapper method used for tone mapping.
                   It currently supports three kinds of methods.
                   <photographic-global>, <photographic-local>, <bilateral>

                   default: <bilateral>
)");

        return 0;
    }

    else {
        std::vector<std::string> args;
        for (int i = 1; i < argc; ++i) {
            args.push_back(argv[i]);
        }

        std::string crfSolverMethod  = "debevec";
        std::string toneMapperMethod = "bilateral";
        const std::string imageDirectoryPath   = argv[argc - 2];
        const std::string shutterspeedFilePath = argv[argc - 1];

        for (std::size_t i = 0; i < args.size(); ++i) {
            if (args[i] == "-crfs") {
                crfSolverMethod = args[i + 1];
            }
            if (args[i] == "-tm") {
                toneMapperMethod = args[i + 1];
            }
        }

        std::cout << "Simple-HDR, copyright (c)2019-2020 Chia-Yu, Chou\n"
                  << std::endl;

        cv::Mat hdri;
        HdrSolver hdrSolver(imageDirectoryPath,
                            shutterspeedFilePath,
                            crfSolverMethod,
                            toneMapperMethod);

        hdrSolver.solve(&hdri);
        cv::imwrite("./hdr_result.png", hdri);

        return 0;
    }
}