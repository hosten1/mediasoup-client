#pragma once

#include <memory>
#include "utils/interface_proxy.h"

namespace vi
{

    class IMediaControllerObserver;

    class IMediaController
    {
    public:
        virtual ~IMediaController() = default;

        virtual void init() = 0;

        virtual void destroy() = 0;

        virtual void addObserver(std::shared_ptr<IMediaControllerObserver> observer) = 0;

        virtual void removeObserver(std::shared_ptr<IMediaControllerObserver> observer) = 0;

        virtual void enableAudio(bool enabled) = 0;

        virtual bool isAudioEnabled() = 0;

        virtual void muteAudio(bool muted) = 0;

        virtual bool isAudioMuted() = 0;

        virtual void enableVideo(bool enabled) = 0;

        virtual bool isVideoEnabled() = 0;

        virtual void muteAudio(const std::string &id, bool muted) = 0;

        virtual bool isAudioMuted(const std::string &id) = 0;
    };

    MI_BEGIN_PROXY_MAP(IMediaController)
    MI_PROXY_METHOD0(void, init)
    MI_PROXY_METHOD0(void, destroy)
    MI_PROXY_METHOD1(void, addObserver, std::shared_ptr<IMediaControllerObserver>)
    MI_PROXY_METHOD1(void, removeObserver, std::shared_ptr<IMediaControllerObserver>)
    MI_PROXY_METHOD1(void, enableAudio, bool)
    MI_PROXY_METHOD0(bool, isAudioEnabled)
    MI_PROXY_METHOD1(void, muteAudio, bool)
    MI_PROXY_METHOD0(bool, isAudioMuted)
    MI_PROXY_METHOD1(void, enableVideo, bool)
    MI_PROXY_METHOD0(bool, isVideoEnabled)
    MI_PROXY_METHOD2(void, muteAudio, const std::string &, bool)
    MI_PROXY_METHOD1(bool, isAudioMuted, const std::string &)
    MI_END_PROXY_MAP()
}
