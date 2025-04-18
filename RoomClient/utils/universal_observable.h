/************************************************************************
 * @Copyright: 2021-2024
 * @FileName:
 * @Description: Open source mediasoup room client library
 * @Version: 1.0.0
 * @Author: Jackie Ou
 * @CreateTime: 2021-10-1
 *************************************************************************/
#ifndef ROOMCLIENT_UTILS_UNIVERSAL_H_
#define ROOMCLIENT_UTILS_UNIVERSAL_H_

#include <type_traits>
#include <list>
#include <algorithm>
#include <string>
#include "absl/types/any.h"
#include "absl/types/optional.h"
#include "rtc_base/deprecated/recursive_critical_section.h"
// #include "rtc_base/thread.h"

namespace vi
{
    template <typename Observer>
    class UniversalObservable
    {
    public:
        using observer_ptr = std::shared_ptr<Observer>;
        void addWeakObserver(const observer_ptr &observer, absl::optional<std::string> threadName);
        void addObserver(const observer_ptr &observer, absl::optional<std::string> threadName);
        void removeObserver(const observer_ptr &observer);
        void clearObserver();
        size_t numOfObservers();
        bool hasObserver(const observer_ptr &observer);

    protected:
        bool hasObserverInternal(const observer_ptr &observer);
        virtual void notifyObservers(std::function<void(const observer_ptr &)> notifier) const;

    private:
        template <typename T = std::shared_ptr<Observer>>
        class InnerObject
        {
        public:
            InnerObject(std::shared_ptr<Observer> o, absl::optional<std::string> name)
                : observer(o), threadName(name)
            {
            }

            T observer;
            absl::optional<std::string> threadName;
        };

        using WeakObject = InnerObject<std::weak_ptr<Observer>>;
        using Object = InnerObject<std::shared_ptr<Observer>>;

        rtc::RecursiveCriticalSection _criticalSection;
        std::list<absl::any> _observers;
    };
}
#endif // ! ROOMCLIENT_UTILS_UNIVERSAL_H_