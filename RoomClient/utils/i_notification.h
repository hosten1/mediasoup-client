
#ifndef ROOMCLIENT_UTILS_I_NOTIFICATION_H_
#define ROOMCLIENT_UTILS_I_NOTIFICATION_H_

#include <string>

namespace vi
{

    class INotification
    {
    public:
        virtual ~INotification() = default;

        virtual std::string type() { return typeid(*this).name(); };
    };

}
#endif // !ROOMCLIENT_UTILS_I_NOTIFICATION_H_
