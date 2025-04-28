cmake_minimum_required(VERSION 3.16)
project(RoomClient LANGUAGES CXX)

# ——————————————————————————————————————————————
# 1) Global settings
# ——————————————————————————————————————————————
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# match your Qt .pro deployment target
set(CMAKE_OSX_DEPLOYMENT_TARGET "10.7" CACHE STRING "")
# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -frtti -fexceptions")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wno-sign-conversion -Wno-sign-compare -frtti -fexceptions)
endif()

# ——————————————————————————————————————————————
# 2) Find Qt (Core only, no GUI)
# ——————————————————————————————————————————————
# Qt5 provides its own CMake config files; prefer this form
# find_package(Qt5 COMPONENTS Core REQUIRED)

# ——————————————————————————————————————————————
# 3) Add your staticlib target
# ——————————————————————————————————————————————
set(ROOM_CLIENT_SOURCES
    logger/rtc_log_sink.cpp
    logger/u_logger.cpp
    opengl/i420_texture_cache.cpp
    opengl/video_shader.cpp
    service/base_video_capturer.cc
    service/component_factory.cpp
    service/media_controller.cpp
    service/mediasoup_api.cpp
    service/participant.cpp
    service/participant_controller.cpp
    service/room_client.cpp
    service/signaling_client.cpp
    service/service_factory.cpp
    service/windows_capture.cpp
    utils/bad_any_cast.cc
    # utils/notification_center.cpp

    # utils/notification_keys.cpp
    utils/universal_observable.cpp
    utils/sdp_utils.cpp
    utils/string_utils.cpp
    utils/task_scheduler.cpp
    utils/thread_provider.cpp
    utils/interface_proxy.cpp
    websocket/connection_metadata.cpp
    websocket/websocket_endpoint.cpp
    websocket/websocket_transport.cpp

   
)


list(APPEND ROOM_CLIENT_SOURCES
    logger/rtc_log_sink.h
    logger/u_logger.h
    opengl/gl_defines.h
    opengl/i420_texture_cache.h
    opengl/video_shader.h
    service/i_component_factory.h
    service/i_engine_event_handler.h
    service/i_media_controller_observer.h
    service/i_media_controller.h
    service/i_mediasoup_api.h
    service/i_participant_controller_observer.h
    service/i_participant_controller.h
    service/i_participant.h
    service/i_room_client.h
    service/i_room_client_observer.h
    service/i_service_factory.hpp
    service/i_service.hpp
    service/i_signaling_observer.h
    service/i_signaling_client.h
    service/base_video_capturer.h
    service/component_factory.h
    service/media_controller.h
    service/mediasoup_api.h
    service/participant.h
    service/participant_controller.h
    service/room_client.h
    service/signaling_client.h
    service/service_factory.hpp
    service/windows_capture.h
    service/options.h
    # utils/bad_any_cast.h

    # utils/notification_keys.hpp
    # utils/notification_center.hpp
    # utils/notification.hpp
    utils/i_notification.h
    utils/i_observer.hpp
    utils/universal_observable.hpp

    # utils/universal_observable.h
    utils/sdp_utils.h
    utils/string_utils.h
    utils/task_scheduler.h
    utils/thread_provider.h
    utils/interface_proxy.h
    websocket/i_connection_observer.h
    websocket/i_transport_observer.h
    websocket/i_transport.h
    websocket/websocket_request.h
    websocket/connection_metadata.h
    websocket/websocket_endpoint.h
    websocket/websocket_transport.h
)

# 条件引入平台特定文件
if(APPLE)
    list(APPEND ROOM_CLIENT_SOURCES
        service/mac_capturer.h
        service/mac_capturer.mm
    )
elseif(WIN32)
    list(APPEND ROOM_CLIENT_SOURCES
        service/windows_capture.h
        service/windows_capture.cpp
    )
endif()

# 定义编译选项 是使用 libmediasoupclient 的源码 还是使用编译好的库
option(USE_LIB_MEDIASOUP_CLIENT_SOURCE "Use libmediasoupclient source code" ON)

