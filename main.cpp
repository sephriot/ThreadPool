#include <iostream>
#include "ThreadPool.h"

int main() {

    ThreadPool& p = ThreadPool::getInstance();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}