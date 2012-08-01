TEMPLATE = app
CONFIG+=testcase
testcase.timeout = 400 # this test is slow
QT += network location testlib
TARGET = tst_qnmeapositioninfosource_realtime_generic

INCLUDEPATH += ..

HEADERS += ../../utils/qlocationtestutils_p.h \
           ../../qgeopositioninfosource/testqgeopositioninfosource_p.h \
           ../qnmeapositioninfosourceproxyfactory.h \
           ../tst_qnmeapositioninfosource.h

SOURCES += ../../utils/qlocationtestutils.cpp \
           ../../qgeopositioninfosource/testqgeopositioninfosource.cpp \
           ../qnmeapositioninfosourceproxyfactory.cpp \
           ../tst_qnmeapositioninfosource.cpp \
           tst_qnmeapositioninfosource_realtime_generic.cpp
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0
