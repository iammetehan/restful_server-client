#include "Handle.h"
#include "Util.h"

#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

extern std::set<util::Object> objects;

namespace handle
{
    static void Add(const http::request<http::string_body>& req, http::response<http::string_body>& res)
    {
        std::istringstream iss(req.body());
        boost::property_tree::ptree parsed_pt;
        boost::property_tree::json_parser::read_json(iss, parsed_pt);

        if(objects.insert(util::json::ToObject(parsed_pt)).second )
        {
            res.result(http::status::created);
        }
        else
        {
            res.result(http::status::internal_server_error);
        }
    }

    static void Get(const http::request<http::string_body>& req, http::response<http::string_body>& res)
    {
        const int id = std::stoi(req.body());
        auto it = util::Object::FindObjectById(objects, id);

        if (objects.end() != it)
        {
            res.body() = util::json::Serialize(util::json::FromObject(*it));
            res.result(http::status::accepted);
        }
        else
        {
            res.result(http::status::internal_server_error);
        }

        const util::Object& obj = *it;

    }

    static void Delete(const http::request<http::string_body>& req, http::response<http::string_body>& res)
    {
        const int id = std::stoi(req.body());
        auto it = util::Object::FindObjectById(objects, id);

        if (objects.end() != it)
        {
            objects.erase(it);
            res.result(http::status::accepted);
        }
        else
        {
            res.result(http::status::internal_server_error);
        }
    }

    void Request(const http::request<http::string_body>& req, http::response<http::string_body>& res)
    {
        if (req.method() == http::verb::post)
        {
            Add(req, res);
        }
        else if (req.method() == http::verb::get)
        {
            Get(req, res);
        }
        else if (req.method() == http::verb::delete_)
        {
            Delete(req, res);
        }
        else
        {
            res.result(http::status::not_found);
            res.body() = "404 Not Found";
        }

        res.version(req.version());
        res.prepare_payload();
    }

    void Session(tcp::socket socket)
    {
        beast::error_code ec;

        while(true)
        {
            beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req, ec);

            if (ec == http::error::end_of_stream)
            {
                break;
            }

            if (ec)
            {
                return;
            }

            http::response<http::string_body> res;
            Request(req, res);
            http::write(socket, res, ec);
            if (ec)
            {
                return;
            }
        }
    }

}
