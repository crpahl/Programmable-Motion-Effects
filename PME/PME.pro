QT += opengl
TARGET = PME
TEMPLATE = app
OTHER_FILES += \
    input_test.txt

HEADERS += \
    Parser.h \
    mainwindow.h \
    cswindow.h

SOURCES += \
    Parser.cpp \
    mainwindow.cpp \
    main.cpp \
    cswindow.cpp