# 引入 libmediasoupclient 的源码
if(USE_LIB_MEDIASOUP_CLIENT_SOURCE)
    # set(LIBWEBRTC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc" CACHE STRING "libwebrtc include path")
    # set(LIBWEBRTC_BINARY_PATH "" CACHE STRING "libwebrtc binary path")
    # add_subdirectory(deps/libmediasoupclient)
    # Set version number.
    set(mediasoupclient_VERSION_MAJOR 3)
    set(mediasoupclient_VERSION_MINOR 2)
    set(mediasoupclient_VERSION_PATCH 0)
   
    # Configure a header file to pass the version.
    configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/libmediasoupclient/version.hpp.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/deps/libmediasoupclient/include/version.hpp"
    )
    list(APPEND ROOM_CLIENT_SOURCES
        deps/libsdptransform/src/grammar.cpp
        deps/libsdptransform/src/parser.cpp
        deps/libsdptransform/src/writer.cpp
        deps/libmediasoupclient/src/Consumer.cpp
        deps/libmediasoupclient/src/DataConsumer.cpp
        deps/libmediasoupclient/src/DataProducer.cpp
        deps/libmediasoupclient/src/Device.cpp
        deps/libmediasoupclient/src/Handler.cpp
        deps/libmediasoupclient/src/Logger.cpp
        deps/libmediasoupclient/src/PeerConnection.cpp
        deps/libmediasoupclient/src/Producer.cpp
        deps/libmediasoupclient/src/Transport.cpp
        deps/libmediasoupclient/src/mediasoupclient.cpp
        deps/libmediasoupclient/src/ortc.cpp
        deps/libmediasoupclient/src/scalabilityMode.cpp
        deps/libmediasoupclient/src/sdp/MediaSection.cpp
        deps/libmediasoupclient/src/sdp/RemoteSdp.cpp
        deps/libmediasoupclient/src/sdp/Utils.cpp
        deps/libmediasoupclient/include/Consumer.hpp
        deps/libmediasoupclient/include/Device.hpp
        deps/libmediasoupclient/include/Handler.hpp
        deps/libmediasoupclient/include/Logger.hpp
        deps/libmediasoupclient/include/MediaSoupClientErrors.hpp
        deps/libmediasoupclient/include/PeerConnection.hpp
        deps/libmediasoupclient/include/Producer.hpp
        deps/libmediasoupclient/include/Transport.hpp
        deps/libmediasoupclient/include/mediasoupclient.hpp
        deps/libmediasoupclient/include/ortc.hpp
        deps/libmediasoupclient/include/scalabilityMode.hpp
        deps/libmediasoupclient/include/sdp/MediaSection.hpp
        deps/libmediasoupclient/include/sdp/RemoteSdp.hpp
        deps/libmediasoupclient/include/sdp/Utils.hpp
    )
endif() # 修复：添加缺失的 endif()

# 定义编译选项 是使用 libmediasoupclient 的源码 还是使用编译好的库
option(USE_LIB_WEBSOCKETPP_SOURCE "Use libmediasoupclient source code" ON)

