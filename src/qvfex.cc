/*
 * qvfex.cc
 *
 * Contains the main method for program qvfex.
 *
 * Takes an input stream or stdin and for each matrix provided will consider all
 * possible extensions and output any which are mutation-finite.
 */

#include <unistd.h>
#include <fstream>
#include <iostream>
#include <string>

#include "qv/extension_iterator.h"
#include "qv/mass_finite_check.h"

void usage() {
	std::cout << "qvfex [-i input_file] [-o output_file]" << std::endl;
	std::cout << "Returns each mutation-finite extension of provided matrices" << std::endl;
	std::cout << "  -i Input file to read matrices from, default is stdin" << std::endl;
	std::cout << "  -o Output file, default stdout" << std::endl;
}

int run_both(std::istream& in, std::ostream& out) {
	typedef cluster::EquivQuiverMatrix Matrix;
	typedef cluster::ExtensionIterator<Matrix> Iter;
	typedef cluster::MassFiniteCheck Check;
	Check chk;
	std::string str;
	while(std::getline(in, str)) {
		if(str[0] == '{') {
			Matrix m(str);
			Iter iter(m);
			while(iter.has_next()){
				Matrix n = iter.next();
				if(chk.is_finite(n)){
					out << n << std::endl;
				}
			}
		}
	}
	return 0;
}

int run_in(std::istream& in) {
	return run_both(in, std::cout);
}

int run_out(std::ostream& out) {
	return run_both(std::cin, out);
}

int run() {
	return run_both(std::cin, std::cout);
}

int main(int argc, char* argv[]) {

	bool input = false;
	std::string ifile;
	bool output = false;
	std::string ofile;

	int c;

	while((c = getopt(argc, argv, "i:o:")) != -1) {
		switch(c) {
			case 'i':
				input = true;
				ifile = optarg;
				break;
			case 'o':
				output = true;
				ofile = optarg;
				break;
			case '?':
				usage();
				return 1;
			default:
				usage();
				return 2;
		}
	}
	if(input) {
		std::ifstream f_in;
		f_in.open(ifile);
		if(!f_in.is_open()) {
			std::cout << "Error opening file: " << ifile << std::endl;
			return 1;
		}
		if(output) {
			std::ofstream f_out;
			f_out.open(ofile);
			if(!f_out.is_open()) {
				std::cout << "Error opening file: " << ofile << std::endl;
				return 1;
			}
			return run_both(f_in, f_out);
		}
		return run_in(f_in);
	}
	if(output) {
		std::ofstream f_out;
		f_out.open(ofile);
		if(!f_out.is_open()) {
			std::cout << "Error opening file: " << ofile << std::endl;
			return 1;
		}
		return run_out(f_out);
	}
	return run();
}

