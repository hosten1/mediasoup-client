/**
 * This file is part of mediasoup_client project.
 * Author:    Jackie Ou
 * Created:   2021-11-01
 **/
/************************************************************************
 * @Copyright: 2021-2024
 * @FileName:
 * @Description: Open source mediasoup room client library
 * @Version: 1.0.0
 * @Author: Jackie Ou
 * @CreateTime: 2021-10-1
 *************************************************************************/

#ifndef ROOMCLIENT_UTILS_THREAD_PROVIDER_H_
#define ROOMCLIENT_UTILS_THREAD_PROVIDER_H_
#include "singleton.h"
#include <atomic>
#include <list>
#include <memory>
#include <mutex>
#include <string>

namespace rtc {
class Thread;
}

namespace vi {

class ThreadProvider : public vi::Singleton<ThreadProvider> {
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

  ThreadProvider &operator=(ThreadProvider &&) = delete;

public:
  void stopAll();

private:
  std::unordered_map<std::string, std::shared_ptr<rtc::Thread>> _threadsMap;

  std::mutex _mutex;

  rtc::Thread *_mainThread = nullptr;

  std::atomic_bool _inited;

  std::atomic_bool _destroy;
};
} // namespace vi
#endif // ! ROOMCLIENT_UTILS_THREAD_PROVIDER_H_