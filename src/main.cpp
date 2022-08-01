#include <iostream>
#include <fstream>
//#include <string>
//#include <vector>
#include <chrono>
#include <limits>

#include "argparse/argparse.hpp"

//         1_000_000
#define INF 1000000

void print_mat(const int* const mat, size_t size) {
    for (size_t i = 0; i < size; i++) {
        for (size_t j = 0; j < size; j++) {
            std::cout << mat[i*size+j] << ' ';
        }
        std::cout << std::endl;
    }
}

void floyd_warshall(int *mat, const size_t &size) {
    for (size_t k = 0; k < size; ++k) {
        for (size_t i = 0; i < size; ++i) {
            for (size_t j = 0; j < size; ++j) {
                if (mat[i*size+k] + mat[k*size+j] < mat[i*size+j]) {
                    mat[i*size+j] = mat[i*size+k] + mat[k*size+j];
                }
            }
        }
    }
}

int min_distance_index(int *dist, bool *visited, const size_t &size) {
    int min = INF, min_index;
    for (size_t i = 0; i < size; ++i) {
        if (visited[i] == false && dist[i] <= min) {
            min = dist[i];
            min_index = i;
        }
    }
    return min_index;
}

void dijkstra(
    int const *og_mat,
    int  *dist,
    bool *visited,
    const int &src,
    const size_t &size
) {
    // Initialize distances and visited
    for (size_t i = 0; i < size; ++i) {
        dist[i] = INF;
        visited[i] = false;
    }
    // distance to self
    dist[src] = 0;
    for (size_t i = 0; i < size-1; ++i) {
        int u = min_distance_index(dist, visited, size);
        visited[u] = true;
        

        for (size_t v = 0; v < size; v++) {
            if (  !visited[v]
                && og_mat[u*size+v]
                && dist[u] != INF
                && dist[u] + og_mat[u*size+v] < dist[v]
            ) {
                dist[v] = dist[u] + og_mat[u*size+v];
            }
        }
    }
}

void dijkstra_wrapper(
    int const *og_mat,
    int  *dmat,
    bool *visited,
    const size_t &size
) {
    // Initialize
    int *dist;
    for (size_t i = 0; i < size; ++i) {
        dist = dmat + (size * i);
        // for (size_t j = 0; j < size; ++j) {
        //     visited[j] = false;
        //     dist[j] = INF;
        // }
        // dist[i] = 0;
        // call dijkstra
        dijkstra(og_mat, dist, visited, i, size);
    }
}

auto main(int argc, char *argv[]) -> int {
    using std::cout;
    using std::cerr;
    using std::endl;

    argparse::ArgumentParser program("paa-t4","0.0.1");
    
    program.add_argument("inputfile")
        //.help("File containing the data to build the trees")
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

    // mat[size][size], len(mat)
    int size, len;
    // Original matrix
    int *mat;
    // Dijkstra matrix
    int *dmat;
    bool *visited;
    // Floyd-Warshall matrix
    int *fmat;

    // load from files
    {
        int value;
        std::ifstream ifs(str_in);

        if (ifs >> value) {
            size = value;
        } else {
            cerr << "Error reading matrix size" << endl;
        }

        len = size * size;
        mat  = new int[len];
        dmat = new int[len];
        fmat = new int[len];
        visited = new bool[len];

        int count = 0;
        while (ifs >> value && count < len) {
            mat[count++] = value;
        }
    }

    print_mat(mat, size);

    // write output file headers
    // std::ofstream ofs_output(str_out);
    // ofs_output << "COLNAME | OTHERCOL" << endl;
    // ofs_output << std::fixed;

    // timing
    // using std::chrono::duration_cast;
    using clock = std::chrono::high_resolution_clock;
    // using milli = std::chrono::milliseconds;
    // using nano  = std::chrono::nanoseconds;

    // run tests
    for (int r = 0; r < runs; r++) {
        cout << "Running [" << r+1 << '/' << runs << "]" << endl; //cout.flush();

        // Init
        // prepare dijkstra matrix
        // for (size_t i = 0; i < len; i++) {
        //     dmat[i] = mat[i];
        // }

        // prepare floyd-warshall matrix
        for (size_t i = 0; i < size; i++) {
            for (size_t j = 0; j < size; j++) {
                auto temp = mat[i*size+j];
                if (i != j && temp == 0) {
                    fmat[i*size+j] = INF;
                } else {
                    fmat[i*size+j] = temp;
                }
            }
        }

        cout << "--- Floyd Warshall ---" << endl;
        auto floyd_warshall_t1 = clock::now();
        floyd_warshall(fmat, size);
        auto floyd_warshall_t2 = clock::now();
        print_mat(fmat, size);
        std::chrono::duration<double, std::nano> fw_span = floyd_warshall_t2 - floyd_warshall_t1;
        cout << fw_span.count() << "ns" << endl;

        cout << "--- Dijkstra ---" << endl;
        auto dijkstra_t1 = clock::now();
        dijkstra_wrapper(mat, dmat, visited, size);
        auto dijkstra_t2 = clock::now();
        print_mat(dmat, size);
        std::chrono::duration<double, std::nano> d_span = dijkstra_t2 - dijkstra_t1;
        cout << d_span.count() << "ns" << endl;

        // COLNAME | OTHERCOL
        // ofs_output   << 123
        //     << " | " << 456
        //     << endl;
    }

    return 0;
}
