#include <iostream>
#include <fstream>
#include <vector>

#include "graph.hpp"
#include "max_height.hpp"
#include "color_walk.hpp"
#include "scc.hpp"

using namespace cs251;

void usage(std::string name) {
	std::cout << "Usage:" << std::endl;
	std::cout << "    " << name << " PART INPUT [EXPECTED]" << std::endl;
	std::cout << std::endl;
	std::cout << "PART: Which part of the assignment to run: 1, 2, or 3" << std::endl;
	std::cout << "INPUT: Path to input file" << std::endl;
	std::cout << "EXPECTED: Path to expected file (only needed for part 2)" << std::endl;
	std::cout << std::endl;
}

int main(int argc, char** argv) {
	try {

	if (argc < 3 || argc > 4) {
		usage(argv[0]);
		return -1;
	}

	int part = std::atoi(argv[1]);
	if (part < 1 || part > 3) {
		usage(argv[0]);
		return -1;
	}

	if (part == 1) {
		graph g;
		g.read_edge_weights(argv[2]);
		int h = max_height::calculate(g);
		std::cout << h << std::endl;
	}

	else if (part == 2) {
		if (argc != 4) {
			usage(argv[0]);
			return -1;
		}

		// Read starting vertex
		std::ifstream expected;
		expected.open(argv[3]);
		int start_idx;
		expected >> start_idx;

		graph g;
		g.read_edge_colors(argv[2]);
		auto colorwalk = color_walk::calculate(g, start_idx);

		std::cout << start_idx << " ";
		for (auto p : colorwalk) {
			std::cout << p.first << " " << p.second << " ";
		}
		std::cout << std::endl;
	}

	else if (part == 3) {
		graph g;
		g.read_edge_weights(argv[2]);
		int s = scc::search(g);
		std::cout << s << std::endl;
	}

	} catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
		return -1;
	}
}
