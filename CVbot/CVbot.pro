#-------------------------------------------------
#
# Detector de Rostros con Rotacion
#
#-------------------------------------------------

QT += opengl widgets serialport

unix:INCLUDEPATH += "/usr/include/GL/"                          # OpenGL
unix:LIBS += "/usr/lib/x86_64-linux-gnu/libglut.so"               # OpenGL

DIR_OPENCV_LIBS = /usr/local/lib

unix:LIBS += -L$$DIR_OPENCV_LIBS

unix:LIBS += -lopencv_core \
             -lopencv_highgui \
             -lopencv_imgproc \
             -lopencv_objdetect \
#             -lopencv_calib3d \
#             -lopencv_ml \
#             -lopencv_video \
#             -lopencv_features2d \
#             -lopencv_flann \
#             -lopencv_photo \
#             -lopencv_stitching \
#             -lopencv_superres \
#             -lopencv_video \
#             -lopencv_videostab \
#             -lopencv_imgcodecs \
             -lopencv_videoio \
#             -lopencv_bgsegm


SOURCES += main.cpp \
    controlador.cpp \
    container.cpp \
    window.cpp \
    cameraprocessor.cpp \
    camerawidget.cpp

HEADERS += \
    block.h \
    container.h \
    cameraprocessor.h \
    window.h \
    controlador.h \
    camerawidget.h \
    texture.h

FORMS += \
    controlador.ui
