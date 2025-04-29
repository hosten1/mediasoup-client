/************************************************************************
 * @Copyright: 2021-2024
 * @FileName:
 * @Description: Open source mediasoup room client library
 * @Version: 1.0.0
 * @Author: Jackie Ou
 * @CreateTime: 2021-10-1
 *************************************************************************/

#include "thread_provider.h"
#include "logger/u_logger.h"
#include "rtc_base/physical_socket_server.h"
#include "rtc_base/thread.h" // 头文件依赖移到 .cpp 文件中
#include <atomic>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_map>

namespace vi {

ThreadProvider::ThreadProvider() : _inited(false), _destroy(true) {}

ThreadProvider::~ThreadProvider() {
  DLOG("~ThreadProvider()");
  if (!_destroy) {
    stopAll();
  }
}

void ThreadProvider::init() {
  std::lock_guard<std::mutex> lock(_mutex);

  _mainThread = rtc::ThreadManager::Instance()->CurrentThread();

  _inited = true;
}

void ThreadProvider::destroy() { _destroy = true; }

void ThreadProvider::create(const std::list<std::string> &threadNames) {
  std::lock_guard<std::mutex> lock(_mutex);

  if (!_inited) {
    DLOG("_inited == false");
    return;
  }

  for (const auto &name : threadNames) {
    _threadsMap[name] = rtc::Thread::Create();
    _threadsMap[name]->SetName(name, nullptr);
    _threadsMap[name]->Start();
  }
}

void ThreadProvider::stopAll() {
  std::lock_guard<std::mutex> lock(_mutex);

  for (const auto &thread : _threadsMap) {
    thread.second->Stop();
  }
  _threadsMap.clear();

  _destroy = true;
}

rtc::Thread *ThreadProvider::thread(const std::string &name) {
  std::lock_guard<std::mutex> lock(_mutex);

  if (name == "main") {
    return _mainThread;
  } else if (_threadsMap.find(name) != _threadsMap.end()) {
    return _threadsMap[name].get();
  }

  return nullptr;
}

} // namespace vi
