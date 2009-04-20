# -------------------------------------------------
# Project created by QtCreator 2009-01-24T16:01:49
# -------------------------------------------------
QT += sql \
    phonon
LIBS +=  -framework TagLib

TARGET = nutsh-05
TEMPLATE = app
SOURCES += main.cpp \
    nutshmainwindow.cpp \
    nutshlecteur.cpp \
    nutshindexer.cpp \
    nutshsqlsaver.cpp \
    nutshmetadata.cpp \
    nutshplaylistinterface.cpp \
    nutshcomunicator.cpp \
    nutshsearchlineinterface.cpp \
    nutshdriveinterface.cpp \
    nutshmetadatainterface.cpp \
    nutshmetadatalist.cpp \
    nutshplayinginterface.cpp
HEADERS += nutshmainwindow.h \
    nutshlecteur.h \
    nutshindexer.h \
    nutshsqlsaver.h \
    nutshmetadata.h \
    nutshplaylistinterface.h \
    nutshcomunicator.h \
    nutshsearchlineinterface.h \
    nutshdriveinterface.h \
    preprocess.h \
    nutshmetadatainterface.h \
    nutshmetadatalist.h \
    nutshplayinginterface.h
