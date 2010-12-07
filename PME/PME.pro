QT += opengl
TEMPLATE = app
CONFIG += console
TARGET = PME
OTHER_FILES += \
    input_test.txt \
    input_octagon.txt \
    input_cube.txt \
    input_triangle.txt \
    input_octagon.txt \
    input_cube.txt

HEADERS += \
    Parser.h \
    mainwindow.h \
    cswindow.h \
    TAO.h \
    Object3D.h \
    Vector.h \
    bilinear.h \
    camera.h \
    Ray.h

SOURCES += \
    Parser.cpp \
    mainwindow.cpp \
    main.cpp \
    cswindow.cpp \
    TAO.cpp \
    Object3D.cpp \
    Vector.cc \
    bilinear.cc \
    camera.cpp \
    Ray.cpp
