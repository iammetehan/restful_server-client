#ifndef HANDLE_H
#define HANDLE_H

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>

namespace handle
{
    namespace asio = boost::asio;
    namespace beast = boost::beast;
    namespace http = beast::http;
    using tcp = asio::ip::tcp;

    void Request(const http::request<http::string_body>& req,
                 http::response<http::string_body>& res);
    void Session(tcp::socket socket);
}
#endif // HANDLE_H
