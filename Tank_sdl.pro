TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp

INCLUDEPATH += C:/Software/SDL/include
LIBS += -LC:/Software/SDL/lib -lmingw32 -mwindows -mconsole -lSDL2main -lSDL2 -lSDL2_image
