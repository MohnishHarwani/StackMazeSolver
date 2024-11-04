#include "../include/cyclic_double_queue.hpp"
#include "iostream"
using namespace cs251;
/*
The code is provided to be built as an executable for grading.
You can modify the code based on your needs, but the original copy of this file will be used for testing.
*/
template <typename T> void run_test();
template <typename T> T parse_item(std::string itemstr);

int main() {
    cyclic_double_queue<int> k(4, 4, 3);
    std::cout<< "New main works\n";
    k.enqueue_back(23);
    k.printContents();
    k.enqueue_front(23);
    k.printContents();
    k.enqueue_front(-47);
    k.printContents();
    k.enqueue_back(-88);
    k.printContents();
    k.enqueue_back(35);
    k.printContents();
    k.dequeue_front();
    k.printContents();
    
}



