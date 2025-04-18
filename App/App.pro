QT       += core gui opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

DEFINES += WEBRTC_POSIX WEBRTC_MAC ASIO_STANDALONE GL_SILENCE_DEPRECATION
#QT_NO_KEYWORDS

#QMAKE_INFO_PLIST +=  $${TARGET}/Info.plist
#QMAKE_POST_LINK += sed -i -e "s/@VERSION@/$$VERSION/g" "../Debug/$${TARGET}.app/Contents/Info.plist";

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.7
QMAKE_CFLAGS += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
#在 Qt 项目里遇到第三方库（比如 sigslot）也用到 emit、signals、slots 这些名字时，就会和 Qt 的 moc 关键字冲突，报出类似：
#CONFIG += no_keywords

INCLUDEPATH += $$PWD/../RoomClient \
    $$PWD/../RoomClient/client/include \
    $$PWD/../RoomClient/deps/webrtc/include/webrtc \
    $$PWD/../RoomClient/deps/webrtc/include/webrtc/third_party/abseil-cpp \
    $$PWD/../RoomClient/deps/webrtc/include/webrtc/third_party/boringssl/src/include \
    $$PWD/../RoomClient/deps/spdlog/include \
    $$PWD/../RoomClient/deps/rapidjson/include \
    $$PWD/../RoomClient/deps/asio/asio/include \
    $$PWD/../RoomClient/deps/rapidjson/include \
    $$PWD/../RoomClient/deps/libmediasoupclient/include \
    $$PWD/../RoomClient/deps/libsdptransform/include/json.hpp
    /usr/local/Cellar/glew/2.2.0_1/include

LIBS += -L$$PWD/../RoomClient/deps/webrtc/lib/ -lwebrtc
LIBS += -L$$PWD/../RoomClient/deps/webrtc/lib/ -lsdk_combined
LIBS += -L$$PWD/../RoomClient/deps/libssl/lib/ -lcrypto
LIBS += -L$$PWD/../RoomClient/deps/libssl/lib/ -lssl
LIBS += -L$$PWD/../RoomClient/Release -lRoomClient
mac {
    LIBS += -L/usr/local/Cellar/glew/2.2.0_1/lib/ -lGLEW
    LIBS += -framework AudioToolbox -framework CoreAudio -framework AVFoundation -framework CoreMedia -framework CoreVideo
    LIBS += -framework CoreGraphics \
            -framework ApplicationServices
    QMAKE_CXXFLAGS += -std=c++17 -stdlib=libc++
    QMAKE_LFLAGS  += -stdlib=libc++
}


CONFIG(debug, debug | release) {
    DESTDIR = $$PWD/../Debug
    LIBS += -L$$PWD/../Debug/ -lRoomClient
}
else {
    DESTDIR = $$PWD/../Release
    LIBS += -L$$PWD/../Release/ -lRoomClient
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
