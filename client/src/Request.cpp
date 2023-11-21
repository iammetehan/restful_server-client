#include "Common.h"
#include "Util.h"
#include "Data.h"

#include <iostream>

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>

extern std::set<size_t> objectIds;

namespace request
{
    void RepeatNTimes(std::function<void()> function, const size_t& n)
    {
        for (int i = 0 ; i < n; i++)
        {
            function();
        }
    }

    namespace make
    {
        namespace beast = boost::beast;
        namespace http = beast::http;
        namespace asio = boost::asio;
        using tcp = asio::ip::tcp;

        void Add()
        {
            try
            {
                using namespace data::create;


                boost::asio::io_context ioc;
                tcp::resolver resolver(ioc);
                auto const results = resolver.resolve(connection::Host(),
                                                      std::to_string(connection::Port()));

                tcp::socket socket(ioc);
                boost::asio::connect(socket, results.begin(), results.end());
                http::request<http::string_body>req(http::verb::post,
                                                    connection::Target(),
                                                    connection::HTTPVersion());

                req.set(http::field::host, connection::Host());
                req.set(http::field::content_type, connection::ContentType());

                const boost::property_tree::ptree& nObject = util::json::FromObject(random::Object());

                req.body() = util::json::Serialize(nObject);
                req.prepare_payload();

                http::write(socket, req);

                beast::flat_buffer buffer;
                http::response<http::string_body> res;
                http::read(socket, buffer, res);

                if (http::status::created == res.result())
                {
                    objectIds.insert(nObject.get<size_t>(data::definition::Id()));
                }

                socket.close();
                ioc.stop();
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        void Delete()
        {
            try
            {
                boost::asio::io_context ioc;
                tcp::resolver resolver(ioc);
                auto const results = resolver.resolve(connection::Host(),
                                                      std::to_string(connection::Port()));

                tcp::socket socket(ioc);
                boost::asio::connect(socket, results.begin(), results.end());
                http::request<http::string_body> req(http::verb::delete_,
                                                     connection::Target(),
                                                     connection::HTTPVersion());

                req.set(http::field::host, connection::Host());
                req.set(http::field::content_type, connection::ContentType());

                const size_t id = data::select::random::Id(objectIds);

                req.body() = std::to_string(id);
                req.prepare_payload();

                http::write(socket, req);

                beast::flat_buffer buffer;
                http::response<http::string_body> res;
                http::read(socket, buffer, res);

                if (http::status::accepted == res.result())
                {
                    objectIds.erase(id);
                }

                socket.close();
                ioc.stop();
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }

        void Read()
        {
            try
            {
                using namespace data::create;

                boost::asio::io_context ioc;
                tcp::resolver resolver(ioc);
                auto const results = resolver.resolve(connection::Host(),
                                                      std::to_string(connection::Port()));

                tcp::socket socket(ioc);
                boost::asio::connect(socket, results.begin(), results.end());
                http::request<http::string_body> req(http::verb::get,
                                                     connection::Target(),
                                                     connection::HTTPVersion());

                req.set(http::field::host, connection::Host());
                req.set(http::field::content_type, connection::ContentType());
                req.body() = std::to_string(data::select::random::Id(objectIds));
                req.prepare_payload();

                http::write(socket, req);

                beast::flat_buffer buffer;
                http::response<http::string_body> res;
                http::read(socket, buffer, res);

                if (http::status::accepted == res.result())
                {
//                    std::cout << res.body() << std::endl;
                }

                socket.close();
                ioc.stop();
            }
            catch (const std::exception& e)
            {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
}
