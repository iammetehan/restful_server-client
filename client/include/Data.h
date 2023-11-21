#ifndef DATA_H
#define DATA_H

#include "Util.h"

#include <string>
#include <set>

#include <boost/property_tree/ptree.hpp>

namespace data
{
    namespace create::random
    {
        util::Object Object();
    }

    namespace select::random
    {
        size_t Id(const std::set<size_t>& objects);
    }
}
#endif // DATA_H
