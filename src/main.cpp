#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>

#include "argparse/argparse.hpp"

auto main(int argc, char *argv[]) -> int {
    using std::cout;
    using std::cerr;
    using std::endl;

    argparse::ArgumentParser program("paat3","0.0.1");
    
    program.add_argument("inputfile")
        .help("File containing the data to build the trees")
        .required();


    program.add_argument("-r")
        .help("Number of runs")
        .default_value(1)
        .scan<'i',int>()
        .nargs(1);

    program.add_argument("--outputfile","-o")
        .default_value(std::string("output.csv"))
        .help("CSV file to store the results");

    try
    {
        program.parse_args(argc, argv);
    }
    catch(const std::runtime_error& err)
    {
        cerr << err.what() << '\n';
        cerr << program;;
        std::exit(1);
    }

    std::string str_in, str_out;

    str_in   = program.get<std::string>("inputfile");
    str_out  = program.get<std::string>("-o");
    int runs = program.get<int>("-r");

    // cout << "Input  -> " << str_in  << endl;
    // cout << "Output -> " << str_out << endl;
    // cout << "Runs   -> " << runs    << endl;

    // Store input file contens
    // INPUT_CONTAINER GOES HERE

    // load from files
    {
        long value;

        std::ifstream ifs(str_in);
        while (ifs >> value) {
            //Take input
        }
    }

    // write results to output
    // std::ofstream ofs_output(str_out);
    // ofs_output << "COLNAME | OTHERCOL" << endl;
    // ofs_output << std::fixed;

    // timing
    using std::chrono::duration_cast;
    using clock = std::chrono::high_resolution_clock;
    using milli = std::chrono::milliseconds;
    using nano  = std::chrono::nanoseconds;

    // run tests
    for (int r = 0; r < runs; r++) {
        cout << "Running [" << r+1 << '/' << runs << "]" << endl; //cout.flush();

        // INIT CODE

        auto t1 = clock::now();
        // TASK
        auto t2 = clock::now();
        
        std::chrono::duration<double, std::milli> span = t2 - t1;

        // COLNAME | OTHERCOL
        // ofs_output   << 123
        //     << " | " << 456
        //     << endl;
    }

    return 0;
}
