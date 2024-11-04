#include "cyclic_double_queue.hpp"
#include "iostream"
using namespace cs251;
/*
The code is provided to be built as an executable for grading.
You can modify the code based on your needs, but the original copy of this file will be used for testing.
*/
template <typename T> void run_test();
template <typename T> T parse_item(std::string itemstr);

int main() {
  try {
	  std::string typestr;
	  std::getline(std::cin, typestr);
	  if (typestr == "int")
	    run_test<int>();
	  else if (typestr == "float")
	    run_test<float>();
	  else if (typestr == "string")
	    run_test<std::string>();
  } catch (const std::exception& e) {
    std::cerr << "Unhandled exception: " << e.what() << std::endl;
    return 1;
  }
	return 0;
}

template <typename T>
void run_test() {
	std::string args;
	std::getline(std::cin, args);
	const int initialCapacity = std::atoi(args.c_str());
	std::getline(std::cin, args);
	const int increaseFactor = std::atoi(args.c_str());
	std::getline(std::cin, args);
	const int decreaseFactor = std::atoi(args.c_str());

	cyclic_double_queue<T> q(initialCapacity, increaseFactor, decreaseFactor);
	while (true)
	{
		std::string text{};
		std::getline(std::cin, text);
		const auto command = text.substr(0, 2);
		const auto valueStr = text.size() > 2 ? text.substr(3) : "";
    const auto value = parse_item<T>(valueStr);
		try {
			if (command == "qt") {
				break;
			}
			if (command == "ef")
			{
				q.enqueue_front(value);
			}
			else if (command == "eb")
			{
				q.enqueue_back(value);
			}
			else if (command == "df")
			{
				std::cout << q.dequeue_front() << std::endl;
			}
			else if (command == "db")
			{
				std::cout << q.dequeue_back() << std::endl;
			}
			else if (command == "pf")
			{
				q.pop_front();
			}
			else if (command == "pb")
			{
				q.pop_back();
			}
			else if (command == "gf")
			{
				std::cout << q.front() << std::endl;
			}
			else if (command == "gb")
			{
				std::cout << q.back() << std::endl;
			}
			else if (command == "cl")
			{
				q.clear();
			}
			else if (command == "gs")
			{
				std::cout << q.get_size() << std::endl;
			}
			else if (command == "gc")
			{
				std::cout << q.get_capacity() << std::endl;
			}
			else if (command == "ps")
			{
				std::cout << q.print_status() << std::endl;
			}
		}
		catch (const std::out_of_range& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
}

template<> int parse_item<int>(std::string itemstr) {
  return !itemstr.empty() ? std::atoi(itemstr.c_str()) : -2147483647 - 1;
}
template<> float parse_item<float>(std::string itemstr) {
  return !itemstr.empty() ? std::atof(itemstr.c_str()) : 0.0f;
}
template<> std::string parse_item<std::string>(std::string itemstr) {
  return itemstr;
}
