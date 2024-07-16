QT       += core gui printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Controller.cpp \
    Model.cpp \
    graphview.cpp \
    main.cpp \
    View.cpp \
    qcustomplot.cpp

HEADERS += \
    Controller.h \
    IController.h \
    IModel.h \
    IView.h \
    Model.h \
    View.h \
    graphview.h \
    qcustomplot.h

FORMS += \
    graphview.ui \
    view.ui

LIBS -= /usr/local/lib/QtCore.framework/Versions/A/QtCore

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
