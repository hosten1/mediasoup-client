/************************************************************************
* @Copyright: 2021-2024
* @FileName:
* @Description: Open source mediasoup room client library
* @Version: 1.0.0
* @Author: Jackie Ou
* @CreateTime: 2021-10-1
*************************************************************************/

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
