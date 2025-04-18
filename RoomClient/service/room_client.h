#ifndef ROOMCLIENT_SERVICE_ROOM_CLIENT_H_
#define ROOMCLIENT_SERVICE_ROOM_CLIENT_H_

#include <memory>
#include <unordered_map>
#include <cstdint>
#include "i_room_client.h"

namespace vi
{

    class IComponentFactory;
    class ISignalingClient;
    class IMediasoupApi;
    class MacTrackSource;
    class IParticipant;
    class MediaController;
    class ParticipantController;

    class RoomClientImpl;

    class RoomClient : public IRoomClient
    {
    public:
        RoomClient(std::weak_ptr<IComponentFactory> wcf);

        ~RoomClient();

        void init() override;

        void destroy() override;

        void addObserver(std::shared_ptr<IRoomClientObserver> observer) override;

        void removeObserver(std::shared_ptr<IRoomClientObserver> observer) override;

        void join(const std::string &host, uint16_t port, const std::string &roomId, const std::string &displayName, std::shared_ptr<Options> options) override;

        void leave() override;

        std::shared_ptr<IMediaController> getMediaController() override;

        std::shared_ptr<IParticipantController> getParticipantController() override;

        static std::string initLibMediasoup();
        static void CleanupLibMediasoup();

    private:
        std::shared_ptr<RoomClientImpl> _roomclientImpl;
    };

}
#endif // ROOMCLIENT_SERVICE_ROOM_CLIENT_H_