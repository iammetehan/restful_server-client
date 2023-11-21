#include "Util.h"
#include "Common.h"

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>

namespace util
{
    namespace json
    {
        std::string Serialize(const boost::property_tree::ptree& pt)
        {
            std::ostringstream oss;
            boost::property_tree::json_parser::write_json(oss, pt);
            return oss.str();
        }

        Object ToObject(const boost::property_tree::ptree& pt)
        {
            return Object(pt.get<size_t>(data::definition::Id()),
                          pt.get<std::string>(data::definition::Payload()));
        }

        boost::property_tree::ptree FromObject(const util::Object& obj)
        {
            boost::property_tree::ptree pt;
            pt.put(data::definition::Id(), obj.GetId());
            pt.put(data::definition::Payload(), obj.GetPayload());

            return pt;
        }
    }

    Object::Object(const size_t id, const std::string &payload)
        : id(id), payload(payload)
    {

    }

    bool Object::operator==(const Object &other) const
    {
        return id == other.id;
    }

    bool Object::operator<(const Object &other) const
    {
        return id < other.id;
    }

    std::ostream& operator<<(std::ostream &os, const Object &obj)
    {
        os << "Object ID : " << obj.GetId() << std::endl
           <<" Payload   : " << obj.GetPayload() << std::endl;

        return os;
    }

    const std::string& Object::GetPayload() const
    {
        return payload;
    }

    size_t Object::GetId() const
    {
        return id;
    }
}


