QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Analizador/Graficar.cpp \
        Analizador/Nodo.cpp \
        Analizador/parser.cpp \
        Analizador/scanner.cpp \
        Ejecutar.cpp \
        Montar/Disco.cpp \
        Montar/Montar.cpp \
        Montar/Particion.cpp \
        Usuario.cpp \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    Analizador/lexico.l \
    Analizador/sintactico.yy

HEADERS += \
    Analizador/Graficar.h \
    Analizador/Nodo.h \
    Analizador/parser.h \
    Analizador/scanner.h \
    Ejecutar.h \
    Montar/Disco.h \
    Montar/Montar.h \
    Montar/Particion.h \
    Usuario.h
