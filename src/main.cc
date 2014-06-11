/*
 * main.cc
 */
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <string>

#include "mass_finite_check.h"
#include "skew_symmetric_iterator.h"

void usage() {
	std::cout << "qvfin -s size [-o output] [-c class_output]" << std::endl;
	std::cout << "  -s Size of matrices to check" << std::endl;
	std::cout << "  -o Output file for all finite matrices" << std::endl;
	std::cout << "  -c Output file for class representatives" << std::endl;
}

int find_finite(int size, std::ostream& out, std::ostream& c_out = std::cout) {
	using cluster::SkewSymmetricIterator;
	using cluster::MassFiniteCheck;
	using cluster::EquivQuiverMatrix;
	MassFiniteCheck chk;
	SkewSymmetricIterator iter(size);
	while(iter.has_next()){
		std::shared_ptr<EquivQuiverMatrix> n = iter.next();
		if(chk.is_finite(*n) && chk.last_new_class()){
			c_out << *n << std::endl;
		}
	}
	auto set = chk.set();
	for(auto i = set->begin(); i != set->end(); i++) {
		out << **i << std::endl;
	}
	return 0;
}

int find_class(int size, std::ostream& c_out = std::cout) {
	using cluster::SkewSymmetricIterator;
	using cluster::MassFiniteCheck;
	using cluster::EquivQuiverMatrix;
	MassFiniteCheck chk;
	SkewSymmetricIterator iter(size);
	while(iter.has_next()){
		std::shared_ptr<EquivQuiverMatrix> n = iter.next();
		if(chk.is_finite(*n) && chk.last_new_class()){
			c_out << *n << std::endl;
		}
	}
	return 0;
}

int run(int size, std::string out, std::string class_out) {
	if(out.empty()) {
		if(class_out.empty()){
			return find_class(size);
		}
		std::ofstream f_out;
		f_out.open(class_out);
		if(!f_out.is_open()){
			return 1;
		}
		return find_class(size, f_out);
	} else {
		std::ofstream f;
		f.open(out);
		if(!f.is_open()){
			return 1;
		}
		if(class_out.empty()){
			return find_finite(size, f);
		}
		std::ofstream f_out;
		f_out.open(class_out);
		if(!f_out.is_open()){
			return 1;
		}
		return find_finite(size, f, f_out);
	}
}

int main(int argc, char* argv[]) {
	int c;
	bool option = false;
	int size = 0;
	std::string out;
	std::string class_out;

	while((c = getopt(argc, argv, "s:o:c:")) != -1) {
		option = true;
		switch(c) {
			case 's':
				size = std::atoi(optarg);
				if(size < 3) {
					usage();
					return 1;
				}
				break;
			case 'o':
				out = optarg;
				break;
			case 'c':
				class_out = optarg;
				break;
			case '?':
				usage();
				return 1;
			default:
				usage();
				return 2;
		}
	}
	if(!option){
		usage();
		return 1;
	}
	run(size, out, class_out);
}

