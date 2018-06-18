#-------------------------------------------------
#
# Project created by QtCreator 2011-05-26T15:38:31
#
#-------------------------------------------------

QT       += core gui xml
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SpriteDecomposer
TEMPLATE = app

SOURCES += main.cpp\
        interface.cpp \
    workarea.cpp \
    animation.cpp \
    cut.cpp \
    frame.cpp \
    sequencer.cpp \
    mark.cpp \
    aboutdialog.cpp \
    application.cpp

ICON = SpriteDecomposer.icns

HEADERS  += interface.h \
    workarea.h \
    animation.h \
    cut.h \
    frame.h \
    sequencer.h \
    mark.h \
    aboutdialog.h \
    application.h \
    saveable_widget.h

FORMS    += interface.ui \
    aboutdialog.ui

RESOURCES += menu.qrc \
    lang.qrc

TRANSLATIONS = lang/fr_fr.ts \
            lang/en_us.ts

QMAKE_CXXFLAGS +=  -std=c++14 -Wall -frtti -fexceptions -Werror=return-type
QMAKE_CXXFLAGS +=-Werror=overloaded-virtual
QMAKE_CXXFLAGS +=  -Wctor-dtor-privacy -Werror=delete-non-virtual-dtor -fstrict-aliasing
QMAKE_CXXFLAGS +=  -Werror=strict-aliasing -Wstrict-aliasing=2
QMAKE_CXXFLAGS +=  -Wno-warning=gnu-statement-expression

CONFIG += c++14

#using new C++ libs for macos http://blog.michael.kuron-germany.de/2013/02/using-c11-on-mac-os-x-10-8/
#that may not work with C++14 though, Apple is slow
macx: QMAKE_CXXFLAGS += -stdlib=libc++
macx: QMAKE_LFLAGS += -lc++
macx: QMAKE_CXXFLAGS += -mmacosx-version-min=10.10
macx: QMAKE_MACOSX_DEPLOYMENT_TARGET=10.10

CONFIG(debug, debug|release) {
     message( "Building the DEBUG Version" )
     #lets optimize for CPU on debug, for release - packager should do
     QMAKE_CXXFLAGS +=  -march=native -O0 -g
     DEFINES += _DEBUG
     unix:!maxc:QMAKE_CXXFLAGS += -fsanitize=undefined -fsanitize=vptr
     unix:!maxc:LIBS += -lubsan
}
else {
    DEFINES += NDEBUG
    message( "Building the RELEASE Version" )
    #delegated to packager - didn't work easy, let it be here
    #QMAKE_CXXFLAGS += -O3 -march=native
    QMAKE_CXXFLAGS_RELEASE = -O3 -march=native
}
