// thread_provider.cpp
#include "thread_provider.h"
#include "rtc_base/thread.h" // 头文件依赖移到 .cpp 文件中
#include <unordered_map>
#include <mutex>
#include <atomic>
#include <string>
#include <list>
#include <memory>

namespace vi
{

    class ThreadProviderImpl
    {
    public:
        ThreadProviderImpl() : _mainThread(nullptr), _inited(false), _destroy(false) {}

        ~ThreadProviderImpl()
        {
            stopAll();
        }

        void init()
        {
            // 初始化逻辑
            _inited = true;
        }

        void destroy()
        {
            // 销毁逻辑
            _destroy = true;
        }

        void create(const std::list<std::string> &threadNames)
        {
            for (const auto &name : threadNames)
            {
                std::unique_ptr<rtc::Thread> rawThread = rtc::Thread::Create(); // 使用 Create 方法创建线程
                rawThread->Start();
                _threadsMap[name] = std::shared_ptr<rtc::Thread>(rawThread.release(), [](rtc::Thread *t)
                                                                 { t->Stop(); delete t; }); // 使用自定义删除器
            }
        }

        rtc::Thread *thread(const std::string &name)
        {
            auto it = _threadsMap.find(name);
            if (it != _threadsMap.end())
            {
                return it->second.get();
            }
            return nullptr;
        }

        void stopAll()
        {
            for (auto &pair : _threadsMap)
            {
                pair.second->Stop();
            }
            _threadsMap.clear();
        }

    private:
        std::unordered_map<std::string, std::shared_ptr<rtc::Thread>> _threadsMap;
        std::mutex _mutex;
        rtc::Thread *_mainThread;
        std::atomic_bool _inited;
        std::atomic_bool _destroy;
    };

    ThreadProvider::ThreadProvider() : _impl(std::make_unique<ThreadProviderImpl>()) {}

    ThreadProvider::~ThreadProvider() {}

    void ThreadProvider::init()
    {
        _impl->init();
    }

    void ThreadProvider::destroy()
    {
        _impl->destroy();
    }

    void ThreadProvider::create(const std::list<std::string> &threadNames)
    {
        _impl->create(threadNames);
    }

    rtc::Thread *ThreadProvider::thread(const std::string &name)
    {
        return _impl->thread(name);
    }

    void ThreadProvider::stopAll()
    {
        _impl->stopAll();
    }

}