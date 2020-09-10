QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


INCLUDEPATH += "$$(OPENCV_3_4)/include" 
			   
CONFIG(release, debug|release): LIBS    += "$$(OPENCV_3_4)/x64/vc14/lib/opencv_world340.lib"
										   
CONFIG(debug, debug|release): LIBS    += "$$(OPENCV_3_4)/x64/vc14/lib/opencv_world340d.lib"

SOURCES += \
    controller/SignalCenter.cpp \
    main.cpp \
    model/CVGraphicsModel.cpp \
    model/ParamListModel.cpp \
    ui/MainWidget.cpp \
    ui/MainWindow.cpp \
    ui/widgets/CVImageViewer/CVGraphicsView.cpp \
    ui/widgets/MousePositionWidget.cpp \
    model/ImageModel.cpp \
    model/RoiRectModel.cpp \
    ui/widgets/OptionsButtonBar.cpp \
    ui/widgets/ParamList.cpp 

HEADERS += \
    controller/SignalCenter.h \
    model/CVGraphicsModel.h \
    model/ParamListModel.h \
    ui/MainWidget.h \
    ui/MainWindow.h \
    ui/widgets/CVImageViewer/CVGraphicsView.h \
    ui/widgets/MousePositionWidget.h \
    model/ImageModel.h \
    model/RoiRectModel.h   \
    ui/widgets/OptionsButtonBar.h \
    ui/widgets/ParamList.h 

FORMS += \
    ui/widgets/MousePostionWidget.ui \
    ui/MainWidget.ui  \
    ui/widgets/OptionsButtonBar.ui 
    
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource/qss.qrc