# 引入 libmediasoupclient 的源码
if(USE_LIB_WEBSOCKETPP_SOURCE)
    # Force the script to use FetchContent and not CPM internally to fetch asio
    # option(ASIO_USE_CPM "Download Asio with CPM instead of FetchContent" OFF)
    # option(
    # ASIO_CPM_FETCHCONTENT_COMPAT
    # "Should asio be declared with FetchContent functions to be compatible. This doesn't not allow CPM cache to work."
    # ON
    # )

    # # Download this repository
    # include(FetchContent)
    # FetchContent_Declare(
    # asiocmake
    # GIT_REPOSITORY "https://github.com/OlivierLDff/asio.cmake"
    # GIT_TAG "main"
    # )
    # FetchContent_MakeAvailable(asiocmake)

    # ...

    # # Link to the created library asio::asio or asio
    # target_link_libraries(${PROJECT_NAME} PRIVATE asio::asio)
    # set(LIBWEBRTC_INCLUDE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc" CACHE STRING "libwebrtc include path")
    # set(LIBWEBRTC_BINARY_PATH "" CACHE STRING "libwebrtc binary path")
    # add_subdirectory(deps/libmediasoupclient)
    list(APPEND ROOM_CLIENT_SOURCES
        # deps/asio/asio/src/asio.cpp
        # deps/asio/asio/src/asio_ssl.cpp
        deps/websocketpp/websocketpp/client.hpp
        deps/websocketpp/websocketpp/close.hpp
        deps/websocketpp/websocketpp/connection_base.hpp
        deps/websocketpp/websocketpp/connection.hpp
        deps/websocketpp/websocketpp/endpoint_base.hpp
        deps/websocketpp/websocketpp/endpoint.hpp
        deps/websocketpp/websocketpp/error.hpp
        deps/websocketpp/websocketpp/frame.hpp
        deps/websocketpp/websocketpp/server.hpp
        deps/websocketpp/websocketpp/uri.hpp
        deps/websocketpp/websocketpp/utf8_validator.hpp
        deps/websocketpp/websocketpp/utilities.hpp
        deps/websocketpp/websocketpp/version.hpp
        deps/websocketpp/websocketpp/base64/base64.hpp
        # deps/websocketpp/websocketpp/common/*.hpp
        # deps/websocketpp/websocketpp/concurrency/*.hpp
        # deps/websocketpp/websocketpp/config/*.hpp
        # deps/websocketpp/websocketpp/extensions/*.hpp
        # deps/websocketpp/websocketpp/extensions/permessage_deflate/*.hpp
        # deps/websocketpp/websocketpp/http/*.hpp
        # deps/websocketpp/websocketpp/http/impl/*.hpp
        # deps/websocketpp/websocketpp/impl/*.hpp
        # deps/websocketpp/websocketpp/logger/*.hpp
        # deps/websocketpp/websocketpp/message_buffer/*.hpp
        # deps/websocketpp/websocketpp/processors/*.hpp
        # deps/websocketpp/websocketpp/random/*.hpp
        # deps/websocketpp/websocketpp/roles/*.hpp
        # deps/websocketpp/websocketpp/sha1/*.hpp
        # deps/websocketpp/websocketpp/transport/*.hpp
        # deps/websocketpp/websocketpp/transport/asio/*.hpp
        # deps/websocketpp/websocketpp/transport/asio/security/*.hpp
        # deps/websocketpp/websocketpp/transport/base/*.hpp

        # # deps/websocketpp/websocketpp/transport/debug/*.hpp
        # deps/websocketpp/websocketpp/transport/iostream/*.hpp
        # deps/websocketpp/websocketpp/transport/stub/*.hpp
        # deps/websocketpp/websocketpp/sha1/*.hpp
        # deps/websocketpp/websocketpp/sha1/*.hpp
        # deps/websocketpp/tutorials/utility_client
    )
endif() # 修复：添加缺失的 endif()

if(MSVC)
    message(STATUS "MSVC CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

    set_source_files_properties(${ROOM_CLIENT_SOURCES}
        PROPERTIES COMPILE_FLAGS "/W3 /WX")
else()
    message(STATUS "Not MSVC CMAKE_CXX_COMPILER_ID: ${CMAKE_CXX_COMPILER_ID}")

    set_source_files_properties(${ROOM_CLIENT_SOURCES}
        PROPERTIES COMPILE_FLAGS -Wall -Wextra -Wpedantic -Wno-sign-conversion -Wno-sign-compare)
endif()

option(RAPIDJSON_BUILD_DOC "Build rapidjson documentation." OFF)
option(RAPIDJSON_BUILD_EXAMPLES "Build rapidjson examples." OFF)
option(RAPIDJSON_BUILD_TESTS "Build rapidjson perftests and unittests." OFF)
option(RAPIDJSON_BUILD_THIRDPARTY_GTEST
    "Use gtest installation in `thirdparty/gtest` by default if available" OFF)
option(RAPIDJSON_BUILD_CXX11 "Build rapidjson with C++11" ON)
option(RAPIDJSON_BUILD_CXX17 "Build rapidjson with C++17" ON)

add_subdirectory(deps/rapidjson)
add_subdirectory(deps/spdlog)

# add_subdirectory(deps/asio)
# add_subdirectory(deps/websocketpp)
add_library(${PROJECT_NAME} STATIC ${ROOM_CLIENT_SOURCES})

# 对 Debug 生效，添加 -O0 -g；对 Release 生效，使用 -O3
target_compile_options(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:-O0;-g>"
    "$<$<CONFIG:Release>:-O3>"
)

# 仅对 Debug 生效
# target_compile_options(${PROJECT_NAME} PRIVATE
#     "$<$<CONFIG:Debug>:-fno-inline;-fno-inline-small-functions;-fno-lto>"
# )
# set_target_properties(${PROJECT_NAME} PROPERTIES
#     INTERPROCEDURAL_OPTIMIZATION_RELEASE OFF
# )

# ——————————————————————————————————————————————
# 4) Include directories
# ——————————————————————————————————————————————
# 定义依赖路径变量，便于管理和维护
set(WEBSOCKETPP_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/websocketpp)
set(LIBMEDIASOUPCLIENT_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/libmediasoupclient/include)
set(RAPIDJSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/rapidjson/include)
set(SPDLOG_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/spdlog/include)
set(ASIO_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/asio/asio/include)
set(SDPTRANSFORM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/deps/libsdptransform/include)
set(WEBRTC_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc/third_party/abseil-cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc/third_party/boringssl/src/include
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc/third_party
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc/sdk/objc
    ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc/sdk/objc/base
)

# set(JSON_INCLUDE_DIR
# ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc
# ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc/third_party
# ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/include/webrtc/sdk/objc
# )

# 使用 target_include_directories 设置头文件路径
target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    PRIVATE
    ${WEBRTC_INCLUDE_DIRS}
    ${SDPTRANSFORM_INCLUDE_DIR}
    ${RAPIDJSON_INCLUDE_DIR}
    ${SPDLOG_INCLUDE_DIR}
    ${ASIO_INCLUDE_DIR}
    ${WEBSOCKETPP_INCLUDE_DIR}
    ${LIBMEDIASOUPCLIENT_INCLUDE_DIR}
)

