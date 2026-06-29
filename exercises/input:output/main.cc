#include<iostream>
#include<string>
#include<vector>
#include<cmath>
#include<iomanip>

/*
int main(int argc, char* argv[]) {
    std::vector<double> numbers;

    for (int i = 0; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-n" && i + 1 < argc) {
            numbers.push_back(std::stod(argv[++i]));
            ++i;
        }
    }

    for (double n : numbers) {
        std::cout << n << "\t" 
                  << std::sin(n) << "\t"
                  << std::cos(n) << "\t" << std::endl;
    }

    return 0;

}


int main() {
    double x;

    std::cout << std::fixed << std::setprecision(6);

    while(std::cin >> x) {
        std::cout << x << "\t" 
                  << std::sin(x) << "\t"
                  << std::cos(x) << "\t" << std::endl;
    }
}

*/

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

int main(int argc, char* argv[]) {

    std::string infile = "";
    std::string outfile = "";

    // Parse command line arguments
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "--input" && i + 1 < argc) {
            infile = argv[++i];
        }
        else if (arg == "--output" && i + 1 < argc) {
            outfile = argv[++i];
        }
    }

    std::ifstream myinput(infile);
    std::ofstream myoutput(outfile);

    if (!myinput.is_open() || !myoutput.is_open()) {
        std::cerr << "Error opening files: " << infile << " " << outfile << std::endl;
        return EXIT_FAILURE;
    }

    double x;

    while (myinput >> x) {
        myoutput << x << " "
                 << std::sin(x) << " "
                 << std::cos(x) << std::endl;
    }

    myinput.close();
    myoutput.close();

    return EXIT_SUCCESS;
}