#ifndef UTIL_H
#define UTIL_H

#include <string>
#include <set>

#include <boost/property_tree/ptree.hpp>

namespace util
{
    class Object
    {
    public:
        Object(const size_t id, const std::string& payload);

        bool operator==(const Object& other) const;
        bool operator<(const Object& other) const;

        friend std::ostream& operator<<(std::ostream& os, const Object& obj);

        size_t GetId() const;
        const std::string& GetPayload() const;

        static std::set<Object>::iterator FindObjectById(const std::set<Object>& objects, const int id)
        {
            for (auto it = objects.begin(); it != objects.end(); ++it)
            {
                if (it->GetId() == id)
                {
                    return it;
                }
            }
            return objects.end(); // Return objects.end() if not found
        }
    private:
        size_t id;
        std::string payload;
    };

    namespace json
    {
        std::string Serialize(const boost::property_tree::ptree& pt);
        Object ToObject(const boost::property_tree::ptree& pt);
        boost::property_tree::ptree FromObject(const util::Object& obj);
    }

}



#endif // UTIL_H
