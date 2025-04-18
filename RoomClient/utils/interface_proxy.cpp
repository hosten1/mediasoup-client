
#include "utils/interface_proxy.h"
#include "rtc_base/thread.h"

namespace vi
{

    template <typename T, typename R, typename... Args>
    R MethodCall<T, R, Args...>::marshal(const std::string &name)
    {
        const auto task = [&]()
        {
            this->invoke(std::index_sequence_for<Args...>());
            _promises.set_value();
        };

        rtc::Thread *thread = TMgr->thread(name);
        assert(thread);
        if (thread->IsCurrent())
        {
            task();
        }
        else
        {
            thread->PostTask(RTC_FROM_HERE, task);
            std::future<void> future = _promises.get_future();
            future.get();
        }

        return _result.get();
    }

    // 显式实例化模板类（如果需要）
    // template class MethodCall<SomeClass, void>;
    // template class MethodCall<SomeClass, int, int>;

}