## mediasoup-client
* C++ client side library for building mediasoup based applications
* Windows

## Dependencies

* [Qt5](http://download.qt.io/archive/qt/) 
* [asio](https://github.com/chriskohlhoff/asio) 
* [websocketpp](https://github.com/zaphoyd/websocketpp) 
* [rapidjson](https://github.com/Tencent/rapidjson.git) 
* [spdlog](https://github.com/gabime/spdlog)
* [WebRTC] M104

* *Note:* 
* asio/websocketpp/rapidjson/spdlog have joined this repository as submodules

## UI

<img src="https://github.com/ouxianghui/mediasoup-client/blob/main/UI.png" width="960" height="540" /><br>

## UI

<img src="https://github.com/ouxianghui/mediasoup-client/blob/main/UI.png" width="960" height="540" /><br>

## IDE
* Xcode
* Run `/Applications/Qt/6.2.3/macos/bin/qmake ./App/App.pro -spec macx-xcode` and `/Applications/Qt/6.2.3/macos/bin/qmake ./RoomClient/RoomClient.pro -spec macx-xcode` to generate Xcode project.

* Qt Creator
* Open Mediasoup.pro using Qt Creator.

# macOS 下的使用，为了对齐m88以前的版本；
我在WebRTC的api/video/video_frame.h中添加了如下代码：
```cpp
VideoFrame::Builder& VideoFrame::Builder::set_update_rect(
    const VideoFrame::UpdateRect& update_rect) {
  update_rect_ = update_rect;
  return *this;
}
```
对应以前的老版本；