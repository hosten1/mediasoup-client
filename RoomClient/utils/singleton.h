#ifndef ROOMCLIENT_UTILS_SINGLETON_H_
#define ROOMCLIENT_UTILS_SINGLETON_H_

#include <memory>
#include <mutex>

namespace vi
{

    template <typename T>
    class Singleton
    {
    public:
        virtual ~Singleton() {}
        static std::shared_ptr<T> &sharedInstance()
        {
            static std::shared_ptr<T> _instance;
            static std::once_flag ocf;
            std::call_once(ocf, [&]()
                           { _instance = std::make_shared<T>(); });
            return _instance;
        }
    };

}

#endif // !ROOMCLIENT_UTILS_SINGLETON_H_