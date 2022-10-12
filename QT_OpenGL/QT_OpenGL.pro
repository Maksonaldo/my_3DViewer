QT       += core gui openglwidgets opengl printsupport

include(for_gif/gifimage/qtgifimage.pri)
greaterThan(QT_MAJOR_VERSION, 4): QT += opengl



CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    widget.cpp \
    ../parsing.c \
    ../afins.c

HEADERS += \
    mainwindow.h \
    widget.h \
    ../parsing.h \
    ../afins.h

FORMS += \
    mainwindow.ui \


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../text.txt \
    text.txt
