#include <iostream>
#include <thread>
#include <vector>
 
 
int main() {
    std::vector<std::thread> workers;
    workers.emplace_back([]{
        while (true) {
            std::cout << "Thread is running" << std::endl;
        }
    });
    return 0;
}