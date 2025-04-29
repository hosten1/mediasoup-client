#CONFIG(debug, debug | release) {
#    DESTDIR = $$PWD/../RoomClient/Debug
#} else {
#    DESTDIR = $$PWD/../RoomClient/Release
#}

QT       += core gui opengl openglwidgets
QT += core opengl openglwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

win: {
    DEFINES += GL_SILENCE_DEPRECATION
    DEFINES += UNICODE
    DEFINES += _UNICODE
    DEFINES += WIN32
    DEFINES += _ENABLE_EXTENDED_ALIGNED_STORAGE
    DEFINES += WIN64
    DEFINES += BUILD_STATIC
    DEFINES += USE_AURA=1
    DEFINES += NO_TCMALLOC
    DEFINES += FULL_SAFE_BROWSING
    DEFINES += SAFE_BROWSING_CSD
    DEFINES += SAFE_BROWSING_DB_LOCAL
    DEFINES += CHROMIUM_BUILD
    DEFINES += _HAS_EXCEPTIONS=0
    DEFINES += __STD_C
    DEFINES += _CRT_RAND_S
    DEFINES += _CRT_SECURE_NO_DEPRECATE
    DEFINES += _SCL_SECURE_NO_DEPRECATE
    DEFINES += _ATL_NO_OPENGL
    DEFINES += CERT_CHAIN_PARA_HAS_EXTRA_FIELDS
    DEFINES += PSAPI_VERSION=2
    DEFINES += _SECURE_ATL
    DEFINES += _USING_V110_SDK71_
    DEFINES += WINAPI_FAMILY=WINAPI_FAMILY_DESKTOP_APP
    DEFINES += WIN32_LEAN_AND_MEAN
    DEFINES += NOMINMAX
    DEFINES += NTDDI_VERSION=NTDDI_WIN10_RS2
    DEFINES += _WIN32_WINNT=0x0A00
    DEFINES += WINVER=0x0A00
    DEFINES += DYNAMIC_ANNOTATIONS_ENABLED=1
    DEFINES += WTF_USE_DYNAMIC_ANNOTATIONS=1
    DEFINES += WEBRTC_ENABLE_PROTOBUF=1
    DEFINES += WEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE
    DEFINES += RTC_ENABLE_VP9
    DEFINES += HAVE_SCTP
    DEFINES += WEBRTC_USE_H264
    DEFINES += WEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0
    DEFINES += WEBRTC_WIN
    DEFINES += ABSL_ALLOCATOR_NOTHROW=1
    DEFINES += HAVE_WEBRTC_VIDEO
    DEFINES += HAVE_WEBRTC_VOICE
    DEFINES += ASIO_STANDALONE
    DEFINES += _WEBSOCKETPP_CPP11_INTERNAL_
}

unix: {
    DEFINES += WEBRTC_MAC
    DEFINES += WEBRTC_POSIX
}

DEFINES += ABSL_ALLOCATOR_NOTHROW=1
DEFINES += ASIO_STANDALONE
#QMAKE_MACOSX_DEPLOYMENT_TARGET=10.15

#QMAKE_POST_LINK += sed -i -e "s/@VERSION@/$$VERSION/g" "../Debug/$${TARGET}.app/Contents/Info.plist"

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
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
    DESTDIR = $$PWD/../Debug
    win: {
        LIBS += $$PWD/../deps/glew/lib/Release/x64/glew32.lib
        LIBS += winmm.lib Advapi32.lib comdlg32.lib dbghelp.lib dnsapi.lib gdi32.lib msimg32.lib odbc32.lib odbccp32.lib oleaut32.lib shell32.lib shlwapi.lib user32.lib usp10.lib uuid.lib version.lib wininet.lib winmm.lib winspool.lib ws2_32.lib delayimp.lib kernel32.lib ole32.lib crypt32.lib iphlpapi.lib secur32.lib dmoguids.lib wmcodecdspuuid.lib amstrmid.lib msdmo.lib strmiids.lib opengl32.lib glu32.lib

        LIBS += $$PWD/../deps/webrtc/lib/windows_debug_x64/webrtc.lib
        LIBS += $$PWD/../deps/cpr/debug/lib/cpr.lib
        LIBS += $$PWD/../deps/cpr/debug/lib/libcurl-d.lib
        LIBS += $$PWD/../deps/cpr/debug/lib/zlibd.lib
        LIBS += $$PWD/../Debug/RoomClient.lib
        QMAKE_CXXFLAGS_DEBUG = /MTd /Zi
    }
    unix: {
        LIBS += -L/usr/local/Cellar/glew/2.2.0_1/lib/ -lGLEW
        LIBS += -framework AudioToolbox -framework CoreAudio -framework AVFoundation -framework CoreMedia -framework CoreVideo

        LIBS += -L$$PWD/../deps/webrtc/lib/ -lwebrtc
        LIBS += -L$$PWD/../Debug/ -lRoomClient
        LIBS += -L/usr/local/Cellar/cpr/1.10.5/lib -lcpr
    }
} else {
    win: {
        DESTDIR = $$PWD/../Release
        LIBS += $$PWD/../deps/webrtc/lib/windows_release_x64/webrtc.lib
        LIBS += $$PWD/../deps/cpr/lib/cpr.lib
        LIBS += $$PWD/../deps/cpr/lib/libcurl.lib
        LIBS += $$PWD/../deps/cpr/lib/zlib.lib
        LIBS += $$PWD/../Release/RoomClient.lib
        QMAKE_CXXFLAGS_RELEASE = /MT
    }
    unix: {
        LIBS += -L/usr/local/Cellar/glew/2.2.0_1/lib/ -lGLEW
        LIBS += -framework AudioToolbox -framework CoreAudio -framework AVFoundation -framework CoreMedia -framework CoreVideo

        LIBS += -L$$PWD/../deps/webrtc/lib/ -lwebrtc
        LIBS += -L$$PWD/../Debug/ -lRoomClient
        LIBS += -L/usr/local/Cellar/cpr/1.10.5/lib -lcpr
    }
}

SOURCES += \
    gallery_view.cpp \
    main.cpp \
    mainwindow.cpp \
    participant_event_handler_wrapper.cpp \
    participant_item_view.cpp \
    participant_list_view.cpp \
    room_client_event_handler_wrapper.cpp \
    table.cpp \
    video_renderer.cpp

HEADERS += \
    gallery_view.h \
    mainwindow.h \
    participant_event_handler_wrapper.h \
    participant_item_view.h \
    participant_list_view.h \
    room_client_event_handler_wrapper.h \
    table.h \
    video_renderer.h

FORMS += \
    gallery_view.ui \
    mainwindow.ui \
    participant_item_view.ui \
    participant_list_view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    icons.qrc

