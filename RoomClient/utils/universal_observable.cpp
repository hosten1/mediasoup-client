#include "utils/universal_observable.h" // 确保路径正确
#include "thread_provider.h"            // 在实现文件中包含完整头文件

namespace vi
{
    template <typename Observer>
    void UniversalObservable<Observer>::addWeakObserver(const observer_ptr &observer, absl::optional<std::string> threadName)
    {
        rtc::CritScope scope(&_criticalSection);
        if (!hasObserverInternal(observer))
        {
            _observers.emplace_back(WeakObject{observer, threadName});
        }
    }

    template <typename Observer>
    void UniversalObservable<Observer>::addObserver(const observer_ptr &observer, absl::optional<std::string> threadName)
    {
        rtc::CritScope scope(&_criticalSection);
        if (!hasObserverInternal(observer))
        {
            _observers.emplace_back(Object{observer, threadName});
        }
    }

    template <typename Observer>
    void UniversalObservable<Observer>::removeObserver(const observer_ptr &observer)
    {
        rtc::CritScope scope(&_criticalSection);
        auto it = std::find_if(_observers.begin(), _observers.end(),
                               [&observer](const auto &item)
                               {
                                   return matchesObserver(item, observer);
                               });
        if (it != _observers.end())
        {
            _observers.erase(it);
        }
    }

    template <typename Observer>
    void UniversalObservable<Observer>::clearObserver()
    {
        rtc::CritScope scope(&_criticalSection);
        _observers.clear();
    }

    template <typename Observer>
    size_t UniversalObservable<Observer>::numOfObservers()
    {
        rtc::CritScope scope(&_criticalSection);
        return _observers.size();
    }

    template <typename Observer>
    bool UniversalObservable<Observer>::hasObserver(const observer_ptr &observer)
    {
        rtc::CritScope scope(&_criticalSection);
        return hasObserverInternal(observer);
    }

    template <typename Observer>
    bool UniversalObservable<Observer>::hasObserverInternal(const observer_ptr &observer) const
    {
        for (const auto &item : _observers)
        {
            if (matchesObserver(item, observer))
            {
                return true;
            }
        }
        return false;
    }

    template <typename Observer>
    void UniversalObservable<Observer>::notifyObservers(std::function<void(const observer_ptr &)> notifier) const
    {
        decltype(_observers) observers;
        {
            rtc::CritScope scope(&_criticalSection);
            observers = _observers;
        }

        for (const auto &item : observers)
        {
            std::shared_ptr<Observer> obs;
            absl::optional<std::string> threadName;

            std::visit([&](const auto &obj)
                       {
                obs = obj.observer.lock();
                threadName = obj.threadName; }, item);

            if (obs)
            {
                rtc::Thread *thread = TMgr->thread(threadName.value_or(""));
                assert(thread);
                if (thread->IsCurrent())
                {
                    notifier(obs);
                }
                else
                {
                    thread->PostTask(RTC_FROM_HERE, [wobs = std::weak_ptr<Observer>(obs), notifier]()
                                     {
                        if (auto observer = wobs.lock())
                        {
                            notifier(observer);
                        } });
                }
            }
        }
    }

    template <typename Observer>
    bool UniversalObservable<Observer>::matchesObserver(const std::variant<WeakObject, Object> &item, const observer_ptr &observer) const
    {
        return std::visit([&](const auto &obj)
                          {
            if (obj.observer.lock() == observer || obj.observer == observer)
            {
                return true;
            }
            return false; }, item);
    }

    // 显式实例化模板，替换为实际观察者类型
    template class UniversalObservable<MyObserver>; // 替换 MyObserver 为实际类型
}