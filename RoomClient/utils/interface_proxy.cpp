
#include "utils/interface_proxy.h"
#include "rtc_base/thread.h"
#include "service/i_room_client.h"
#include "service/i_media_controller.h"
#include "service/i_participant_controller.h"

namespace vi
{

    // template <typename T, typename R, typename... Args>
    // R MethodCall<T, R, Args...>::marshal(const std::string &name)
    // {
    //     const auto task = [&]()
    //     {
    //         this->invoke(std::index_sequence_for<Args...>());
    //         _promises.set_value();
    //     };

    //     rtc::Thread *thread = TMgr->thread(name);
    //     assert(thread);
    //     if (thread->IsCurrent())
    //     {
    //         task();
    //     }
    //     else
    //     {
    //         thread->PostTask(RTC_FROM_HERE, task);
    //         std::future<void> future = _promises.get_future();
    //         future.get();
    //     }

    //     return _result.get();
    // }

    // // // 显式实例化模板类（如果需要）
    // // 在 interface_proxy.cpp 中显式实例化
    // template class vi::MethodCall<vi::IRoomClient, std::__1::shared_ptr<vi::IMediaController>>;
    // template class vi::MethodCall<vi::IRoomClient, std::__1::shared_ptr<vi::IParticipantController>>;
    // template class vi::MethodCall<vi::IRoomClient, void>;
    // template class vi::MethodCall<vi::IRoomClient, void, std::__1::shared_ptr<vi::IRoomClientObserver>>;
    // template class vi::MethodCall<vi::IRoomClient, void, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const &, unsigned short, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const &, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const &, std::__1::shared_ptr<vi::Options>>;
    // template class vi::MethodCall<vi::IMediaController, bool>;
    // template class vi::MethodCall<vi::IMediaController, bool, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const &>;
    // template class vi::MethodCall<vi::IMediaController, void>;
    // template class vi::MethodCall<vi::IMediaController, void, std::__1::shared_ptr<vi::IMediaControllerObserver>>;
    // template class vi::MethodCall<vi::IMediaController, void, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const &, bool>;
    // template class vi::MethodCall<vi::IMediaController, void, bool>;
    // template class vi::MethodCall<vi::IParticipantController, std::__1::shared_ptr<std::__1::unordered_map<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>, std::__1::shared_ptr<vi::IParticipant>, std::__1::hash<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>, std::__1::equal_to<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>>>, std::__1::allocator<std::__1::pair<std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const, std::__1::shared_ptr<vi::IParticipant>>>>>>;
    // template class vi::MethodCall<vi::IParticipantController, std::__1::shared_ptr<vi::IParticipant>, std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char>> const &>;
    // template class vi::MethodCall<vi::IParticipantController, void>;
    // template class vi::MethodCall<vi::IParticipantController, void, std::__1::shared_ptr<vi::IParticipantControllerObserver>>;
}