# ——————————————————————————————————————————————
# 5) Compile‑time definitions (matches your DEFINES in .pro)
# ——————————————————————————————————————————————
target_compile_definitions(${PROJECT_NAME}
    PRIVATE MSC_LOG_TRACE=1
)
target_compile_definitions(${PROJECT_NAME}
    PRIVATE MSC_LOG_DEV=1
)
# 编译时定义
if(APPLE)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        WEBRTC_POSIX
        WEBRTC_MAC
        ASIO_STANDALONE
        GL_SILENCE_DEPRECATION
        QT_NO_KEYWORDS
    )

    # ——————————————————————————————————————————————
    # 6) Link libraries
    # ——————————————————————————————————————————————
    # Link QtCore statically
    target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/lib/libwebrtc.a
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/lib/libsdk_combined.a
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/libssl/lib/libcrypto.a
        ${CMAKE_CURRENT_SOURCE_DIR}/deps/libssl/lib/libssl.a
        "-framework AppKit"
        "-framework CoreGraphics"
        "-framework ApplicationServices"
        "-framework CoreMedia"
        "-framework CoreVideo"
        "-framework CoreFoundation"
        "-framework CoreAudio"
        "-framework AudioToolbox"
        "-framework AVFoundation")
    # 添加库目录
# link_directories(${CMAKE_CURRENT_SOURCE_DIR}/deps/webrtc/lib/obj)
# 假设你的目标是 my_app 或 my_library
# target_link_libraries(${PROJECT_NAME}
#     PRIVATE
#     absl_flags_parse                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
#     base_native_additions_objc
#     base_objc
#     callback_logger_objc
#     default_codec_factory_objc
#     file_logger_objc
#     helpers_objc
#     media_constraints
#     mediaconstraints_objc
#     mediasource_objc
#     metal_objc
#     native_api
#     native_video
#     peerconnectionfactory_base_objc
#     ui_objc
#     video_objc
#     video_toolbox_cc
#     videocapture_objc
#     videocodec_objc
#     videoframebuffer_objc
#     videorendereradapter_objc
#     videosource_objc
#     videotoolbox_objc
#     vp8
#     vp9
#     vpx_codec_constants
#     wrapped_native_codec_objc
# )
elseif(WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE
        WEBRTC_WIN
        ASIO_STANDALONE
        _WIN32_WINNT=0x0601
    )
endif()


# ——————————————————————————————————————————————
# 7) Output directory
# ——————————————————————————————————————————————
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Debug"
    )
else()
    set_target_properties(${PROJECT_NAME} PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Release"
    )
endif()