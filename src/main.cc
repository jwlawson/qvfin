/*
 * main.cc
 */
#include <unistd.h>

#include <iostream>
#include <string>

void usage() {
	std::cout << "qvfin -s size [-o output] [-c class_output]" << std::endl;
	std::cout << "  -s Size of matrices to check" << std::endl;
	std::cout << "  -o Output file for all finite matrices" << std::endl;
	std::cout << "  -c Output file for class representatives" << std::endl;
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
}

