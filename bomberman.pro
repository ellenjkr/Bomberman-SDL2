TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
SOURCES += bomberman.cpp

HEADERS += bomberman.h

win32: LIBS += -L$$PWD/../../SDL2-2.0.10/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../SDL2-2.0.10/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../../SDL2-2.0.10/i686-w64-mingw32/include

win32: LIBS += -L$$PWD/../../../Documents/SDL2-2.0.10/i686-w64-mingw32/lib/ -lSDL2

INCLUDEPATH += $$PWD/../../../Documents/SDL2-2.0.10/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../../../Documents/SDL2-2.0.10/i686-w64-mingw32/include
