#include "api/media_stream_interface.h"
#include "app_delegate.h"
#include "logger/u_logger.h"
#include "mainwindow.h"
#include "mediasoupclient.hpp"
#include "rtc_base/physical_socket_server.h"
#include "service/i_room_client_observer.h"
#include <QApplication>
#include <QMetaType>
#include <QOpenGLFunctions>

static void registerMetaTypes() {
  qRegisterMetaType<vi::RoomState>("vi::RoomState");
  qRegisterMetaType<rtc::scoped_refptr<webrtc::MediaStreamTrackInterface>>(
      "rtc::scoped_refptr<webrtc::MediaStreamTrackInterface>");
  qRegisterMetaType<std::shared_ptr<vi::IParticipant>>(
      "std::shared_ptr<vi::IParticipant>");
  qRegisterMetaType<webrtc::VideoFrame *>("const webrtc::VideoFrame*");
}

int main(int argc, char *argv[]) {
  registerMetaTypes();

  rtc::PhysicalSocketServer ss;
  rtc::AutoSocketServerThread main_thread(&ss);

  vi::ULogger::init();
  AppDelegate::sharedInstance()->init();
  mediasoupclient::Initialize();

  DLOG("mediasoupclient version: {}", mediasoupclient::Version().c_str());

  QApplication a(argc, argv);

  QSurfaceFormat format;
  format.setDepthBufferSize(24);
  format.setStencilBufferSize(8);
  format.setVersion(4, 1);
  format.setProfile(QSurfaceFormat::CoreProfile);
  QSurfaceFormat::setDefaultFormat(format);

  MainWindow w;
  w.init();
  w.show();
  int ret = a.exec();

  mediasoupclient::Cleanup();
  AppDelegate::sharedInstance()->destroy();
  vi::ULogger::destroy();

  return ret;
  // return 0;
}
