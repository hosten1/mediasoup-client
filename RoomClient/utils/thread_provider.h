/**
 * This file is part of mediasoup_client project.
 * Author:    Jackie Ou
 * Created:   2021-11-01
 **/
/**
 * This file is part of mediasoup_client project.
 * Author:    Jackie Ou
 * Created:   2021-11-01
 **/

#ifndef ROOMCLIENT_UTILS_THREAD_PROVIDER_H_
#define ROOMCLIENT_UTILS_THREAD_PROVIDER_H_
#include <memory>
#include <mutex>
#include <atomic>
#include <string>
#include <list>
#include "singleton.h"

namespace rtc
{
	class Thread;
}
namespace vi
{
	class ThreadProviderImpl; // 声明实现类
	class ThreadProvider : public vi::Singleton<ThreadProvider>
	{
	public:
		ThreadProvider();

		~ThreadProvider();

		void init();

		void destroy();

		void create(const std::list<std::string> &threadNames);

		rtc::Thread *thread(const std::string &name);

	private:
		ThreadProvider(const ThreadProvider &) = delete;

		ThreadProvider(ThreadProvider &&) = delete;

		ThreadProvider &operator=(const ThreadProvider &) = delete;

	public:
		void stopAll();

	private:
		std::unique_ptr<ThreadProviderImpl> _impl; // 指向实现的指针
	};
}

#define TMgr ThreadProvider::sharedInstance()
#endif // ! ROOMCLIENT_UTILS_THREAD_PROVIDER_H_