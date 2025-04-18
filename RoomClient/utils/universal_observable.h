#ifndef ROOMCLIENT_UTILS_UNIVERSAL_H_
#define ROOMCLIENT_UTILS_UNIVERSAL_H_

#include <type_traits>
#include <vector>
#include <variant>
#include <algorithm>
#include "absl/types/optional.h"
#include "rtc_base/deprecated/recursive_critical_section.h"

namespace vi
{
    class TMgr; // // 前置声明 TMgr 类型

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
        virtual void notifyObservers(std::function<void(const observer_ptr &)> notifier) const;

    private:
        template <typename T = std::shared_ptr<Observer>>
        struct InnerObject
        {
            InnerObject(std::shared_ptr<Observer> o, absl::optional<std::string> name)
                : observer(o), threadName(name)
            {
            }

            T observer;
            absl::optional<std::string> threadName;
        };

        using WeakObject = InnerObject<std::weak_ptr<Observer>>;
        using Object = InnerObject<std::shared_ptr<Observer>>;

        bool hasObserverInternal(const observer_ptr &observer) const;
        bool matchesObserver(const std::variant<WeakObject, Object> &item, const observer_ptr &observer) const;

        mutable rtc::RecursiveCriticalSection _criticalSection;
        std::vector<std::variant<WeakObject, Object>> _observers;
    };
}
#endif // ! ROOMCLIENT_UTILS_UNIVERSAL_H_