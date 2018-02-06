# -------------------------------------------------
# Project created by QtCreator 2009-01-24T16:01:49
# -------------------------------------------------
QT += gui \
    sql \
    network \
    xml \
    declarative 


ICON += nutsh.icns
CONFIG += release
DESTDIR += bin
win32 { 
    INCLUDEPATH += ./3rdparty/win/FMOD3/inc \
        ./3rdparty/win/taglib/include/taglib
    LIBS += -L3rdparty/win/taglib/lib \
        -ltag \
        -L3rdparty\win\FMOD3\lib \
        -lfmod
}
macx { 
    LIBS += -L/usr/local/lib -ltag
    INCLUDEPATH += /usr/local/include/taglib
    OTHER_FILES += style.css
}
linux-g++ { 
    LIBS += -ltag
    INCLUDEPATH += 3rdparty/linux/include
    QT += phonon
}
TARGET = Nutsh
TEMPLATE = app
SOURCES += src/main.cpp \
    src/nutshupdater.cpp \
    src/dailysonginterface.cpp \
    src/core.cpp \
    src/driveinterface.cpp \
    src/editinterface.cpp \
    src/indexer.cpp \
    src/installationwizard.cpp \
    src/label.cpp \
    src/mainwindow.cpp \
    src/maj.cpp \
    src/metadata.cpp \
    src/metadatainterface.cpp \
    src/metadatalist.cpp \
    src/playbox.cpp \
    src/playlistinterface.cpp \
    src/playinginterface.cpp \
    src/playlistlist.cpp \
    src/searchlineinterface.cpp \
    src/style.cpp \
    src/progressinterface.cpp \
    src/systemtrayicon.cpp \
    src/subinterfaces.cpp \
    src/sqlmanager.cpp \
    src/player.cpp
HEADERS += \
    src/preprocess.h \
    src/dailysonginterface.h \
    src/core.h \
    src/driveinterface.h \
    src/editinterface.h \
    src/indexer.h \
    src/installationwizard.h \
    src/label.h \
    src/mainwindow.h \
    src/maj.h \
    src/metadata.h \
    src/metadatainterface.h \
    src/metadatalist.h \
    src/playbox.h \
    src/playinginterface.h \
    src/playlistinterface.h \
    src/playlistlist.h \
    src/progressinterface.h \
    src/searchlineinterface.h \
    src/style.h \
    src/subinterfaces.h \
    src/updater.h \
    src/systemtrayicon.h \
    src/sqlmanager.h \
    src/player.h
RESOURCES += nutsh.qrc
OBJECTS_DIR = obj/
MOC_DIR = moc/
RC_FILE += icon.rc
TRANSLATIONS += Translations/nutsh_en.ts \
    Translations/nutsh_es.ts
OTHER_FILES += \
    qml/EditInterface.qml \
    qml/MetaInput.qml \
    Interface.qml
