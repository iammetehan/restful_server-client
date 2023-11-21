#include "Data.h"

#include <algorithm>

#include <boost/random.hpp>

namespace data
{
    namespace create
    {
        namespace random
        {
            static std::size_t GenerateId()
            {
                using namespace boost::random;

                constexpr std::size_t minInterval = 0;
                constexpr std::size_t maxInterval = 1000;

                static mt19937 rng;
                static uniform_int_distribution<> dist(minInterval, maxInterval);

                return dist(rng);
            }

            static std::string GeneratePayload()
            {
                using namespace boost::random;

                constexpr std::size_t minInterval = 65;
                constexpr std::size_t maxInterval = 90;

                constexpr std::size_t payloadSize = 255;

                static mt19937 rng;
                static uniform_int_distribution<> dist(minInterval, maxInterval);

                static std::string payload(payloadSize, 0);

                for (int i = 0; i < payloadSize; ++i)
                {
                    payload[i] = dist(rng);
                }

                return payload;
            }

            util::Object Object()
            {
                util::Object obj(GenerateId(), GeneratePayload());
                return obj;
            }
        }
    }

    namespace select
    {
        namespace random
        {
            size_t Id(const std::set<size_t>& objects)
            {
                using namespace boost::random;

                if (1 == objects.size())
                {
                    return *objects.begin();
                }

                mt19937 rng;
                uniform_int_distribution<> dist(0, objects.size());

                std::set<size_t>::iterator it = objects.begin();
                std::advance(it, dist(rng));
                return *it;
            }
        }
    }
}
