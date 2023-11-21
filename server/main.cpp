#include "Util.h"
#include "Common.h"
#include "Handle.h"

#include <boost/asio.hpp>

#include <iostream>
#include <thread>
#include <set>

namespace beast = boost::beast;
namespace http = beast::http;
namespace asio = boost::asio;
using tcp = asio::ip::tcp;

constexpr size_t numberOfThreads = 1;

std::set<util::Object> objects;

void PrintObjects()
{
    std::cout << "------" << std::endl;

    for (const util::Object& obj: objects)
    {
        std::cout << obj;
    }
}

void Listen(asio::io_context& ioc, tcp::acceptor& acceptor)
{
    while(true)
    {
        tcp::socket socket{ioc};
        acceptor.accept(socket);
        handle::Session(std::move(socket));
//        PrintObjects();
    }
}

int main()
{
    try {
        tcp::endpoint endpoint(asio::ip::make_address(connection::Host()),
                               connection::Port());

        asio::io_context ioc(numberOfThreads);
        tcp::acceptor acceptor(ioc, endpoint);

        std::vector<std::thread> threads;
        for (int i = 0; i < numberOfThreads; ++i)
        {
            threads.emplace_back([&ioc, &acceptor]()
            {
                Listen(ioc, acceptor);
            });
        }

        for (auto& thread : threads)
        {
            thread.join();
        }

    }
    catch (const std::exception& e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
