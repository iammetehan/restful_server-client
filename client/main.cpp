#include "Request.h"

#include <iostream>
#include <vector>
#include <thread>
#include <set>

std::set<size_t> objectIds;

void StartTest(const size_t& numberOfRequests)
{
    std::cout << "Starting test for " << numberOfRequests << " requests..." << std::endl;

    auto start = std::chrono::high_resolution_clock::now();

    request::RepeatNTimes(request::make::Add, numberOfRequests);
    request::RepeatNTimes(request::make::Read, numberOfRequests);
    request::RepeatNTimes(request::make::Delete, numberOfRequests);

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Tests are completed in " << duration.count() << " seconds.." << std::endl;
}

int main()
{

    std::vector<size_t> tests{2,
                              4,
                              8};

//    std::vector<size_t> tests{1000,
//                              10000,
//                              100000,
//                              1000000};



    for (const size_t& test: tests)
    {
        StartTest(test);
    }

    return EXIT_SUCCESS;
}
