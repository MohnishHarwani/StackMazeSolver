#include "maze.hpp"
#include "iostream"
#include "cstdlib"
using namespace cs251;
/*
The code is provided to be built as an executable for grading.
You can modify the code based on your needs, but the original copy of this file will be used for testing.
*/
int main()
{
  try {
  	std::string args;
  	std::getline(std::cin, args);
  	const size_t dimX = std::atoi(args.c_str());
  	std::getline(std::cin, args);
  	const size_t dimY = std::atoi(args.c_str());
  	std::getline(std::cin, args);
  	const size_t dimZ = std::atoi(args.c_str());
  	std::getline(std::cin, args);
  	const unsigned seed = std::atoi(args.c_str());
  
  	maze m;
  	m.initialize(dimX, dimY, dimZ, seed);
  	while (true)
  	{
  		std::string input;
  		std::getline(std::cin, input);
  		try {
  			if (input == "quit") {
  				break;
  			}
  			std::string text;
  			if (input == "solve")
  			{
  				std::getline(std::cin, text);
  				const auto startX = std::atoi(text.c_str());
  				std::getline(std::cin, text);
  				const auto  startY = std::atoi(text.c_str());
  				std::getline(std::cin, text);
  				const auto  startZ = std::atoi(text.c_str());
  				std::getline(std::cin, text);
  				const auto  endX = std::atoi(text.c_str());
  				std::getline(std::cin, text);
  				const auto  endY = std::atoi(text.c_str());
  				std::getline(std::cin, text);
  				const auto  endZ = std::atoi(text.c_str());
  				m.solve(startX, startY, startZ, endX, endY, endZ);
  			}
  			else if (input == "print_walls")
  			{
  				std::getline(std::cin, text);
  				std::cout << m.print_walls(std::atoi(text.c_str())) << std::endl;
  			}
  			else if (input == "print_marks")
  			{
  				std::getline(std::cin, text);
  				std::cout << m.print_marks(std::atoi(text.c_str())) << std::endl;
  			}
  		}
  		catch (const std::out_of_range& e)
  		{
  			std::cout << e.what() << std::endl;
  		}
  	}
  } catch (const std::exception& e) {
    std::cerr << "Unhandled exception: " << e.what() << std::endl;
    return 1;
  }
	return 0;
}
