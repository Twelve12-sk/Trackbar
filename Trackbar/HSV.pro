TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    hsv.cpp
INCLUDEPATH += /usr/local/include \
                /usr/local/include/opencv

                /usr/local/include/opencv2

LIBS += /usr/local/lib/libopencv_* \

HEADERS += \
    com2.h
