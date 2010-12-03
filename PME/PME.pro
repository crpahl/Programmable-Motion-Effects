QT += opengl
TEMPLATE = app
TARGET = PME
OTHER_FILES += \
    input_test.txt

HEADERS += \
    Parser.h \
    mainwindow.h \
    cswindow.h \
    TAO.h \
    Object3D.h \
    BiPlane.h

SOURCES += \
    Parser.cpp \
    mainwindow.cpp \
    main.cpp \
    cswindow.cpp \
    TAO.cpp \
    Object3D.cpp \
    BiPlane.cpp
