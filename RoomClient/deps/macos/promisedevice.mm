#include "promisedevice.h"


#import <AVFoundation/AVFoundation.h>
#import <CoreMedia/CoreMedia.h>
#import <CoreVideo/CoreVideo.h>
#include <stdint.h>  // ✅ 确保定义 int64_t

@interface CameraHandler : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>
@property (nonatomic, strong) AVCaptureSession *session;
@property (nonatomic, strong) AVCaptureDeviceInput *videoInput;
@property (nonatomic, strong) AVCaptureVideoDataOutput *videoOutput;
@property (nonatomic, strong) AVCaptureVideoPreviewLayer *previewLayer;
@property (nonatomic, assign) dispatch_queue_t videoQueue;
@end

@implementation CameraHandler

- (instancetype)init {
    self = [super init];
    if (self) {
        self.session = [[AVCaptureSession alloc] init];
        self.videoQueue = dispatch_queue_create("videoQueue", DISPATCH_QUEUE_SERIAL);
    }
    return self;
}

- (void)startCamera {
    NSArray<AVCaptureDevice *> *devices = [[AVCaptureDeviceDiscoverySession
        discoverySessionWithDeviceTypes:@[
            AVCaptureDeviceTypeBuiltInWideAngleCamera,
        ]
        mediaType:AVMediaTypeVideo
        position:AVCaptureDevicePositionUnspecified] devices];

    if (devices.count == 0) {
        NSLog(@"❌ 没有找到可用的摄像头");
        return;
    }

    AVCaptureDevice *device = devices.firstObject;
    NSLog(@"✅ 找到摄像头: %@", device.localizedName);
    if (!device) {
        NSLog(@"❌ 摄像头不可用");
        return;
    }

    NSError *error = nil;
    self.videoInput = [AVCaptureDeviceInput deviceInputWithDevice:device error:&error];
    if (error) {
        NSLog(@"❌ 无法获取摄像头输入: %@", error.localizedDescription);
        return;
    }

    if ([self.session canAddInput:self.videoInput]) {
        [self.session addInput:self.videoInput];
    } else {
        NSLog(@"❌ 无法添加摄像头输入");
        return;
    }

    // 配置输出流
    self.videoOutput = [[AVCaptureVideoDataOutput alloc] init];
    [self.videoOutput setSampleBufferDelegate:self queue:self.videoQueue];

    if ([self.session canAddOutput:self.videoOutput]) {
        [self.session addOutput:self.videoOutput];
    } else {
        NSLog(@"❌ 无法添加摄像头输出");
        return;
    }

    self.previewLayer = [AVCaptureVideoPreviewLayer layerWithSession:self.session];
    self.previewLayer.videoGravity = AVLayerVideoGravityResizeAspectFill;

    // 启动摄像头
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [self.session startRunning];

        // 延迟 1 秒检查 session 是否真的在运行
        dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (long long)(1.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
            if (self.session.isRunning) {
                NSLog(@"✅ 摄像头成功启动");
            } else {
                NSLog(@"❌ 摄像头启动失败");
            }
        });
    });
}

// 监听视频帧数据
- (void)captureOutput:(AVCaptureOutput *)output didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer fromConnection:(AVCaptureConnection *)connection {
    CVImageBufferRef imageBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);
    if (imageBuffer) {
        size_t width = CVPixelBufferGetWidth(imageBuffer);
        size_t height = CVPixelBufferGetHeight(imageBuffer);
        NSLog(@"📷 输出流: 分辨率 %zux%zu", width, height);
    }
}

@end


Permissions::Permissions(QObject *parent) : QObject(parent) {}

bool Permissions::requestCameraPermission() {
    __block bool granted = false;

    dispatch_semaphore_t semaphore = dispatch_semaphore_create(0);

    [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL grantedAccess) {
        granted = grantedAccess;
        dispatch_semaphore_signal(semaphore);
    }];

    dispatch_semaphore_wait(semaphore, DISPATCH_TIME_FOREVER);

    return granted;
}

void Permissions::requestCameraPermission(std::function<void(bool)> callback) {
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeVideo];

    if (status == AVAuthorizationStatusAuthorized) {
        // ✅ 权限已授权
        callback(true);
//        dispatch_async(dispatch_get_main_queue(), ^{
//            CameraHandler *camera = [[CameraHandler alloc] init];
//            [camera startCamera];
//        });
    } else if (status == AVAuthorizationStatusNotDetermined) {
        // ⏳ 请求权限
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeVideo completionHandler:^(BOOL granted) {
            dispatch_async(dispatch_get_main_queue(), ^{
                callback(granted);
                if (granted) {
//                    CameraHandler *camera = [[CameraHandler alloc] init];
//                    [camera startCamera];
                } else {
                    NSLog(@"❌ 用户拒绝了摄像头权限");
                }
            });
        }];
    } else {
        // ❌ 权限被拒绝或受限
        callback(false);
        NSLog(@"❌ 无法访问摄像头，请在系统设置中授权");
    }
}
void Permissions::requestMicrophonePermission(std::function<void(bool)> callback) {
    AVAuthorizationStatus status = [AVCaptureDevice authorizationStatusForMediaType:AVMediaTypeAudio];

    if (status == AVAuthorizationStatusAuthorized) {
        // ✅ 权限已授权
        callback(true);
//        dispatch_async(dispatch_get_main_queue(), ^{
//            MicrophoneHandler *microphone = [[MicrophoneHandler alloc] init];
//            [microphone startMicrophone];
//        });
    } else if (status == AVAuthorizationStatusNotDetermined) {
        // ⏳ 请求权限
        [AVCaptureDevice requestAccessForMediaType:AVMediaTypeAudio completionHandler:^(BOOL granted) {
            dispatch_async(dispatch_get_main_queue(), ^{
                callback(granted);
                if (granted) {
//                    MicrophoneHandler *microphone = [[MicrophoneHandler alloc] init];
//                    [microphone startMicrophone];
                } else {
                    NSLog(@"❌ 用户拒绝了麦克风权限");
                }
            });
        }];
    } else {
        // ❌ 权限被拒绝或受限
        callback(false);
        NSLog(@"❌ 无法访问麦克风，请在系统设置中授权");
    }
}

