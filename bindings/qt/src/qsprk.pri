################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
include(../common.pri)
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

qsprk-uselib:!qsprk-buildlib {
    LIBS += -L$$QSPRK_LIBDIR -l$$QSPRK_LIBNAME
} else {
    HEADERS       += \
                     $$PWD/qsprk.h \
                     $$PWD/qsprkctx.h \
                     $$PWD/qsprkdataset.h

    SOURCES       += \
                     $$PWD/qsprkctx.cpp \
                     $$PWD/qsprkdataset.cpp
}

win32 {
    qsprk-buildlib:shared:DEFINES += QT_SPRK_EXPORT
    else:qsprk-uselib:DEFINES += QT_SPRK_IMPORT
}
################################################################################
#  THIS FILE IS 100% GENERATED BY ZPROJECT; DO NOT EDIT EXCEPT EXPERIMENTALLY  #
#  Please refer to the README for information about making permanent changes.  #
################################################################################
