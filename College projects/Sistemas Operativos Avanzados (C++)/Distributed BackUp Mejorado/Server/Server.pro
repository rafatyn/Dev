#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T16:03:38
#
#-------------------------------------------------

QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Distributed-Backup-Server
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    configfile.cpp

HEADERS  += mainwindow.h \
    configfile.h

FORMS    += mainwindow.ui

unix {
    # Variables
    isEmpty(PREFIX) {
        PREFIX = /usr
    }
    BINDIR  = $$PREFIX/bin

    CONFDIR = /etc
    SCRIPTDIR = $$CONFDIR/init.d
    isEmpty(VARDIR) {
        VARDIR  = /var/lib/$${TARGET}
    }

    # Install
    INSTALLS += target config vardir script script2
    ## Instalar ejecutable
    target.path = $$BINDIR

    ## Instalar archivo de configuración
    config.path = $$CONFDIR
    config.files += $${TARGET}.conf

    ## Crear directorio de archivos variables
    vardir.path = $$VARDIR
    vardir.commands = true

    ## Mover el scrip de arranque a su carpeta destino
    script.path = $$SCRIPTDIR
    script.files += $${TARGET}

    ##Asociar el fichero al arranque
    script2.path = $$SCRIPTDIR
    script2.command = update-rc.d $${TARGET} defaults
}

message('Including config files')
include($$PWD/QttpServer/config/config.pri)

message('Including core files')
include($$PWD/QttpServer/core.pri)
