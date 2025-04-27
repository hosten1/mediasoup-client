#ifndef PROMISEDEVICE_H
#define PROMISEDEVICE_H

#include <QObject>
#include <functional>  // 添加此行


class Permissions : public QObject {
    Q_OBJECT
public:
    explicit Permissions(QObject *parent = nullptr);
    static bool requestCameraPermission();
    static void requestCameraPermission(std::function<void(bool)> callback);
    static void requestMicrophonePermission(std::function<void(bool)> callback);

};

#endif // PROMISEDEVICE_H
