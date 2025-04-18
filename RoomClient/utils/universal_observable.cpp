#include "utils/universal_observable.h" // 确保路径正确
#include "thread_provider.h"
#include "rtc_base/thread.h" // 在实现文件中包含完整头文件

namespace vi
{
    // template <typename Observer>
    // void UniversalObservable<Observer>::addWeakObserver(const observer_ptr &observer, absl::optional<std::string> threadName)
    // {
    //     rtc::CritScope scope(&_criticalSection);
    //     if (!hasObserverInternal(observer))
    //     {
    //         WeakObject wobj(observer, threadName);
    //         _observers.emplace_back(wobj);
    //     }
    // }

    // template <typename Observer>
    // void UniversalObservable<Observer>::addObserver(const observer_ptr &observer, absl::optional<std::string> threadName)
    // {
    //     rtc::CritScope scope(&_criticalSection);
    //     if (!hasObserverInternal(observer))
    //     {
    //         Object obj(observer, threadName);
    //         _observers.emplace_back(obj);
    //     }
    // }

    // template <typename Observer>
    // void UniversalObservable<Observer>::removeObserver(const observer_ptr &observer)
    // {
    //     rtc::CritScope scope(&_criticalSection);
    //     for (auto it = _observers.begin(); it != _observers.end(); ++it)
    //     {
    //         auto var = absl::any(*it);
    //         if (var.has_value())
    //         {
    //             if (absl::any_cast<WeakObject>(&var))
    //             {
    //                 WeakObject wobj = absl::any_cast<WeakObject>(var);
    //                 if (wobj.observer.lock() == observer)
    //                 {
    //                     _observers.erase(it);
    //                     return;
    //                 }
    //             }
    //             else if (absl::any_cast<Object>(&var))
    //             {
    //                 Object obj = absl::any_cast<Object>(var);
    //                 if (obj.observer == observer)
    //                 {
    //                     _observers.erase(it);
    //                     return;
    //                 }
    //             }
    //         }
    //     }
    // }

    // template <typename Observer>
    // void UniversalObservable<Observer>::clearObserver()
    // {
    //     rtc::CritScope scope(&_criticalSection);
    //     _observers.clear();
    // }

    // template <typename Observer>
    // size_t UniversalObservable<Observer>::numOfObservers()
    // {
    //     rtc::CritScope scope(&_criticalSection);
    //     return _observers.size();
    // }

    // template <typename Observer>
    // bool UniversalObservable<Observer>::hasObserver(const observer_ptr &observer)
    // {
    //     rtc::CritScope scope(&_criticalSection);
    //     return hasObserverInternal(observer);
    // }

    // template <typename Observer>
    // bool UniversalObservable<Observer>::hasObserverInternal(const observer_ptr &observer)
    // {
    //     for (auto it = _observers.begin(); it != _observers.end(); ++it)
    //     {
    //         auto var = absl::any(*it);
    //         if (var.has_value())
    //         {
    //             if (absl::any_cast<WeakObject>(&var))
    //             {
    //                 WeakObject wobj = absl::any_cast<WeakObject>(var);
    //                 if (wobj.observer.lock() == observer)
    //                 {
    //                     return true;
    //                 }
    //             }
    //             else if (absl::any_cast<Object>(&var))
    //             {
    //                 Object obj = absl::any_cast<Object>(var);
    //                 if (obj.observer == observer)
    //                 {
    //                     return true;
    //                 }
    //             }
    //         }
    //     }

    //     return false;
    // }

    // template <typename Observer>
    // void UniversalObservable<Observer>::notifyObservers(std::function<void(const observer_ptr &)> notifier) const
    // {
    //     decltype(_observers) observers;
    //     {
    //         rtc::CritScope scope(&_criticalSection);
    //         observers = _observers;
    //     }

    //     for (const auto &observer : observers)
    //     {
    //         auto var = absl::any(observer);
    //         if (var.has_value())
    //         {
    //             std::shared_ptr<Observer> obs;
    //             rtc::Thread *thread = nullptr;

    //             if (absl::any_cast<WeakObject>(&var))
    //             {
    //                 WeakObject wobj = absl::any_cast<WeakObject>(var);
    //                 obs = wobj.observer.lock();
    //                 thread = wobj.thread;
    //             }
    //             else if (absl::any_cast<Object>(&var))
    //             {
    //                 Object obj = absl::any_cast<Object>(var);
    //                 obs = obj.observer;
    //                 thread = obj.thread;
    //             }

    //             if (obs)
    //             {
    //                 assert(thread);
    //                 if (thread->IsCurrent())
    //                 {
    //                     notifier(obs);
    //                 }
    //                 else
    //                 {
    //                     thread->PostTask([wobs = std::weak_ptr<Observer>(obs), notifier]()
    //                                      {
    // 							if (auto observer = wobs.lock()) {
    //                                 notifier(observer);
    // 							} });
    //                 }
    //             }
    //         }
    //     }
    // }
}