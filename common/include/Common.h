#ifndef COMMON_H
#define COMMON_H

namespace data
{
    namespace definition
    {
        constexpr auto Id() {return "id";}
        constexpr auto Payload() {return "payload";}
    }
}

namespace connection
{
    constexpr auto Host() {return "127.0.0.1";}
    constexpr auto Port() {return 8080;}
    constexpr auto Target() {return "/endpoint";}
    constexpr auto HTTPVersion() {return 11;}
    constexpr auto ContentType() {return "application/json";}
}



#endif // COMMON_H
