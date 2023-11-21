#ifndef REQUEST_H
#define REQUEST_H

#include <string>
#include <boost/property_tree/ptree.hpp>

namespace request
{
    void RepeatNTimes(std::function<void()> function, const size_t& n);

    namespace make
    {
        void Add();
        void Delete();
        void Read();
    }
}

#endif // REQUEST_H
