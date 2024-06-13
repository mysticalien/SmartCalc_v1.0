QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets gui printsupport

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../../RPN.c \
    ../../doublestack.c \
    ../../loan_calc.c \
    ../../calc.c \
    ../../stack.c \
    ../../replace_x.c \
    ../../parser.c \
    ../../validation.c \
    ../../deposit_calc.c \
    depositcalc.cpp \
    loancalc.cpp \
    main.cpp \
    mainwindow.cpp \
    plot.cpp \
    qcustomplot.cpp

HEADERS += \
    ../../calc.h \
    ../../stack.h \
    depositcalc.h \
    loancalc.h \
    mainwindow.h \
    plot.h \
    qcustomplot.h

FORMS += \
    depositcalc.ui \
    loancalc.ui \
    mainwindow.ui \
    plot.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target