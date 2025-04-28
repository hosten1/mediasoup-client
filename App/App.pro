#CONFIG(debug, debug | release) {
#    DESTDIR = $$PWD/../RoomClient/Debug
#} else {
#    DESTDIR = $$PWD/../RoomClient/Release
#}

QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# --- 3. macOS special settings ---
macx {
     CONFIG += app_bundle
     DEFINES += WEBRTC_POSIX WEBRTC_MAC ASIO_STANDALONE GL_SILENCE_DEPRECATION

     QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
     QMAKE_CFLAGS += -mmacosx-version-min=10.7
     QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
     QMAKE_INFO_PLIST = $$PWD/../RoomClient/deps/macos/Info.plist


     ENTITLEMENTS_FILE = $$PWD/../RoomClient/deps/macos/App.entitlements
     TARGET_APP_PATH = $$OUT_PWD/$${TARGET}.app/Contents/

     # 复制 entitlements 文件
     QMAKE_POST_LINK += cp $$ENTITLEMENTS_FILE $$TARGET_APP_PATH
     message(Post link command: $$QMAKE_POST_LINK)
     QMAKE_CXXFLAGS += -fobjc-arc -objc
     QMAKE_OBJCFLAGS += -fobjc-arc
     HEADERS += \
                 $$PWD/../RoomClient/deps/macos/promisedevice.h
     OBJECTIVE_SOURCES += \
                 $$PWD/../RoomClient/deps/macos/promisedevice.mm
           # OpenSSL 依赖
     #     INCLUDEPATH += $$PWD/../RoomClient/deps/macos/ssl1.1.1w/include
     #     LIBS += -L$$PWD/../RoomClient/deps/macos/ssl1.1.1w/lib -lssl -lcrypto
     # GLEW + frameworks
         LIBS += -L/usr/local/Cellar/glew/2.2.0_1/lib/ -lGLEW
         LIBS += -framework AudioToolbox -framework CoreAudio -framework AVFoundation -framework CoreMedia -framework CoreVideo
         LIBS += -framework CoreGraphics -framework ApplicationServices
         QMAKE_CXXFLAGS += -stdlib=libc++
         QMAKE_LFLAGS  += -stdlib=libc++
}

#在 Qt 项目里遇到第三方库（比如 sigslot）也用到 emit、signals、slots 这些名字时，就会和 Qt 的 moc 关键字冲突，报出类似：
#CONFIG += no_keywords


INCLUDEPATH += $$PWD/../RoomClient \
    $$PWD/../RoomClient/client/include \
    $$PWD/../RoomClient/deps/webrtc/include/webrtc \
    $$PWD/../RoomClient/deps/webrtc/include/webrtc/third_party/abseil-cpp \
    $$PWD/../RoomClient/deps/webrtc/include/webrtc/third_party/boringssl/src/include \
    $$PWD/../RoomClient/deps/macos \
    $$PWD/../RoomClient/deps/spdlog/include \
    $$PWD/../RoomClient/deps/rapidjson/include \
    $$PWD/../RoomClient/deps/asio/asio/include \
    $$PWD/../RoomClient/deps/rapidjson/include \
    $$PWD/../RoomClient/deps/libmediasoupclient/include \
    $$PWD/../RoomClient/deps/libsdptransform/include/json.hpp \
+   /usr/local/Cellar/glew/2.2.0_1/include

LIBS += -L$$PWD/../RoomClient/deps/webrtc/lib/ -lwebrtc
# iOS和MacOS 下都生效
mac {
    LIBS += -L$$PWD/../RoomClient/deps/webrtc/lib/ -lsdk_combined
}
LIBS += -L$$PWD/../RoomClient/deps/libssl/lib/ -lcrypto
LIBS += -L$$PWD/../RoomClient/deps/libssl/lib/ -lssl


CONFIG(debug, debug | release) {
   LIBS += -L$$PWD/../RoomClient/Debug -lRoomClient

}
else {
    LIBS += -L$$PWD/../RoomClient/Release -lRoomClient

}

SOURCES += \
    app_delegate.cpp \
    gallery_view.cpp \
    mac_video_renderer.cpp \
    main.cpp \
    mainwindow.cpp \
    media_event_adapter.cpp \
    participant_event_adapter.cpp \
    room_event_adapter.cpp \
    video_renderer.cpp

HEADERS += \
    app_delegate.h \
    gallery_view.h \
    mac_video_renderer.h \
    mainwindow.h \
    media_event_adapter.h \
    participant_event_adapter.h \
    room_event_adapter.h \
    video_renderer.h

FORMS += \
    gallery_view.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
