#-------------------------------------------------
#
# Project created by QtCreator 2019-06-21T15:53:51
#
#-------------------------------------------------

QT       += core gui network opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtScrcpy
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        dialog.cpp \
    videoform.cpp

HEADERS += \
        dialog.h \
    videoform.h

FORMS += \
        dialog.ui \
    videoform.ui

# 子模块
include($$PWD/adb/adb.pri)
include($$PWD/server/server.pri)
include($$PWD/decoder/decoder.pri)
include($$PWD/common/common.pri)
include($$PWD/render/render.pri)
include($$PWD/android/android.pri)
include($$PWD/inputcontrol/inputcontrol.pri)


# 包含目录
INCLUDEPATH += \
    $$PWD/adb \
    $$PWD/server \
    $$PWD/decoder \
    $$PWD/common \
    $$PWD/render \
    $$PWD/android \
    $$PWD/inputcontrol \
    $$PWD/third_party/ffmpeg/include

# *************************************************
# Win平台
win32 {
# 输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/output/win/debug
}else{
    DESTDIR = $$PWD/output/win/release
}
# 依赖模块
LIBS += \
    -L$$PWD/third_party/ffmpeg/lib -lavformat \
    -L$$PWD/third_party/ffmpeg/lib -lavcodec \
    -L$$PWD/third_party/ffmpeg/lib -lavutil \
    -L$$PWD/third_party/ffmpeg/lib -lswscale \
}
# *************************************************

# *************************************************
# macos平台
macos {
# 输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/output/mac/debug
}else{
    DESTDIR = $$PWD/output/mac/release
}
# 依赖模块
LIBS += \
    -L$$PWD/third_party/ffmpeg/lib -lavformat.58 \
    -L$$PWD/third_party/ffmpeg/lib -lavcodec.58 \
    -L$$PWD/third_party/ffmpeg/lib -lavutil.56 \
    -L$$PWD/third_party/ffmpeg/lib -lswscale.5 \
}
# *************************************************


# *************************************************
# Linux平台
linux {
# 输出目录
CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/output/linux/debug
}else{
    DESTDIR = $$PWD/output/linux/release
}
# 依赖模块
LIBS += \
    -L$$PWD/third_party/ffmpeg/lib -lavformat \
    -L$$PWD/third_party/ffmpeg/lib -lavcodec \
    -L$$PWD/third_party/ffmpeg/lib -lavutil \
    -L$$PWD/third_party/ffmpeg/lib -lswscale \
}
# *************************************************

