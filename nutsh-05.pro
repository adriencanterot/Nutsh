# -------------------------------------------------
# Project created by QtCreator 2009-01-24T16:01:49
# -------------------------------------------------
QT += sql \
    network
ICON += nutsh.icns
CONFIG += qt debug
DESTDIR += bin
win32 { 
    INCLUDEPATH += . \
        ./3rdparty/win \
        ./3rdparty/win/FMOD3/inc \
        ./3rdparty/win/taglib/include/taglib
    LIBS += -L3rdparty/win/taglib/lib \
        -ltag \
        -L3rdparty/win/FMOD3/lib \
        -lfmod
}
macx { 
    LIBS += -F3rdparty/mac \
        -framework \
        TagLib
    QT += phonon
    INCLUDEPATH += 3rdparty/mac/TagLib.framework/Headers/
    OTHER_FILES += style.css
}
linux-g++ {
    LIBS += -ltag
    QT += phonon
}
TARGET = Nutsh
TEMPLATE = app
SOURCES += src/main.cpp \
    src/nutshmainwindow.cpp \
    src/nutshlecteur.cpp \
    src/nutshindexer.cpp \
    src/nutshsqlsaver.cpp \
    src/nutshmetadata.cpp \
    src/nutshplaylistinterface.cpp \
    src/nutshcomunicator.cpp \
    src/nutshsearchlineinterface.cpp \
    src/nutshdriveinterface.cpp \
    src/nutshmetadatainterface.cpp \
    src/nutshmetadatalist.cpp \
    src/nutshplayinginterface.cpp \
    src/nutshupdater.cpp \
    src/nutshmaj.cpp \
    src/nutshprogressinterface.cpp \
    src/nutshplaylistlist.cpp \
    src/nutshinstallationwizard.cpp \
    src/nutshlabel.cpp \
    src/style.cpp \
    src/nutshsubinterfaces.cpp
HEADERS += src/nutshmainwindow.h \
    src/nutshlecteur.h \
    src/nutshindexer.h \
    src/nutshsqlsaver.h \
    src/nutshmetadata.h \
    src/nutshplaylistinterface.h \
    src/nutshcomunicator.h \
    src/nutshsearchlineinterface.h \
    src/nutshdriveinterface.h \
    src/preprocess.h \
    src/nutshmetadatainterface.h \
    src/nutshmetadatalist.h \
    src/nutshplayinginterface.h \
    src/nutshupdater.h \
    src/nutshmaj.h \
    src/nutshprogressinterface.h \
    src/nutshplaylistlist.h \
    src/nutshinstallationwizard.h \
    src/nutshlabel.h \
    src/nutshsubinterfaces.h
RESOURCES += nutsh.qrc
