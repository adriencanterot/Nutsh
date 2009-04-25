# -------------------------------------------------
# Project created by QtCreator 2009-01-24T16:01:49
# -------------------------------------------------
QT += sql

DESTDIR += bin \

win32 {

INCLUDEPATH += .\
./3rdparty \
./3rdparty/FMOD3/inc \
./3rdparty/taglib/include/taglib

LIBS += -L3rdparty/taglib/lib -ltag \
-L3rdparty/FMOD3/lib -lfmod
}
!win32 {
LIBS +=  -framework TagLib
QT += phonon
}


TARGET = nutsh-05
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
    src/nutshplayinginterface.cpp
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
    src/nutshplayinginterface.h
