#!/bin/bash
# 退出时如果有错误则停止执行
set -e

# export PATH=$PATH:/Users/vrv/Documents/luoyongmeng/WebRTC_iOS_108_h265/depot_tools
# export PATH=/Library/Developer/CommandLineTools/usr/bin:$PATH

# fetch --nohooks webrtc_ios

# # 查看可用版本分支
# git branch -r
# # 切换到m79分支
# git checkout branch-heads/5359(m108)
# gclient sync
# # 或者强制切换到指定commit（eab124aa4dab921c3ab49c7f2e401ddd0647895b id）
# gclient sync -r eab124aa4dab921c3ab49c7f2e401ddd0647895b --force



MAC_LIBPATH=out/mac-debug

# 如果 depot_tools 没有加入 PATH，请设置环境变量（根据实际情况修改路径）
# export PATH="$HOME/depot_tools:$PATH"

# # 同步代码（如果已经同步可以跳过）
# echo "开始同步 WebRTC 代码..."
# gclient sync
cd src
# 生成 GN 构建文件，生成 Xcode 工程文件（静态库模式） use_custom_libcxx=false
echo "生成 GN 构建文件... $(pwd)"
gn gen ${MAC_LIBPATH} --args='target_os="mac" target_cpu="x64" is_clang=true is_debug=false use_rtti=true use_custom_libcxx=false enable_stripping=true  is_component_build=false rtc_use_h264=true  proprietary_codecs=true rtc_include_tests=false rtc_enable_objc_symbol_export=true' --ide=xcode

# 编译生成静态库
echo "开始编译 WebRTC..."
ninja -C ${MAC_LIBPATH}

echo "编译完成，开始合并 WebRTC 静态库..."

FIND_PATH="${MAC_LIBPATH}/obj/sdk"
OUTPUT_LIB="libsdk_combined.a"

# 查找 sdk 目录下所有 .a 文件
LIB_LIST=$(find "${FIND_PATH}" -maxdepth 1 -name "lib*.a")

if [ -z "$LIB_LIST" ]; then
    echo "没有找到 .a 文件！"
    exit 1
fi

echo "合并以下 .a 文件："
echo "$LIB_LIST"

# 使用 libtool 合并
libtool -static -o "${MAC_LIBPATH}/${OUTPUT_LIB}" $LIB_LIST

echo "合并完成，生成的库为 ${MAC_LIBPATH}/${OUTPUT_LIB}"

echo "压缩 WebRTC.framework..."
zip -ry ${MAC_LIBPATH}/WebRTC.framework.zip ${MAC_LIBPATH}WebRTC.framework

# 可选：打开生成的 Xcode 工程
echo "打开 Xcode 工程..."
# open ${MAC_LIBPATH}/all.xcodeproj

